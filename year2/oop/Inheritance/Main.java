import java.util.LinkedList;
import java.math.BigDecimal;
public class Main {
    public static void main(String[] args) {
        LinkedList<ContaBancaria> listaContas = new LinkedList<>();
        // Criando uma conta poupanca
        ContaPoupanca cp = new ContaPoupanca("João", "12345", BigDecimal.valueOf(1000.0), 2);
        // Simulando rendimento de 0.5%
        cp.calcularNovoSaldo(5);
        // Criando uma conta corrente
        ContaCorrente cc = new ContaCorrente("Maria", "54321", BigDecimal.valueOf(2000.0), BigDecimal.valueOf(500.0));
        // Tentando sacar mais do que o saldo + limite
        cc.sacar(BigDecimal.valueOf(2500.0));
        // Realizando operacoes na conta corrente e na conta poupanca
        cc.depositar(BigDecimal.valueOf(500.0));
        cp.sacar(BigDecimal.valueOf(200.0));
        // Adicionando contas na lista
        listaContas.add(cp);
        listaContas.add(cc);
        // Exibindo os saldos das contas
        System.out.println("Saldo da conta " + cc.getCliente() + ": " + cc.getSaldo());
        System.out.println("Saldo da conta " + cp.getCliente() + ": " + cp.getSaldo());
        // Buscando conta pelo numero
        String numeroContaBuscada = "54321";
        int indiceConta = -1;
        for (ContaBancaria conta : listaContas) {
            if (conta.getNumeroConta().equals(numeroContaBuscada)) {
                indiceConta = listaContas.indexOf(conta);
                break;
            }
        }
        // Exibindo se encontrou conta
        if (indiceConta != -1)
            System.out.println("Conta encontrada!");
        else
            System.out.println("Conta não encontrada.");
    }
}