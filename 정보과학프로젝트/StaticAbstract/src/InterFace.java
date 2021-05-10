
interface Global{ // interface도 추상클래스와 비슷한 특성을 가짐
	public static int grade = 2;
	public abstract void global();
}

interface Local{
	public static int grade = 2;
	public abstract void local();
}

interface Global_21 extends Global, Local{ // 이건 가능 - 인터페이스만의 특성
	public abstract void zR();
}

class Gshs2 implements Global_21{ // 클래스-인터페이스는 implements 사용
	// Global, Local, Global21의 메소드를 모두 완성
	public void zR() { }
	public void local() { }
	public void global() { }
}

class A{ } class B{ }
// class C extends A,B{ } - 이건 불가능

public class InterFace {
	public static void main(String args[]) { }
}
