package br.uel.adapter;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;

public class ControleDePonto {
	
	public void registrarEntrada(Funcionario f){
		LocalDateTime time = LocalDateTime.now();
		String format = time.format(DateTimeFormatter.ofPattern("dd/MM/yyy H :m :s"));
		System.out.println("Entrada: " + f.getNome() + " �s "+ format);
	}
	
	public void registrarSaida(Funcionario f){
		LocalDateTime time = LocalDateTime.now();
		String format = time.format(DateTimeFormatter.ofPattern("dd/MM/yyy H :m :s"));
		System.out.println("Sa�da: " + f.getNome() + " �s "+ format);
	}
	

}
