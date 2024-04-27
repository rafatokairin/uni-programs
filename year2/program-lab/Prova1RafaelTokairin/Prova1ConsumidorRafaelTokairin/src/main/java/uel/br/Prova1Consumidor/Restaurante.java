package uel.br.Prova1Consumidor;

import jakarta.persistence.*;

import java.util.List;

@Entity
public class Restaurante {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String nome;
    public int getId() {
        return this.id;
    }

    @OneToMany(mappedBy = "restaurante")
    private List<ItemCardapio> itemCardapio;

    public void setId(int id) {
        this.id = id;
    }
    public String getNome() {
        return this.nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
}
