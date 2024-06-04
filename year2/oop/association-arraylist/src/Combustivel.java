public class Combustivel {
    private String nome;
    private double precoLitro;
    public double getPreco() {
        return precoLitro;
    }
    public String getNome() {
        return nome;
    }
    public void setPreco(double preco) {
        this.precoLitro = preco;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public double abastecerLitros(double litros) {
        return this.precoLitro * litros;
    }
    public double abastecerDinheiro(double dinheiro) {
        return dinheiro / this.precoLitro;
    }
}