public class AccountTest {
    public static void main(String[] args) {
        // create two Account objects
        Account account1 = new Account("Jane Green", 2000);
        Account account2 = new Account("John Blue", 4000);

        // display initial value of name for each Account
        System.out.printf("account1 name is: %s balance is: $%d%n", account1.getName(), account1.getBalance());
        System.out.printf("account2 name is: %s balance is: $%d%n", account2.getName(), account2.getBalance());
    }
}
