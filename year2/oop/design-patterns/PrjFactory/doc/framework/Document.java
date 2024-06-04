package doc.framework;

public abstract class Document {
	
	public abstract void open();
	
	public abstract void close();
	
	public void save() {
		System.out.println("documento salvo!");
	}
	
	public void revert() {
		System.out.println("mudança revertida!");
	}

}
