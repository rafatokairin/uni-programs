public class Principal {

	public static void main(String[] args) throws InterruptedException {
		
		ControleDePonto controleDePonto = 
				new Adapter();
		Funcionario funcionario = 
				new Funcionario("Joao de Souza");
		controleDePonto.registrarEntrada(funcionario);
		Thread.sleep(3000);
		controleDePonto.registrarSaida(funcionario);
		
		
	}

}
