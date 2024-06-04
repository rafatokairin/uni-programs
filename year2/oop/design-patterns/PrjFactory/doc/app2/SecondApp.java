package doc.app2;
import doc.framework.Application;
import doc.framework.Document;

public class SecondApp extends Application {
	
	public static final int TYPE_A = 1;
	public static final int TYPE_B = 2;
	public static final int TYPE_D = 3;
			
	@Override
	public Document createDocument(int type) {
		
		if (type == TYPE_A) {
			return new TypeADocument();
		} else if (type == TYPE_B) {
			return new TypeBDocument();
		} else if (type == TYPE_D) {
			return new TypeDDocument();
		} else {
			System.out.println("Tipo não suportado");
			return null;
		}
	}

}
