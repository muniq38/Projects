package scenebuild_event;

import java.util.Random;
import javafx.event.ActionEvent;
import javafx.fxml.FXML; // @FXML 사용
import javafx.scene.control.Label;
import javafx.scene.control.Button;

public class MainController { 
	
	@FXML // 반드시 추가
	private Label redMessage; // FXML에서 대상의 fx:id와 일치해야 함
	
	@FXML
	private Label greenMessage;
	
	@FXML
	private Label pinkMessage;
	
	public void generateRandom(ActionEvent event) { // 버튼의 OnAction에 들어감
		String value = ((Button)event.getSource()).getText();
		Random rand = new Random();
		int myrand = rand.nextInt(50)+1;
		if(value.equals("당")) redMessage.setText(Integer.toString(myrand));
		else if(value.equals("찌")) greenMessage.setText(Integer.toString(myrand));
		else if(value.equals("머뚱")) pinkMessage.setText(Integer.toString(myrand));
	}
	
}
