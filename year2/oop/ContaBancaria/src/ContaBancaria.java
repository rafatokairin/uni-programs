import java.math.BigDecimal;

public abstract class ContaBancaria {
    protected String cliente;
    protected String numeroConta;
    protected BigDecimal saldo;
    public ContaBancaria(String cliente, String numeroConta) {
        this.cliente = cliente;
        this.numeroConta = numeroConta;
        this.saldo = BigDecimal.ZERO;
    }
    void sacar(double saque) {
        if(saldo.compareTo(BigDecimal.valueOf(saque)) >= 0) {
            this.saldo = this.saldo.subtract(BigDecimal.valueOf(saque));
        } else {
            System.out.println("Saque superou limite!");
        }
    }
    void depositar(double deposito) {
        this.saldo = this.saldo.add(BigDecimal.valueOf(deposito));
    }
    public String getCliente() {
        return cliente;
    }
    public String getNumeroConta() {
        return numeroConta;
    }
    public BigDecimal getSaldo() {
        return saldo;
    }
}
