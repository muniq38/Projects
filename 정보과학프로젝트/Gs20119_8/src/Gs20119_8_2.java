
class Car{
	int speed = 10;
	int direction = 20;
	String code = "1234567";
	static String brand = "HYUNDAI";
	
	Car(int speed, int direction){
		this.speed=speed; this.direction=direction; }
	Car(int speed){ this.speed=speed; }
	Car(){ }
	
	int getSpeed() { return speed; }
	int getDir() { return direction; }
	String getCode() { return code; }
	String getBrand() { return brand; }
	
	static void setBrand(String brand) { Car.brand = brand; }
	void setSpeed(int speed) { this.speed = speed; }
	void setDir(int direction) { this.direction = direction; }
	void setCode(String code) { this.code = code; }
	
	void print1() {
		System.out.println("Car@"+code+" - "+"속도 : "+speed+", 방향 : "+direction); }
}

public class Gs20119_8_2 {
	public static void main(String[] args) {
		Car c1 = new Car(40,30);
		Car c2 = new Car(60,30);
		Car c3 = new Car();
		
		c1.setCode("1cfe174");
		c2.setCode("da89a7");
		c3.setCode("1833c9c");
		
		c1.print1();
		c2.print1();
		c3.print1();
		
		Car.setBrand("KIA");
	}
}
