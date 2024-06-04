package br.uel.oo;

public class Mussarela implements Pizza{

	@Override
	public void preparar() {
		System.out.println("molho, mussarela");
		
	}

	@Override
	public void assar() {
		System.out.println("12 minutos...");
		
	}

	@Override
	public void cobrar() {
		System.out.println("R$ 30,00");
		
	}
	
	

}
