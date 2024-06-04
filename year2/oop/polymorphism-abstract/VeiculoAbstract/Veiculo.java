public abstract class Veiculo {
    private String marca;
    private String modelo;
    private String placa;
    public void licenciar(){
        System.out.println("Veiculo "+marca+" "+modelo+ " com a placa "+placa+" está licenciado!");
    }
    public abstract int obterNrEixos();
    public void setMarca(String marca) {
        this.marca = marca;
    }
    public void setModelo(String modelo) {
        this.modelo = modelo;
    }
    public void setPlaca(String placa) {
        this.placa = placa;
    }
}