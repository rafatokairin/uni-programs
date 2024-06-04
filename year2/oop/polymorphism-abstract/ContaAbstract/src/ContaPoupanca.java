import java.math.BigDecimal;

public class ContaPoupanca extends ContaBancaria{
    private int diaRendimento;
    public ContaPoupanca(String cliente, String numeroConta) {
        super(cliente, numeroConta);
    }
    public void calcularNovoSaldo(int taxa) {
        for (int i = 0; i < this.diaRendimento; i++)
            this.saldo = this.saldo.add(this.saldo.multiply(BigDecimal.valueOf(taxa / 100.0)));
    }
}