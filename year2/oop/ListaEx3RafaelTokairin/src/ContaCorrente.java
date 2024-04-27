import java.math.BigDecimal;
public class ContaCorrente extends ContaBancaria {
    private BigDecimal limite;
    public ContaCorrente(String cliente, String numeroConta, BigDecimal saldo, BigDecimal limite) {
        super(cliente, numeroConta, saldo);
        this.limite = limite;
    }
    @Override
    public void sacar(BigDecimal valor) {
        BigDecimal limiteNegativo = getSaldo().subtract(this.limite).negate();
        if (limiteNegativo.compareTo(valor) >= 0) {
            BigDecimal novoSaldo = getSaldo().subtract(valor);
            setSaldo(novoSaldo);
        } else {
            System.out.println("Saque superou limite!");
        }
    }
}