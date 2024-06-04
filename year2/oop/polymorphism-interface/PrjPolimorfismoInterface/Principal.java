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
		List<Pizza> pedidos =
				new ArrayList<Pizza>();
		
		int escolha = 0;
		
		Scanner scan = new Scanner(System.in);
		
		
		
		while (escolha != -1){
			System.out.println("Digite a sua opção: 1- pedir pizza; 2-visualizar pedidos");
			escolha = scan.nextInt();
			
			if (escolha == 1){
				System.out.println("Digite a sua opção: 1- Calabresa; 2- Mussarela; 3- Romeu e Julieta");
				escolha=scan.nextInt();
				if (escolha == 1){
					
					Pizza cala = 
							new Calabresa();
					
					pedidos.add(cala);
					
				} else if (escolha == 2){
					
					Pizza mussa = 
							new Mussarela();
					
					pedidos.add(mussa);
					
				} else if (escolha == 3){
					Pizza romeu = 
							new RomeuJulieta();
					
					pedidos.add(romeu);
				}
				
				
			} else if (escolha == 2){
				Iterator<Pizza> it = 
						pedidos.iterator();
				while (it.hasNext()){
					Pizza pizza = it.next();
					pizza.preparar();
					pizza.assar();
					pizza.cobrar();
					System.out.println("=======================================");
					
				}
			}
		}
		
		

	}

}
