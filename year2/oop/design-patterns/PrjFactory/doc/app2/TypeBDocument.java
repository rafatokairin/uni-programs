package doc.app2;
import doc.framework.Document;

public class TypeBDocument extends Document {

	@Override
	public void open() {
		System.out.println("abrindo o documento do tipo B!!!!");

	}

	@Override
	public void close() {
		System.out.println("fechando o documento do tipo B!!!!");

	}

}
