package test.exam.access01.package01;

public class A { // 무조건 첫 시작은 public이나 default만 가능
	// 보통 주축을 public으로 쓰고, 주축에서 쓰는 다른 클래스는 default로 사용
	
	A a1 = new A(true); // public 생성자 사용한 a1
	A a2 = new A(); // default 생성자 쓴 a2
	A a3 = new A("Hello"); // private 쓴 a3
	
	public int Field01;
	int Field02;
	private int Field03;
	
	A() { // 생성자 - Constructor
		Field01 = 1;
		Field02 = 1;
		Field03 = 1; // 자기 클래스에서는 private에도 접근가능
		
		method01();
		method02();
		method03();
	}
	
	public void method01() { } // 메소드 - Method
	void method02() { }
	private void method03() { }
	
	private A(String str) { }
	public A(boolean b) { }
	
}
