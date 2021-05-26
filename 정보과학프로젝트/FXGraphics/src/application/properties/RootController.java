package application.properties;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.effect.MotionBlur;
import javafx.scene.paint.Color;
import javafx.scene.paint.CycleMethod;
import javafx.scene.paint.LinearGradient;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;
import javafx.scene.shape.Rectangle;

public class RootController implements Initializable {

	@FXML Canvas canvas; // fxml 파일의 Canvas를 쓰고 싶어!
	@FXML Rectangle rect; // 아니면 따로 도형을 쓸수도 있음
	GraphicsContext gc; // canvas를 다룰 때는 context를 받아서 조작해야 한다.
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		gc = canvas.getGraphicsContext2D(); 
		//Image image = new Image(getClass().getResourceAsStream("up.jpg"));
		//gc.drawImage(image, 100, 100); // 이미지를 배경으로 넣고 싶을때
		draw(); drawGrad(); // context 받아서 그리기
	}

	private void drawGrad() {
		Stop[][] stop = new Stop[2][];
		stop[0] = new Stop[] {
			new Stop(0,Color.RED),
			new Stop(1,Color.BLUE) };
		stop[1] = new Stop[] {
			new Stop(0,Color.YELLOW),
			new Stop(1,Color.RED) };
		
		LinearGradient lg = new LinearGradient(0,0,1,0, true, CycleMethod.NO_CYCLE, stop[0]);
		gc.setFill(lg); // Gradient는 색에 해당
		gc.fillRect(50, 50, 100, 100);
		
		RadialGradient rg = new RadialGradient(0,0,100,100,100, false, CycleMethod.NO_CYCLE, stop[1]);
		gc.setFill(rg);
		gc.fillOval(75, 75, 100, 100);
	}

	private void draw() {
		gc.setFill(Color.AQUAMARINE); // 페인트 설정 = setFill
		gc.setStroke(Color.rgb(123, 213, 100)); // 선 설정 = setStroke
		gc.fillRect(30, 30, 150, 150); // 칠하기 = fill
		gc.strokeOval(90, 90, 50, 50); // 그리기 = stroke
		
		gc.setFill(Color.BLACK);
		gc.fillText("iPad Pro", 80, 20); 
		
		rect.setEffect(new MotionBlur(0,90));
		rect.setStroke(Color.BLUE); 
		// rect.setFill : FXML 파일에서 직접 다뤘음 - 유연한 사고!
	}
	
}
