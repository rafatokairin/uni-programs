package br.uel.decorator;

public class Principal {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		String mensagem = "teste";
		
		Emissor b = new EmissorBasico();
		
		Emissor c = new EmissorDecoratorComCriptografia(b);
		
		Emissor d = new EmissorDecoratorMsgDuplicada(c);
		
		Emissor dd = new EmissorDecoratorMsgDuplicada(d);
		
		dd.enviar(mensagem);
		
		
		
		
		
		
		
		
		
		
//		Emissor emissor = new EmissorBasico();
//		
//		System.out.println("======== Emissor básico");
//		emissor.enviar(mensagem);
		
		
//		Emissor emissorCript = new EmissorDecoratorComCriptografia(
//				new EmissorBasico());
//		
//		System.out.println("======== Emissor com criptografia");
//		emissorCript.enviar(mensagem);
//		
//		System.out.println("======== Emissor com duas criptografias");
//		
//		Emissor emissorCript2 = 
//				new EmissorDecoratorComCriptografia(
//						new EmissorDecoratorComCriptografia(new EmissorBasico()));
//		
//		emissorCript2.enviar("teste2");
//		
//		System.out.println("======== Emissor duplicador");
//		
//		Emissor emissordupl = new EmissorDecoratorMsgDuplicada(new EmissorBasico());
//		emissordupl.enviar("Acorda, pessoal!");
//		
		
		

	}

}
