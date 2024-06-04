public class Main {
    public static void main(String[] args) {
        Veiculo c = new Carro();
        c.setMarca("Volkswagen");
        c.setModelo("Gol");
        c.setPlaca("ABC1D23");
        System.out.println(c.obterNrEixos());
        c.licenciar();
    }
}