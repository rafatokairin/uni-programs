
public class Main {
    public static void main(String[] args) {
        // TODO Auto-generated method stub

        Gerente g1 = new Gerente(10000);

        System.out.println("salario inicial: "+
                g1.getSalario());

        g1.aumentarSalario();

        System.out.println("salario apos primeiro aumento: "+
                g1.getSalario());

        g1.aumentarSalario(1.05);

        System.out.println("salario apos segundo aumento: "+
                g1.getSalario());
    }
}