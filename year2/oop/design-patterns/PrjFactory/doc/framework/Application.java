package doc.framework;
import java.util.LinkedList;

public abstract class Application {
	
	private LinkedList<Document> docs;
	
	public abstract Document createDocument(int type);
	
	public void newDocument(int type) {
		Document doc = this.createDocument(type);
		docs.add(doc);
	}
	
	public void openDocument(int index) {
		
		docs.get(index).open();
		
	}

}
