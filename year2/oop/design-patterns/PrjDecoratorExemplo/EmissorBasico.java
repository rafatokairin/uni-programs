package br.uel.decorator;

public class EmissorBasico implements Emissor {

	@Override
	public void enviar(String mensagem) {
		// TODO Auto-generated method stub
		System.out.println("Enviando uma mensagem...");
		System.out.println(mensagem);
	}
	
	

}
