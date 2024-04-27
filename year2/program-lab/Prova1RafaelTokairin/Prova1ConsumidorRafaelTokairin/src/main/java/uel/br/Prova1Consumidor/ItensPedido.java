package uel.br.Prova1Consumidor;

public class ItensPedido extends ItemCardapio {
    private int quantidadePedido;
    private String nomeRestaurante;
    public ItensPedido(int id, String nome, String descricao, double preco, String nomeRestaurante) {
        this.id = id;
        this.nome = nome;
        this.descricao = descricao;
        this.preco = preco;
        this.quantidadePedido = 1;
        this.nomeRestaurante = nomeRestaurante;
    }
    public int getQuantidadePedido() {
        return quantidadePedido;
    }
    public void setQuantidadePedido(int quantidadePedido) {
        this.quantidadePedido = this.quantidadePedido + quantidadePedido;
    }
    public String getNomeRestaurante() {
        return this.nomeRestaurante;
    }
    public void setNomeRestaurante(String nomeRestaurante) {
        this.nomeRestaurante = nomeRestaurante;
    }

}

