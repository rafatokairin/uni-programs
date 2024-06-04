package br.uel.singleton;

public class Principal {

	public static void main(String[] args) {
		
		Configuracao c = Configuracao.getInstance();
		
		System.out.println("Time zone: "+ c.getPropriedades("time-zone"));
		System.out.println("Currency: "+c.getPropriedades("currency-code"));
		
		

	}

}
