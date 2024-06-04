import java.math.BigDecimal;
public class ContaCorrente extends ContaBancaria{
    private BigDecimal limite;
    public ContaCorrente(String cliente, String numeroConta, BigDecimal limite) {
        super(cliente, numeroConta);
        this.limite = limite;
    }
    @Override
    public void sacar(double valor) {
        BigDecimal total = this.limite.add(this.saldo);
        if (BigDecimal.valueOf(valor).compareTo(total) <= 0) {
            this.saldo = this.saldo.subtract(BigDecimal.valueOf(valor));
        } else {
            System.out.println("Saque superou limite!");
        }
    }
}