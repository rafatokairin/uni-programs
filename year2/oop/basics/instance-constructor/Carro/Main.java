import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
            Carro carro1 = new Carro("Nissan", "Versa");

            String marca = carro1.getMarca();
            String modelo = carro1.getModelo();
            int marcha = carro1.calcMarcha(50);

            System.out.println(marca + ' ' + modelo);
            System.out.println("Marcha: " + marcha);
    }
}