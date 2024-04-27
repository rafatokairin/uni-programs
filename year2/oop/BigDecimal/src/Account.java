// Fig. 8.16: Interest.java
// Compound-interest calculations with BigDecimal.
import java.math.BigDecimal;
import java.text.NumberFormat;

public class Account {
    private String name; // instance variable
    private BigDecimal balance;

    // Account constructor that receives two parameters
    public Account(String name, BigDecimal balance) {
        this.name = name; // assign name to instance variable name

        // validate that the balance is greater than 0.0; if it's not,
        // instance variable balance keeps its default initial value of 0.0
        if (balance.compareTo(BigDecimal.ZERO) == 1) { // if the balance is valid
            this.balance = balance; // assign it to instance variable balance
        }
    }

    // method that deposits (adds) only a valid amount to the balance
    public void deposit(double depositAmount) {
        if (depositAmount > 0.0) { // if the depositAmount is valid
            balance = balance.add(BigDecimal.valueOf(depositAmount)); // add it to the balance
        }
    }

    // method returns the account balance
    public BigDecimal getBalance() {
        return balance;
    }

    // method that sets the name
    public void setName(String name) {
        this.name = name;
    }

    // method that returns the name
    public String getName() {
        return name;
    }
}