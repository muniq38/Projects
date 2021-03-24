
class A {
	public int a;
	protected int b;
	int c;
	private int d=1;
	A(){ System.out.println("A-init"+d); }
	void a1() { System.out.println("A-a1"); }
	void a2() { System.out.println("A-a2"); }
}

class B extends A {
	B(){ 
		super(); // super == BÀÇ ºÎ¸ð == A
		System.out.println("B-init"); 
	}void b1() {  }
	void a1() { 
		System.out.println("B-a1");
		super.a1(); // A.a1()
	}
}

public class Inherit {
	public static void main(String[] args) {
		B obj = new B(); 
		obj.a1();
	}
}
