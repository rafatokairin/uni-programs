package br.uel.oo;

public class Cpf extends Documento {
	@Override
	public String getNrDocumentoFormatado() {
		if (this.formatar(this.getNrDocumento()) ==  null){
			return null;
		} else {
			return this.formatar(this.getNrDocumento());
		}
	}
	
	private String formatar(String pNrDocumento){
		if (pNrDocumento.length() == 11){
			return pNrDocumento.substring(0,3)+
					"."+pNrDocumento.substring(3,6)+
					"."+pNrDocumento.substring(6,9)+
					"-"+pNrDocumento.substring(9,11);
		} else {
			System.out.println("nao eh um CPF");
			return null;
		}
	}
}
