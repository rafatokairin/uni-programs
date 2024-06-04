import java.math.BigDecimal;
public class ContaInvestimento extends Tributavel{
    public ContaInvestimento(String cliente, String numeroConta) {
        super(cliente, numeroConta);
    }
    public void calcularNovoSaldo(int taxaRendimento) {
        this.saldo = this.saldo.add(this.saldo.multiply(BigDecimal.valueOf(taxaRendimento / 100.0)));
    }
    public BigDecimal calcularTaxaAdministracao(int taxaRendimento) {
        BigDecimal novoSaldo = this.saldo.add(this.saldo.multiply(BigDecimal.valueOf(taxaRendimento / 100.0)));
        return (novoSaldo.subtract(this.saldo).multiply(BigDecimal.valueOf(0.01)));
    }
    @Override
    public BigDecimal calcularTributo(BigDecimal taxaRendimento) {
        BigDecimal novoSaldo = this.saldo.add(this.saldo.multiply(taxaRendimento.divide(BigDecimal.valueOf(100))));
        return (novoSaldo.subtract(this.saldo).multiply(BigDecimal.valueOf(0.005)));
    }
}