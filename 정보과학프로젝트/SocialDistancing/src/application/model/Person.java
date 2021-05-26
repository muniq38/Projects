package application.model;

import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class Person { // 개발 포인트 : Person은 뭐로 이루어져 있는가?
	
	public static final int radius = 5; 
	
	private State state;
	private Position loc;
	private Moving moving;
	private Circle c;
	private Pane world;
	// 상태, 위치, 속도, 형태는 각자 만들어서 구현!
	
	public Person(State state, Pane world) { // 클래스의 기본 : Construct
		this.state = state;
		this.moving = new Moving();
		this.loc = new Position(world, radius);
		this.c = new Circle(radius, state.getColor());
		this.world = world;
		c.setStroke(Color.BLACK); // 형태가 있으면 바로 그래픽스 설정
		world.getChildren().add(c); // 형태를 world에서 그려주도록 설정!!
	}
	
	public State getState() { return this.state; } // private field - getter
	public void setState(State state) { // private field - setter
		this.state = state;
		c.setFill(state.getColor()); 
	}
	
	public void move() { loc.move(moving, world); } // 위치 클래스에 역할 넘기기
	public void draw() { // 객체에 저장되어있는대로 그리게 시키기
		c.setRadius(radius);
		c.setTranslateX(loc.getX()); 
		c.setTranslateY(loc.getY());
	}
}
