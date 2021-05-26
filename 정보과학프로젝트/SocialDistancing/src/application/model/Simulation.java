package application.model;

import java.util.ArrayList;

import javafx.scene.layout.Pane;

public class Simulation { // Person을 가지고 실험하는 장소
	
	private ArrayList<Person> people; // java의 vector
	
	public Simulation(Pane world, int popSize) { // 초기상태
		people = new ArrayList<Person>();
		for(int i=0; i<popSize; i++) { people.add(new Person(State.SUSCEPTIBLE, world)); }
		people.add(new Person(State.INFECTED, world)); 
		draw();
	}
	
	public ArrayList<Person> getPeople(){ return people; }
	public void move() { for(Person p : people) { p.move(); }} // 이동과 그림은 Person에게 넘기기
	public void draw() { for(Person p : people) { p.draw(); }}
	
}
