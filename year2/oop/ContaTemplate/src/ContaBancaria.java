public abstract class ContaBancaria {
	
	private double saldo;
	
	public void depositar(double valor){
		this.saldo += valor; 
		this.saldo -= this.calcularTaxa();
	}
	
	public void sacar(double valor){
		this.saldo -= valor;
		this.saldo -= this.calcularTaxa();
	}
	
	public abstract double calcularTaxa();

	public double getSaldo() {
		return saldo;
	}
	
	

}
