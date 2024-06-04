public class Main {
    // transforma em vetor numbers
    public static double product(double... numbers) {
        double total = 1.0;
        for (double d : numbers)
            total *= d;
        return total;
    }

    public static void main(String[] args) {
        System.out.println(product(2, 3, 4, 5));
    }
}