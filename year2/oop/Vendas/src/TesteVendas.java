import java.security.SecureRandom;

public class TesteVendas {

	public static void main(String[] args) {
		SecureRandom r = new SecureRandom();
		
		int cont = 0;
		
		int[] vendas = new int[6];
		
		while (cont < 10) {
			double valorVenda = r.nextDouble()*700;
			
			System.out.println(valorVenda);
			
			if (valorVenda < 600) {
				System.out.println("posição incrementada: "+(int)valorVenda/100);
				vendas[(int)valorVenda/100]++;
			} else {
				System.out.println("posição incrementada: 5");
				vendas[5]++;
			}
			
			cont++;
		}
		
		for (int i = 0; i < 6; i++) {
			System.out.println(vendas[i]);
		}

	}

}
