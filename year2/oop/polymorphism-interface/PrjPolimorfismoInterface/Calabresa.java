package br.uel.oo;

public class Calabresa implements Pizza{

	@Override
	public void preparar() {
		System.out.println("molho, mussarela, calabresa, cebola");
	}

	@Override
	public void assar() {
		System.out.println("15 minutos...");
		
	}

	@Override
	public void cobrar() {
		System.out.println("R$ 35,00");
		
	}
	
}
