use actix_web::{get, web::{Data, Query}, HttpResponse, Responder};
use serde::Deserialize;
use sqlx::query_as;
use crate::model::{AppState, Local, Point};
use std::collections::HashSet;  

#[derive(Deserialize, Debug)]
pub struct Request {
    pub name: String,
    max_distance: Option<usize>,
}

#[derive(Deserialize, Debug)]
struct ReverseRequest {
    lat:  f64,
    long: f64,
}

fn distancia_de_edicao(str1: &str, str2: &str) -> usize {
    if str1.len() <= 1 || str2.len() <= 1 {
        return usize::MAX; // Retorna um valor alto para palavras com tamanho <= 1
    }

    let m = str1.len();
    let n = str2.len();
    let mut matriz = vec![vec![0; n + 1]; m + 1];

    for i in 0..=m {
        matriz[i][0] = i;
    }
    for j in 0..=n {
        matriz[0][j] = j;
    }

    for i in 1..=m {
        for j in 1..=n {
            let custo = if str1.as_bytes()[i - 1] == str2.as_bytes()[j - 1] {
                0
            } else {
                1
            };
            matriz[i][j] = usize::min(
                usize::min(matriz[i - 1][j] + 1, matriz[i][j - 1] + 1),
                matriz[i - 1][j - 1] + custo,
            );
        }
    }

    matriz[m][n]
}

fn jaccard_similarity(str1: &str, str2: &str) -> f64 {
    let set1: HashSet<_> = str1.chars().collect();
    let set2: HashSet<_> = str2.chars().collect();

    let intersection: HashSet<_> = set1.intersection(&set2).copied().collect();
    let union: HashSet<_> = set1.union(&set2).copied().collect();

    intersection.len() as f64 / union.len() as f64
}

#[get("/local")]
pub async fn get_local(state: Data<AppState>, query: Query<Request>) -> impl Responder {
    // Busca todos os locais
    let locais: Vec<Local> = match sqlx::query_as!(
        Local,
        "SELECT name, img_path, description, lat, long, ty, display_name FROM locais"
    )
    .fetch_all(state.db())
    .await
    {
        Ok(locais) => locais,
        Err(_) => return HttpResponse::InternalServerError().finish(),
    };

    // Calcula a similaridade de cada local com o nome pesquisado
    let nome_pesquisado = query.name.to_lowercase();
    let max_distance = query.max_distance.unwrap_or(5);
    let min_similarity = 0.2; // Similaridade mínima de Jaccard para considerar a palavra

    let mut similares: Vec<(Local, usize, f64)> = locais
        .into_iter()
        .map(|local| {
            let distancia = distancia_de_edicao(&nome_pesquisado, &local.name.to_lowercase());
            let similaridade = jaccard_similarity(&nome_pesquisado, &local.name.to_lowercase());
            (local, distancia, similaridade)
        })
        .filter(|(_, _, similaridade)| *similaridade >= min_similarity)
        .collect();

    // Ordena pelos mais semelhantes
    similares.sort_by(|a, b| a.1.cmp(&b.1));

    // Verifica se a menor distância está dentro do limite permitido
    if let Some((local, distancia, _)) = similares.first() {
        if distancia <= &max_distance {
            HttpResponse::Ok().json(local)
        } else {
            HttpResponse::NotFound().json(format!("Local `{}` não encontrado dentro da distância máxima permitida", query.name))
        }
    } else {
        HttpResponse::NotFound().json(format!("Local `{}` não encontrado", query.name))
    }
}

#[derive(Deserialize, Debug)]
pub struct CategoryRequest {
    pub ty: String,
}

#[get("/category")]
pub async fn get_by_category(state: Data<AppState>, query: Query<CategoryRequest>) -> impl Responder {
    match query_as!(
        Local,
        "SELECT name, img_path, description, lat, long, ty, display_name FROM locais WHERE ty = $1",
        query.ty
    )
    .fetch_all(state.db())
    .await
    {
        Ok(locals) => HttpResponse::Ok().json(locals),
        _ => HttpResponse::NotFound().json(format!("Nenhum local encontrado para a categoria `{}`", query.ty)),
    }
}

#[get("/reverse")]
pub async fn get_reverse_search(
    state: Data<AppState>,
    query: Query<ReverseRequest>,
) -> impl Responder {
    let point = Point::new(query.lat, query.long);

    match sqlx::query_as!(
        Local,
        "SELECT name, display_name, img_path, description, lat, long, ty FROM locais",
    )
    .fetch_all(state.db())
    .await
    {
        Ok(locais) if !locais.is_empty() => {
            let min = locais
                .iter()
                .min_by(|a, b| {
                    a.point()
                        .distance(&point)
                        .total_cmp(&b.point().distance(&point))
                })
                .unwrap();
            HttpResponse::Ok().json(min)
        }
        _ => HttpResponse::NotFound().json(format!("Ponto `{:?}` nao encontrado", point)),
    }
}
