public enum TrafficLight {
    RED(20,"Vermelho"),
    YELLOW(3,"Amarelo"),
    GREEN(30,"Verde");
    private final String nome;
    private final int time;
    TrafficLight(int time, String nome) {
        this.nome = nome;
        this.time = time;
    }
    public String getNome() {
        return nome;
    }
    public int getTime() {
        return time;
    }
}