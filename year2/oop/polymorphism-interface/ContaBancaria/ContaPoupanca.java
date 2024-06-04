import java.math.BigDecimal;
public class ContaPoupanca implements ContaBancaria {
    private BigDecimal saldo;
    private int diaRendimento;
    private String cliente;
    private String numeroConta;
    public ContaPoupanca(String cliente, String numeroConta, BigDecimal saldo, int diaRendimento) {
        this.diaRendimento = diaRendimento;
        this.cliente = cliente;
        this.numeroConta = numeroConta;
        this.saldo = saldo;
    }
    public void sacar(BigDecimal valor) {
        BigDecimal subValue = this.saldo.subtract(valor);
        if (subValue.compareTo(BigDecimal.ZERO) == -1)
            System.out.println("Saldo negativo!");
        else
            this.saldo = subValue;
    }
    public void depositar(BigDecimal valor) {
        if (this.saldo != null) {
            this.saldo = this.saldo.add(valor);
        } else {
            this.saldo = valor;
        }
    }
    public void calcularNovoSaldo(double taxaRendimento) {
        BigDecimal taxa = BigDecimal.valueOf(taxaRendimento / 100);
        for (int i = 0; i < this.diaRendimento; i++)
        {
            BigDecimal rendimento = this.saldo.multiply(taxa);
            BigDecimal novoSaldo = this.saldo.add(rendimento);
            this.saldo = novoSaldo;
        }
    }
    public BigDecimal getSaldo() {
        return saldo;
    }
    public String getCliente() {
        return cliente;
    }
}