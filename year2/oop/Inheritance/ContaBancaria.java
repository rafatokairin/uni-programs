import java.math.BigDecimal;
public class ContaBancaria {
    private String cliente;
    private String numeroConta;
    private BigDecimal saldo;
    public ContaBancaria(String cliente, String numeroConta, BigDecimal saldo) {
        this.cliente = cliente;
        this.numeroConta = numeroConta;
        this.saldo = saldo;
    }
    public BigDecimal getSaldo() {
        return saldo;
    }
    public String getCliente() {
        return cliente;
    }
    public void setSaldo(BigDecimal saldo) {
        this.saldo = saldo;
    }
    public String getNumeroConta() {
        return numeroConta;
    }
    public void sacar(BigDecimal valor) {
        BigDecimal subValue = this.saldo.subtract(valor);
        if (subValue.compareTo(BigDecimal.ZERO) == -1)
            System.out.println("Saldo negativo!");
        else
            this.saldo = subValue;
    }
    public void depositar(BigDecimal valor) {
        this.saldo = this.saldo.add(valor);
    }
}