package br.uel.adapter;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;

public class ControleDePontoNovo {
	public void registrar(Funcionario f, boolean entrada){
		
		LocalDateTime time = LocalDateTime.now();
		String format = time.format(DateTimeFormatter.ofPattern("dd/MM/yyy H :m :s"));
		
		if(entrada){
			System.out.println("Entrada: " + f.getNome() + " às "+ format);
		} else {
			System.out.println("Saída: " + f.getNome() + " às "+ format);
		}
		
		
	}
}
