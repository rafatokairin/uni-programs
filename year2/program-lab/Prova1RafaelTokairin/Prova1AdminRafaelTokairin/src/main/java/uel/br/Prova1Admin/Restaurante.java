package uel.br.Prova1Admin;

import jakarta.persistence.*;

import java.util.List;

@Entity
public class Restaurante {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String nome;
    @OneToMany(mappedBy = "restaurante", cascade = CascadeType.ALL)
    private List<ItemCardapio> itensCardapio;
    public int getId() {return id;}
    public void setId(int id) {this.id = id;}
    public String getNome() {return nome;}
    public void setNome(String nome) {this.nome = nome;}
    public List<ItemCardapio> getItensCardapio() {return itensCardapio;}
    public void setItensCardapio(List<ItemCardapio> itensCardapio) {this.itensCardapio = itensCardapio;}
}
