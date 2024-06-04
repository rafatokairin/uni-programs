import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ControleDePontoNovo {
	public void registrar(Funcionario f, boolean entrada){
		
		LocalDateTime time = LocalDateTime.now();
		String format = time.format(DateTimeFormatter.ofPattern("dd/MM/yyy H :m :s"));
		
		if(entrada){
			System.out.println("Entrada: " + f.getNome() + " as "+ format);
		} else {
			System.out.println("Saida: " + f.getNome() + " as "+ format);
		}
		
		
	}
}
