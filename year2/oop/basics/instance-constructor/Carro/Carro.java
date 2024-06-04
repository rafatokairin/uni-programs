public class Carro {
    private String marca;
    private String modelo;
    public Carro(String marca, String modelo) {
        this.marca = marca;
        this.modelo = modelo;
    }
    public String getMarca() {
        return marca;
    }
    public String getModelo() {
        return modelo;
    }
    public int calcMarcha(int veloAtual) {
        if (veloAtual <= 20)
            return 1;
        else if (veloAtual > 20 && veloAtual < 30)
            return 2;
        else if (veloAtual > 30 && veloAtual < 45)
            return 3;
        else if (veloAtual > 45 && veloAtual < 85)
            return 4;
        else if (veloAtual >= 85)
            return 5;
        else
            return 0;
    }
}