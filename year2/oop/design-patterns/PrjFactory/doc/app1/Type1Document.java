package doc.app1;
import doc.framework.Document;

public class Type1Document extends Document {

	@Override
	public void open() {
		System.out.println("abrindo o documento do tipo 1!!!!");

	}

	@Override
	public void close() {
		System.out.println("fechando o documento do tipo 1!!!!");

	}

}
