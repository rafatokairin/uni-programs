import java.util.ArrayList;

public class Bomba {
    private int id;
    private ArrayList<Combustivel> combustiveis;
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public ArrayList<Combustivel> getCombustiveis() {
        return combustiveis;
    }
    public void setCombustiveis(ArrayList<Combustivel> combustiveis) {
        this.combustiveis = combustiveis;
    }
}