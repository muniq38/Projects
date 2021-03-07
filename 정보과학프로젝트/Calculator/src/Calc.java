// 20119 최재열 정보과학프로젝트 
public class Calc {
	public static void main(String[] args) {
		Calculator myCal = new Calculator();
		System.out.println("20 + 10 = " + myCal.add(20, 10));
		System.out.println("20 - 10 = " + myCal.sub(20, 10));
		System.out.println("20 * 10 = " + myCal.mul(20, 10));
		System.out.println("20 / 10 = " + myCal.div(20, 10));
	}
	
	public static class Calculator{
		Calculator(){ System.out.println("Initialized"); }
		int add(int a, int b) { return a+b; }
		int sub(int a, int b) { return a-b; }
		int div(int a, int b) { return a/b; }
		int mul(int a, int b) { return a*b; }
	}
}
