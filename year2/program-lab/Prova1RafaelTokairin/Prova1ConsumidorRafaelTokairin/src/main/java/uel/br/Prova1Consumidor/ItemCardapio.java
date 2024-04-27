package uel.br.Prova1Consumidor;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;

import java.io.Serializable;

@Entity
@Table(name="item_cardapio")
public class ItemCardapio implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    protected int id;
    protected String nome;
    protected String descricao;
    protected double preco;
    @ManyToOne
    @JoinColumn(name="id_restaurante")
    protected Restaurante restaurante;
    public int getId() { return this.id; }
    public String getNome() { return this.nome; }
    public double getPreco() {
        return this.preco;
    }
    public String getDescricao() {
        return this.descricao;
    }
    public Restaurante getRestaurante() {
        return restaurante;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public void setPreco(double preco) {
        this.preco = preco;
    }
}
