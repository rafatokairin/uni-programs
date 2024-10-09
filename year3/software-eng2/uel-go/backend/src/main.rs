use actix_web::{web::Data, App, HttpServer};
use actix_cors::Cors;
use dotenv::dotenv;
use sqlx::postgres::PgPoolOptions;

mod model;
mod service;

use model::AppState;
use service::{get_local, get_by_category, get_reverse_search};

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    dotenv().ok();

    let database_url = std::env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    let pool = PgPoolOptions::new()
        .max_connections(5)
        .connect(&database_url)
        .await
        .expect("Could not connect to database");

    HttpServer::new(move || {
        App::new()
            .app_data(Data::new(AppState::new(pool.clone())))
            .wrap(
                Cors::default()
                    .allow_any_origin()
                    .allow_any_method()
                    .allow_any_header()
            )
            .service(get_local)
            .service(get_by_category)
            .service(get_reverse_search)
    })
    .bind(("localhost", 8080))?
    .run()
    .await
}
