
final class Hi { }
// class Hi2 extends Hi{ } - final이므로 X

abstract class Paper { // 미완성 클래스 
	abstract void wri(); // 미완성 메소드 wri - 구현부 작성할 수 없음
	void asdf(int a) { System.out.println(a); }
} 

class GradPaper extends Paper{ // 미완성 클래스의 미완성 메소드는 자식이 물려받아 완성
	@Override
	void wri() { System.out.println("GradPaper"); } // 완성 자식 클래스라면 필수!!
	int go(int a) { return a*a; }  // 맘껏 연장 가능, asdf는 다시 쓰지 않아도 됨
	// abstract void wri(); X - 완성 클래스에 미완성 메소드를 넣을 수 없음
	// void wri(); X - 구현부까지 작성해야 완성된 메소드
}

class BasicPaper extends Paper{ 
	@Override
	void wri() { System.out.println("BasicPaper"); } 
}

abstract class FPaper extends Paper{ }
// 만약 부모의 미완성 클래스를 완성시키지 못할 경우 여기에도 abstract를 붙여야 함

public class Hello {
	
	final static int a=10; // static final = constant
	static int width=200;
	static int height=100; // static field (Hello.height)
	static int max(int a, int b) { return a>b?a:b; } // static method (Hello.max)
	
	void write(int a, int b) { System.out.println(max(a,b)); }
	// static method는 자유롭게 사용 가능
	
	public static void main(String args[]) {
		
		max(1,2); // write(1,2); X - static에서 nonstatic 호출 불가능
		Hello test = new Hello();
		test.write(1,2);
		
		// Paper P = new Paper(); X - abstract는 constructor 사용 불가능
		GradPaper P1 = new GradPaper();
		BasicPaper P2 = new BasicPaper();
		Paper[] P = {P1,P2}; // polymorphism 활용
		for(Paper p : P) { p.wri(); }
		
	}
}

