package br.uel.decorator;

public class EmissorDecoratorMsgDuplicada extends EmissorDecorator {
	
	public EmissorDecoratorMsgDuplicada(Emissor emissor){
		super(emissor);
	}

	@Override
	public void enviar(String mensagem) {
		System.out.println("mensagem duplicada...");
		this.getEmissor().enviar(this.duplicar(mensagem));

	}
	
	private String duplicar(String mensagem){
		
		return mensagem.concat("||"+mensagem);
	}

}
