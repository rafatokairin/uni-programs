package doc.app1;
import doc.framework.Application;
import doc.framework.Document;

public class FirstApp extends Application {
	
	public static final int TYPE_1 = 1;
	public static final int TYPE_2 = 2;
	public static final int TYPE_3 = 3;
			
	@Override
	public Document createDocument(int type) {
		
		if (type == TYPE_1) {
			return new Type1Document();
		} else if (type == TYPE_2) {
			return new Type2aDocument();
		} else if (type == TYPE_3) {
			return new Type3Document();
		} else {
			System.out.println("Tipo não suportado");
			return null;
		}
	}

}
