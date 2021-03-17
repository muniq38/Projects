package test.exam.access01.package01;

public class B {
	public B() {
		A a = new A(); // A() 생성자는 Field03에 접근가능하지만
		
		a.Field01 = 3;
		a.Field02 = 2; 
		
		a.method01();
		a.method02();

		// a2.Field03=1; // 상관없이 a2는 Field03에 접근할 수 없음  
		// A a1 = new A("Hello"); // private이라 접근 불가능 
	}
}
