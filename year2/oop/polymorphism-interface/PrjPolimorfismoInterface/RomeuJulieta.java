package br.uel.oo;

public class RomeuJulieta implements Pizza {

	@Override
	public void preparar() {
		System.out.println("goiabada, queijo");

	}

	@Override
	public void assar() {
		System.out.println("15 minutos");

	}

	@Override
	public void cobrar() {
		System.out.println("R$ 40,00");

	}

}
