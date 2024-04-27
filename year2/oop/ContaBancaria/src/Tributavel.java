import java.math.BigDecimal;

public abstract class Tributavel extends ContaBancaria{
    abstract BigDecimal calcularTributo(BigDecimal taxaRendimento);
    public Tributavel(String cliente, String numeroConta) {
        super(cliente, numeroConta);
    }
}