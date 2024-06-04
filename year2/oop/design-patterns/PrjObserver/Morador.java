package br.uel.observer;

public class Morador implements PortaObserver {
	
	public Morador(String nome){
		this.nome = nome;
	}
	
	private String nome;

	@Override
	public void update(Porta porta) {
		
		System.out.println("Notificando o morador "
				+this.nome+" que a porta está aberta");
		System.out.println("porta aberta? "
				+porta.isPortaAberta());

	}

}
