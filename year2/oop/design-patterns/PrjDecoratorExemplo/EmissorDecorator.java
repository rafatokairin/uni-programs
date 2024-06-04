package br.uel.decorator;

public abstract class EmissorDecorator implements Emissor {

	private Emissor emissor;
	
	//para criar uma instância de Decorator, 
	//eu sempre preciso passar uma instância que será a base
	public EmissorDecorator(Emissor emissor){
		this.emissor = emissor;
	}
	
	@Override
	public abstract void enviar(String mensagem);
	
	public Emissor getEmissor(){
		return this.emissor;
	}
	
	
	
	

}
