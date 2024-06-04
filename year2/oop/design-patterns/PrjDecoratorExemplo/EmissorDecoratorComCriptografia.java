package br.uel.decorator;

public class EmissorDecoratorComCriptografia extends EmissorDecorator {

	public EmissorDecoratorComCriptografia(Emissor emissor){
		super(emissor);
	}
	
	@Override
	public void enviar(String mensagem) {
		System.out.println("Enviando mensagem criptografada");
		this.getEmissor().enviar(criptografar(mensagem));

	}
	
	private String criptografar(String mensagem){
		String mensagemCriptografada = 
				new StringBuilder(mensagem).reverse().toString();
		return mensagemCriptografada;
	}

}
