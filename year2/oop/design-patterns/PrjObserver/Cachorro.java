package br.uel.observer;

public class Cachorro implements PortaObserver {

	@Override
	public void update(Porta porta) {
		System.out.println(porta.isPortaAberta());
		System.out.println("au au au au");

	}

}
