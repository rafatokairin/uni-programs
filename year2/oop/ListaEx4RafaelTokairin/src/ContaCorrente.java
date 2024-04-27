import java.math.BigDecimal;
public class ContaCorrente implements ContaBancaria {
    private BigDecimal saldo;
    private BigDecimal limite;
    private String cliente;
    private String numeroConta;
    public ContaCorrente(String cliente, String numeroConta, BigDecimal saldo, BigDecimal limite) {
        this.saldo = saldo;
        this.limite = limite;
        this.cliente = cliente;
        this.numeroConta = numeroConta;
    }
    public void sacar(BigDecimal valor) {
        BigDecimal limiteNegativo = this.saldo.subtract(this.limite).negate();
        if (limiteNegativo.compareTo(valor) >= 0) {
            BigDecimal novoSaldo = this.saldo.subtract(valor);
            this.saldo = novoSaldo;
        } else {
            System.out.println("Saque superou limite!");
        }
    }
    public void depositar(BigDecimal valor) {
        if (this.saldo != null) {
            this.saldo = this.saldo.add(valor);
        } else {
            this.saldo = valor;
        }
    }
    public BigDecimal getSaldo() {
        return saldo;
    }
    public String getCliente() {
        return cliente;
    }
}
