package application.control;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;

public class RootController implements Initializable {
	
	@FXML TextField id; // 컨트롤러가 직접 읽거나 변경해야 하는 UI 요소는
	@FXML TextField pw; // 이렇게 @FXML을 통해 코드를 연결해 줘야 함
	
	@Override
	public void initialize(URL location, ResourceBundle resources) { }
	
	public void confirm(ActionEvent event) { // confirm 버튼 누르는 작업 수용
		System.out.println(id.getText().toString());
		System.out.println(pw.getText().toString()); // 콘솔 출력도 가능
	}
	
	public void cancel(ActionEvent event) { // cancel 버튼 누르는 작업 수용
		id.setText("");
		pw.setText(""); // UI에 변경사항 적용 (수정)
	}
	
}

// 컨트롤러 : UI에서 생긴 유저의 작업을 받아들이는 함수 존재 (주로 모델에게 처리하도록 넘긴다)
// 이후 해당 함수에서 모델에게 되돌려 받은 변경사항대로 컨트롤러가 UI를 수정 