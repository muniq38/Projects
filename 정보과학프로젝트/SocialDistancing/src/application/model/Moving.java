package application.model;

public class Moving { 
	
	public static final double SPEED = 2;
	private double dx;
	private double dy;
	
	public Moving(double dx, double dy) { this.dx = dx; this.dy = dy; }
	
	public Moving() {
		double dir = Math.random()*2*Math.PI; // random direction
		dx = Math.sin(dir); dy = Math.cos(dir);
	}
	
	public double getDx() { return this.dx; }
	public double getDy() { return this.dy; }

	public void bounceX() { dx = -dx; }
	public void bounceY() { dy = -dy; }
	
}
