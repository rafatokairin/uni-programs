import java.math.BigDecimal;

public interface ContaBancaria {
    public void sacar(BigDecimal valor);
    public void depositar(BigDecimal valor);
}
