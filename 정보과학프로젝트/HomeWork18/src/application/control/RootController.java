package application.control;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.Initializable;

public class RootController implements Initializable {

	@Override
	public void initialize(URL location, ResourceBundle resources) { }
	
	public void appleBtn(ActionEvent event) { System.out.println("APPLE"); }
	
	public void pearBtn(ActionEvent event) { System.out.println("PEAR"); }
	
}

// 컨트롤러 : UI에서 생긴 유저의 작업을 받아들이는 함수 존재 (주로 모델에게 처리하도록 넘긴다)
// 이후 해당 함수에서 모델에게 되돌려 받은 변경사항대로 컨트롤러가 UI를 수정 