package br.uel.adapter;

public class TomadaAdapter extends TomadaDeDoisPinos {
	
	private TomadaDeTresPinos tomadaDeTresPinos;
	
	public TomadaAdapter(){
		tomadaDeTresPinos = new TomadaDeTresPinos();
	}
	
	public void ligarNaTomadaDeDoisPinos(){
		this.tomadaDeTresPinos.ligarNaTomadaDeTresPinos();
	}

}
