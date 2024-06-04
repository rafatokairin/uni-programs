import java.math.BigDecimal;
public class ContaPoupanca extends ContaBancaria {
    private int diaRendimento;
    public ContaPoupanca(String cliente, String numeroConta, BigDecimal saldo, int diaRendimento) {
        super(cliente, numeroConta, saldo);
        this.diaRendimento = diaRendimento;
    }
    public void calcularNovoSaldo(double taxaRendimento) {
        BigDecimal taxa = BigDecimal.valueOf(taxaRendimento / 100);
        for (int i = 0; i < this.diaRendimento; i++)
        {
            BigDecimal rendimento = getSaldo().multiply(taxa);
            BigDecimal novoSaldo = getSaldo().add(rendimento);
            setSaldo(novoSaldo);
        }
    }
}