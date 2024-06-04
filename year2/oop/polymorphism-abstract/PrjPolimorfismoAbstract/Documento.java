package br.uel.oo;

public abstract class Documento {
	private String nrDocumento;
	public void setNrDocumento(String pNrDocumento){
		this.nrDocumento = pNrDocumento;
	}
	public String getNrDocumento(){
		return this.nrDocumento;
	}
	public abstract String getNrDocumentoFormatado();
}
