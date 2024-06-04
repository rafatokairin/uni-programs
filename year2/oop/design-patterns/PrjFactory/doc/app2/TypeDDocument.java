package doc.app2;

import doc.framework.Document;

public class TypeDDocument extends Document{

	@Override
	public void open() {
		System.out.println("abrindo documento tipo D");
		
	}

	@Override
	public void close() {
		// TODO Auto-generated method stub
		System.out.println("fechando documento tipo D");
	}

}
