import doc.app1.FirstApp;
import doc.app2.SecondApp;
import doc.framework.Application;
import doc.framework.Document;

public class Principal {

	public static void main(String[] args) {
		
		Application app1 = new FirstApp();
		
		Document doc = app1.createDocument(FirstApp.TYPE_2);
		
		doc.open();
		
		Application app2 = new SecondApp();
		
		Document doc2 = app2.createDocument(SecondApp.TYPE_B);
		
		Document docNovo = app2.createDocument(SecondApp.TYPE_D);
		
		doc2.open();

	}

}
