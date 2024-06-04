import java.security.SecureRandom;
import java.util.Random;

public class Gerente {
    public String nome;
    private double salario;

    public Gerente(double pSalario) {
        this.salario = pSalario;
    }

    public double getSalario() {
        return this.salario;
    }

    public void aumentarSalario() {
        this.salario =
                this.salario * 1.1;
    }

    public void aumentarSalario(double aumento) {
        this.salario = this.salario * aumento;
    }
}