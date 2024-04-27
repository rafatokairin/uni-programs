public class Main {

    public static void main(String[] args) {
        int total = 0;
        for (String elemento : args) {
            total+=Integer.parseInt(elemento);
        }
        System.out.println(total);
    }
}