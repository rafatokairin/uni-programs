package doc.app1;
import doc.framework.Document;

public class Type2aDocument extends Document {

	@Override
	public void open() {
		System.out.println("abrindo o documento do tipo 2a!!!!");

	}

	@Override
	public void close() {
		System.out.println("encerrando o documento do tipo 2a!!!!");

	}

}
