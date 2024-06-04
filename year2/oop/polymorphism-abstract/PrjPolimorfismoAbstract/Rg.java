package br.uel.oo;

public class Rg extends Documento {
	
	private String orgaoEmissor;
	
	public void setOrgaoEmissor(String pOrgaoEmissor){
		this.orgaoEmissor = pOrgaoEmissor;
	}
	
	public String getOrgaoEmissor() {
		return this.orgaoEmissor;
	}
	
	public String getNrDocumentoFormatado(){
		return this.getNrDocumento()+" "+this.orgaoEmissor;
	}
}