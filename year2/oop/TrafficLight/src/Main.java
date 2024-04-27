import java.util.EnumSet;

public class Main {
    public static void main(String[] args) {
        for (TrafficLight color : TrafficLight.values())
            System.out.printf("%s(%s): %ds\n", color, color.getNome(), color.getTime());
    }
}