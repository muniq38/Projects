import test.exam.access01.package01.A;

public class Main {
	public static void main(String[] args) {
		Point p1 = new Point(1.0,3.0);
		Point p2 = new Point();
		
		p1.increaseX(5);
		p1.decreaseY(10);
		
		p2.increaseX(20);
		p2.decreaseY(5);
		
		p1.printPoint();
		p2.printPoint();
		
		A a1 = new A(true); // public 접근 가능
		// A a2 = new A(); // A()가 default고 다른 패키지에서 접근 불가능
	}
	
	public static class Point{
		static double Max = 100.0;
		double X, Y;
		Point(){ X=0.0; Y=0.0; } // 생성자
		Point(double x, double y) { X=x; Y=y; }
		void increaseX(double dx) { X += dx; }
		void increaseY(double dy) { Y += dy; }
		void decreaseX(double dx) { X -= dx; }
		void decreaseY(double dy) { Y -= dy; }
		void printPoint() {
			System.out.println(X+" "+Y);
		}
	}
	
	public static class Add{
		public int add(int x, int y) { return x+y; }
		public double add(double x, double y) { return x+y; }
		public int add(int x, int y, int z) { return x+y+z; }
		// 메소드 오버로딩 (매개변수에 따라 다양하게 설정 가능)
	}
}
