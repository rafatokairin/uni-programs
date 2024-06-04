package br.uel.oo;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public class Principal {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		List<Documento> documentos =
				new ArrayList<Documento>();
		
		int escolha = 0;
		
		Scanner scan = new Scanner(System.in);

		while (escolha != -1){
			System.out.println("Digite a sua opcao: 1- cadastrar; 2-visualizar numeros; 3- visualizar orgaos emissores de RGs");
			escolha = scan.nextInt();
			
			if (escolha == 1){
				System.out.println("Digite a sua opcao: 1- CPF; 2- RG");
				escolha=scan.nextInt();
				if (escolha == 1){
					
					Documento doc = 
							new Cpf();
					
					System.out.println("Digite o numero do CPF");
					
					String nrCpf = 
							scan.next();
					
					doc.setNrDocumento(nrCpf);
					
					documentos.add(doc);
					
				} else if (escolha == 2){
					
					Documento doc = 
							new Rg();
					
					System.out.println("Digite o numero do RG");
					
					String nrRG = 
							scan.next();
					
					System.out.println("Digite o orgao emissor");
					
					String orgaoEmissor = 
							scan.next();
					
					doc.setNrDocumento(nrRG);
					
					((Rg)doc).setOrgaoEmissor(orgaoEmissor);
					
					documentos.add(doc);
					
				}
				
				
			} else if (escolha == 2){
				Iterator<Documento> it = 
						documentos.iterator();
				while (it.hasNext()){
					Documento documento = it.next();
					System.out.println(documento.getNrDocumentoFormatado());
				}
			} else if (escolha == 3) {
				Iterator<Documento> it = 
						documentos.iterator();
				while (it.hasNext()){
					Documento documento = it.next();
					if (documento instanceof Rg) {
						System.out.println(((Rg)documento).getOrgaoEmissor());
					}
				}
			}
		}
		
		

	}

}
