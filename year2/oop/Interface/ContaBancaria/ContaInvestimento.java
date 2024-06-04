import java.math.BigDecimal;

public class ContaInvestimento implements ContaBancaria, Tributavel {
    private String cliente;
    private String numeroConta;
    private BigDecimal saldo;
    public ContaInvestimento(String cliente, String numeroConta, BigDecimal saldo) {
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
        BigDecimal rendimento = this.saldo.multiply(taxa);
        BigDecimal novoSaldo = this.saldo.add(rendimento);
        this.saldo = novoSaldo;
    }
    public void calcularTaxaAdministracao(double taxaRendimento) {
        BigDecimal taxa = BigDecimal.valueOf(taxaRendimento / 100);
        BigDecimal rendimento = this.saldo.multiply(taxa);
        BigDecimal novoSaldo = this.saldo.add(rendimento);
        System.out.println("Taxa administracao: " + novoSaldo.multiply(BigDecimal.valueOf(0.01)));
    }
    public void calcularTributo(double taxaRendimento) {
        BigDecimal taxa = BigDecimal.valueOf(taxaRendimento / 100);
        BigDecimal rendimento = this.saldo.multiply(taxa);
        BigDecimal novoSaldo = this.saldo.add(rendimento);
        System.out.println("Tributo: " + novoSaldo.multiply(BigDecimal.valueOf(0.005)));
    }
    public BigDecimal getSaldo() {
        return saldo;
    }
    public String getCliente() {
        return cliente;
    }
}