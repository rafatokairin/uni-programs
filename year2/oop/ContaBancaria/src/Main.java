import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        ArrayList<ContaBancaria> conta = new ArrayList<>();
        Scanner v = new Scanner(System.in);
        int opcao;
        do {
            opcao = menu(v);
            switch(opcao) {
                case 1:
                    cadastrarConta(conta, v);
                    break;
                case 2:
                    sacarValor(conta, v);
                    break;
                case 3:
                    atualizarPoupanca(conta, v);
                    break;
                case 4:
                    depositarValor(conta, v);
                    break;
                case 5:
                    mostrarSaldo(conta);
                    break;
                case 6:
                    calcularTributos(conta, v);
                    break;
                case 7:
                    calcularTaxa(conta, v);
                    break;
                case 8:
                    System.out.println("Finalizando...");
                    break;
                default:
                    System.out.println("Opcao invalida!");
                    break;
            }
        } while(opcao != 8);
    }
    public static int menu(Scanner v) {
        System.out.print("\n1. Cadastrar\n2. Sacar\n3. Atualizar conta poupanca\n4. Depositar\n5. Mostrar saldo\n6. Calcular tributos\n7. Calcular taxa de administracao\n8. Sair\n");
        return v.nextInt();
    }
    public static void cadastrarConta(ArrayList<ContaBancaria> contas, Scanner v) {
        System.out.print("1. Conta Corrente\n2. Conta Poupanca\n3. Conta Investimento\n");
        int tipo = v.nextInt();
        v.nextLine();
        System.out.print("Nome do cliente:\n");
        String cliente = v.nextLine();
        System.out.print("Numero da conta:\n");
        String numConta = v.next();
        if(tipo == 1) {
            System.out.print("Valor do limite:\n");
            BigDecimal limite = v.nextBigDecimal();
            ContaBancaria corrente = new ContaCorrente(cliente, numConta, limite);
            contas.add(corrente);
        } else if(tipo == 2) {
            ContaBancaria poupanca = new ContaPoupanca(cliente, numConta);
            contas.add(poupanca);
        } else if(tipo == 3) {
            ContaBancaria investimento = new ContaInvestimento(cliente, numConta);
            contas.add(investimento);
        } else System.out.println("Opcao invalida!");
    }
    public static void sacarValor(ArrayList<ContaBancaria> contas, Scanner v) {
        if(!contas.isEmpty()) {
            System.out.print("Digite o numero da conta:\n");
            String numConta = v.next();
            ContaBancaria conta = encontrarConta(contas, numConta);
            if (conta == null) {
                System.out.println("Conta nao encontrada!");
                return;
            }
            System.out.print("Digite valor do saque:\n");
            double saque = v.nextDouble();
            conta.sacar(saque);
        } else System.out.println("Nenhuma conta aberta!");
    }
    public static void atualizarPoupanca(ArrayList<ContaBancaria> contas, Scanner v) {
        if(!contas.isEmpty()) {
            System.out.print("Digite numero da conta:\n");
            String numConta = v.next();
            ContaBancaria conta = encontrarConta(contas, numConta);
            if (conta == null) {
                System.out.println("Conta nao encontrada!");
                return;
            }
            if(conta instanceof ContaPoupanca) {
                System.out.print("Digite taxa de rendimento:\n");
                int rendimento = v.nextInt();
                ((ContaPoupanca)conta).calcularNovoSaldo(rendimento);
            } else System.out.println("Conta nao eh tipo poupanca");

        } else System.out.println("Nenhuma conta aberta!");
    }
    public static void depositarValor(ArrayList<ContaBancaria> contas, Scanner v) {
        if(!contas.isEmpty()) {
            System.out.print("Digite numero da conta:\n");
            String numConta = v.next();
            ContaBancaria conta = encontrarConta(contas, numConta);
            if (conta == null) {
                System.out.println("Conta nao encontrada!");
                return;
            }
            System.out.print("Digite valor do deposito:\n");
            double deposito = v.nextDouble();
            conta.depositar(deposito);
        } else System.out.println("Nenhuma conta aberta!");
    }
    public static void mostrarSaldo(ArrayList<ContaBancaria> contas) {
        if(!contas.isEmpty()) {
            Iterator<ContaBancaria> it = contas.iterator();
            while (it.hasNext()) {
                ContaBancaria conta = it.next();
                System.out.println("Cliente: " + conta.getCliente() + "\t Numero da conta: " + conta.getNumeroConta() + "\t Saldo: R$" + conta.getSaldo());
            }
        } else System.out.println("Nenhuma conta aberta!");
    }
    public static void calcularTributos(ArrayList<ContaBancaria> contas, Scanner v) {
        if(!contas.isEmpty()) {
            System.out.print("Digite numero da conta:\n");
            String numConta = v.next();
            ContaBancaria conta = encontrarConta(contas, numConta);
            if (conta == null) {
                System.out.println("Conta nao encontrada!");
                return;
            }
            if(conta instanceof ContaInvestimento) {
                System.out.print("Digite taxa de rendimento:\n");
                BigDecimal rendimento = v.nextBigDecimal();
                System.out.println("Tributo: R$" + ((ContaInvestimento)conta).calcularTributo(rendimento));
            } else System.out.println("Conta nao eh tipo investimento!");
        } else System.out.println("Nenhuma conta aberta!");
    }
    public static void calcularTaxa(ArrayList<ContaBancaria> contas, Scanner v) {
        if(!contas.isEmpty()) {
            System.out.print("Digite numero de sua conta:\n");
            String numConta = v.next();
            ContaBancaria conta = encontrarConta(contas, numConta);
            if (conta == null) {
                System.out.println("Conta nao encontrada!");
                return;
            }
            if(conta instanceof ContaInvestimento) {
                System.out.print("Digite taxa de rendimento:\n");
                int rendimento = v.nextInt();
                System.out.println("Taxa de administracao: R$" + ((ContaInvestimento)conta).calcularTaxaAdministracao(rendimento));
            } else System.out.println("Conta nao eh tipo investimento!");
        } else System.out.println("Nenhuma conta aberta!");
    }
    private static ContaBancaria encontrarConta(ArrayList<ContaBancaria> contas, String numeroConta) {
        for (ContaBancaria conta : contas)
            if (conta.getNumeroConta().equals(numeroConta))
                return conta;
        return null;
    }
}