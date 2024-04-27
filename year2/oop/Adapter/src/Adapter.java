public class Adapter extends ControleDePonto {
    private ControleDePontoNovo novo;
    public Adapter() {
        this.novo = new ControleDePontoNovo();
    }
    public void registrarEntrada(Funcionario f) {
        this.novo.registrar(f, true);
    }
    public void registrarSaida(Funcionario f) {
        this.novo.registrar(f, false);
    }
}
