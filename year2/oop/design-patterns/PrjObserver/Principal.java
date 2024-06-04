package br.uel.observer;

public class Principal {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Porta porta = new Porta();
		
		PortaObserver morador1 = new Morador("João");
		PortaObserver morador2 = new Morador("Maria");
		
		PortaObserver cach1 = new Cachorro();
		
		porta.adicionarInteressado(morador1);
		porta.adicionarInteressado(morador2);
		porta.adicionarInteressado(cach1);
		
		porta.setPortaAberta(true);
		
		porta.removerInteressado(morador2);
		
		porta.setPortaAberta(true);
		
		

	}

}
