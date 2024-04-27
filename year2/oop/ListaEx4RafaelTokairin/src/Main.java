import java.math.BigDecimal;
public class Main {
    public static void main(String[] args) {
        ContaBancaria cc = new ContaCorrente("Maria", "54321", BigDecimal.valueOf(2000.0), BigDecimal.valueOf(500.0));
        ContaBancaria cp = new ContaPoupanca("Joao", "12345", BigDecimal.valueOf(1000.0), 2);
        ContaBancaria ci = new ContaInvestimento("Jose", "67890", BigDecimal.valueOf(500.0));
        // Tentando sacar mais do que o saldo + limite
        cc.sacar(BigDecimal.valueOf(2500.0));
        if (cp instanceof ContaPoupanca) {
            ((ContaPoupanca) cp).calcularNovoSaldo(5);
        } else {
            System.out.println("A conta nao eh tipo ContaPoupanca");
        }
        cc.depositar(BigDecimal.valueOf(500.0));
        cp.sacar(BigDecimal.valueOf(200.0));
        // Exibindo os saldos das contas
        System.out.println("Saldo da conta " + ((ContaCorrente)cc).getCliente() + ": " + ((ContaCorrente)cc).getSaldo());
        System.out.println("Saldo da conta " + ((ContaPoupanca)cp).getCliente() + ": " + ((ContaPoupanca)cp).getSaldo());
        System.out.println("Saldo da conta " + ((ContaInvestimento)ci).getCliente() + ": " + ((ContaInvestimento)ci).getSaldo());
        // Calculando taxa ContaInvestimento
        ((Tributavel)ci).calcularTributo(10);
        ((ContaInvestimento)ci).calcularTaxaAdministracao(5);
    }
}