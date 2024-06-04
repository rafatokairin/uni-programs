package br.uel.observer;

import java.util.HashSet;
import java.util.Set;

public class Porta {
	
	private boolean portaAberta = false;
	
	Set<PortaObserver> interessados = new HashSet<PortaObserver>();
	
	public void adicionarInteressado(PortaObserver portaObserver){
		interessados.add(portaObserver);
	}
	
	public void removerInteressado(PortaObserver portaObserver){
		interessados.remove(portaObserver);
	}

	public boolean isPortaAberta() {
		return portaAberta;
	}

	public void setPortaAberta(boolean portaAberta) {
		this.portaAberta = portaAberta;
		if (this.portaAberta) {
			this.notificar();
		}
		
	}
	
	public void notificar() {
		
		for(PortaObserver interessado : this.interessados){
			interessado.update(this);
		}
		
	}
	
	

}
