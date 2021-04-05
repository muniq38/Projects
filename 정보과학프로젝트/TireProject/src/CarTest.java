
import java.util.Scanner;

class Car {
	
	Tire[] T = new Tire[4];
	static Scanner input = new Scanner(System.in);
	static String[] tireName = { "FrontLeftTire", "FrontRightTire", 
			"BackLeftTire", "BackRightTire" };
	
	public Car() {
		int mRot; 
		for(int i=0; i<4; i++) {
			System.out.printf(tireName[i]+"의 남은 수명 입력 : ");
			mRot = input.nextInt();
			T[i] = new Tire(tireName[i],mRot);
		}System.out.println("새로운 차량 제작 완료!");
		System.out.println("++++++++++++++++++++");
	}
	
	public int run() { 
		System.out.println("자동차 주행중");
		for(int i=0; i<4; i++) { 
			if(!T[i].roll()){ stop(i); break; } 
		}System.out.println("+++++++++++++++++++++");
		return 0;
	}
	
	void stop(int i) { 
		System.out.println("자동차 멈춰!!");
		System.out.printf("어떤 타이어로 교체하고 싶으신가요? [A:1|B:2|기본:Else] : ");
		int X = input.nextInt();
		switch(X) {
		case 1: 
			System.out.println(tireName[i]+" A형 타이어로 교체");
			T[i] = new ATire(tireName[i], ATire.maxRotation);
			break;
		case 2:
			System.out.println(tireName[i]+" B형 타이어로 교체");
			T[i] = new BTire(tireName[i], BTire.maxRotation);
			break;
		default:
			System.out.println(tireName[i]+" 기본형 타이어로 교체");
			T[i] = new Tire(tireName[i], Tire.maxRotation);
			break;
		}
	}
}

class Tire {
	public static int maxRotation = 10;
	int Rotationleft;
	String location;
	
	public Tire(String loc, int mRot) { 
		location = loc; Rotationleft = mRot;
	}
	
	public boolean roll() { 
		Rotationleft--;
		if(Rotationleft>0) { callRotationLeft(); return true; }
		else { callWarning(); return false; }
	}
	
	void callRotationLeft() {
		System.out.println(location+" - 타이어 남은 수명 : "+Rotationleft);
	}
	
	void callWarning() {
		System.out.println(location+" ** 타이어 교체 필요 **");
	}
}

class ATire extends Tire {
	public static int maxRotation = 12;
	public ATire(String loc, int Rotation) { super(loc,Rotation); }
	@Override
	void callRotationLeft() {
		System.out.println(location+" - A 타이어 남은 수명 : "+Rotationleft);
	}
}

class BTire extends Tire {
	public static int maxRotation = 13;
	public BTire(String loc, int Rotation) { super(loc,Rotation); }
	@Override
	void callRotationLeft() {
		System.out.println(location+" - B 타이어 남은 수명 : "+Rotationleft);
	}
}

public class CarTest {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		Car Benz = new Car();
		System.out.printf("오늘은 얼마나 주행할까요? : ");
		int N = input.nextInt();
		for(int i=0; i<N; i++) Benz.run();
	}
}