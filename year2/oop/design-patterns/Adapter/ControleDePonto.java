import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ControleDePonto {
	
	public void registrarEntrada(Funcionario f){
		LocalDateTime time = LocalDateTime.now();
		String format = time.format(DateTimeFormatter.ofPattern("dd/MM/yyy H :m :s"));
		System.out.println("Entrada: " + f.getNome() + " as "+ format);
	}
	
	public void registrarSaida(Funcionario f){
		LocalDateTime time = LocalDateTime.now();
		String format = time.format(DateTimeFormatter.ofPattern("dd/MM/yyy H :m :s"));
		System.out.println("Saida: " + f.getNome() + " as "+ format);
	}
	

}
