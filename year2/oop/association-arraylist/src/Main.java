import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Digite ID da bomba:");
        int id = sc.nextInt();
        sc.nextLine(); // remove caracter '\n' sc.nextInt()
        ArrayList<Combustivel> combustiveis = new ArrayList<Combustivel>();
        Bomba bomba = new Bomba();
        bomba.setId(id);
        boolean verifica = true;
        while (verifica) {
            System.out.println("Digite nome combustivel:");
            String nome = sc.nextLine();
            System.out.println("Digite valor/litro:");
            double valorLitro = sc.nextDouble();
            sc.nextLine(); // remove caracter '\n' sc.nextDouble()
            Combustivel comb = new Combustivel();
            comb.setNome(nome);
            comb.setPreco(valorLitro);
            combustiveis.add(comb);
            System.out.println("Inserir outro combustivel? s/n:");
            String confirmar = sc.nextLine();
            if (confirmar.equals("s") == false)
                verifica = false;
        }
        bomba.setCombustiveis(combustiveis);
        System.out.printf("\nID bomba: %d\n", bomba.getId());
        for (int i = 0; i < combustiveis.size(); i++) {
            System.out.printf("%d. %s: $%.2f\n", i, bomba.getCombustiveis().get(i).getNome(), bomba.getCombustiveis().get(i).getPreco());
        }
        System.out.println("\nDigite numero do combustivel:");
        int n = sc.nextInt();
        sc.nextLine(); // remove caracter '\n' sc.nextInt()
        System.out.println("Digite quantia de litros:");
        double litros = sc.nextDouble();
        sc.nextLine(); // remove caracter '\n' sc.nextDouble()
        System.out.printf("Total conta: $%.2f\n", bomba.getCombustiveis().get(n).abastecerLitros(litros));
        System.out.println("\nDigite quantia de dinheiro:");
        double dinheiro = sc.nextDouble();
        sc.nextLine(); // remove caracter '\n' sc.nextDouble()
        System.out.printf("Total abastecido: %.2fL\n", bomba.getCombustiveis().get(n).abastecerDinheiro(dinheiro));
    }
}