import java.util.Scanner;

public class Main {
    public static int div(int d, int n) throws ArithmeticException {
        return n / d;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, d;
        boolean cont = true;
        do {
            try {
                System.out.printf("Digite n: ");
                n = sc.nextInt();
                System.out.printf("Digite d: ");
                d = sc.nextInt();
                System.out.println(div(d, n));
                cont = false;
            }
            catch (ArithmeticException arithmeticException) {
                System.err.printf("Exception: %s\n", arithmeticException);
                System.out.println("Nao eh possivel realizar divisao por zero!");
            }
        } while (cont);
    }
}