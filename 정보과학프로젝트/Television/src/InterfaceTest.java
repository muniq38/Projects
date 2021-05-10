
interface RemoteControl{ // 인터페이스 = 클래스를 만들기 위한 틀

	static final int MAX_VOLUME = 10; // 1. 상수 - 절대적/변경불가
	static final int MIN_VOLUME = 0; 
	
	// 2. 정적 메소드 - 절대적/변경불가
	public static void changeBattery(){ System.out.println("배터리 교체"); }
	// 여기까지는 외부 클래스에서도 implement 없이 쓸 수 있음 
	
	public void turnOn(); // 3. 추상메소드 - 강제적 (필수구현 틀) 
	public void turnOff();
	public void setVolume(int volume);
	
	default void setMute(boolean mute) { // 4. 디폴트메소드 - 선택적 (오버라이드 가능)
		if(mute) { System.out.println("무음처리"); }
		else { System.out.println("무음해제"); }
	} // 디폴트 메소드를 구현하지 않을 경우 제시된 구현부를 사용

}

class Television implements RemoteControl{
	
	private int volume; // 필드는 모두 클래스 내부에서 선언해야 함
	private boolean on;
	public Television(int volume, boolean on) { this.volume=volume; this.on=on; }
	
	public void turnOn() {
		if(on) System.out.println("이미 켜져 있잖아!");
		else { on=true; System.out.println("TV ON"); }
	}public void turnOff() {
		if(on) { on=false; System.out.println("TV OFF"); }
		else System.out.println("...");
	}
	
	public void setVolume(int volume) {
		if(volume > RemoteControl.MAX_VOLUME)
			this.volume = RemoteControl.MAX_VOLUME;
		else if(volume < RemoteControl.MIN_VOLUME)
			this.volume = RemoteControl.MIN_VOLUME;
		else 
			this.volume = volume;
		System.out.println("Current TV volume"+this.volume);
	}
	
}

class Audio implements RemoteControl{
	
	private int volume;
	private boolean mute;
	private boolean on;
	public Audio(int volume, boolean on, boolean mute) 
	{ this.volume=volume; this.on=on; this.mute=mute; }
	
	public void turnOn() {
		if(on) System.out.println("이미 켜져 있잖아!");
		else { on=true; System.out.println("Audio ON"); }
	}public void turnOff() {
		if(on) { on=false; System.out.println("Audio OFF"); }
		else System.out.println("...");
	}
	
	public void setVolume(int volume) {
		if(volume > RemoteControl.MAX_VOLUME)
			this.volume = RemoteControl.MAX_VOLUME;
		else if(volume < RemoteControl.MIN_VOLUME)
			this.volume = RemoteControl.MIN_VOLUME;
		else 
			this.volume = volume;
		System.out.println("Current Audio volume"+this.volume);
	}
	
	@Override
	public void setMute(boolean mute) {
		if(this.mute==mute) { System.out.println("이미 되어 있잖아!"); }
		if(mute) { System.out.println("Audio 무음처리"); }
		else { System.out.println("Audio 무음해제"); }
		this.mute=mute;
	}
	
}


public class InterfaceTest {
	public static void main(String[] args) {
		
		RemoteControl rc = null; // 사용법은 Abstract와 비슷함
		
		rc = new Television(0,false); // 자유자재로 Polymorphism 활용
		rc.turnOn();
		rc.setMute(true);
		
		rc = new Audio(0,false,false);
		rc.turnOn();
		rc.setMute(true);
		
	}
}
