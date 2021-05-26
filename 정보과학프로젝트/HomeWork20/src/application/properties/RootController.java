package application.properties;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;

public class RootController implements Initializable {

	@FXML Canvas canvas; // fxml 파일의 Canvas를 쓰고 싶어!
	GraphicsContext gc; // canvas를 다룰 때는 context를 받아서 조작해야 한다.
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		gc = canvas.getGraphicsContext2D(); 
		gc.setFill(Color.BLUE);
		gc.fillRect(0, 0, 200, 200);
		canvas.addEventHandler(MouseEvent.MOUSE_DRAGGED, (event) -> {
			gc.clearRect(event.getX()-2, event.getY()-2, 5, 5);
		}); // 이벤트추가는 canvas에 직접 - 구현 귀찮다고 씬빌더 의존하지 말것
	} // 씬빌더에 작업을 할 때 : 정적이고 기본값인 틀 디자인에만 해당
} 
