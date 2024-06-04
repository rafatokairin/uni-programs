public class Account {
    private String name;
    private int balance;
    // constructor initializes name with parameter name and balance
    public Account(String name, int balance) { // constructor name is class name
        this.name = name;
        this.balance = balance;
    }
    // method to retrieve the name
    public String getName() {
        return name;
    }
    public int getBalance() {
        return balance;
    }
}