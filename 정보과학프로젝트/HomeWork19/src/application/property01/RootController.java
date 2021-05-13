package application.property01;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.text.Font;

public class RootController implements Initializable {

	@FXML private Label label;
	@FXML private Slider slider; // 슬라이더와 라벨 정보 읽기/변경
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		slider.valueProperty().addListener((observable, oldValue, newValue) -> { 
			label.setFont(new Font(newValue.doubleValue()));
		}); // Slider의 위치를 나타내는 Value --동기화-> Label의 크기를 나타내는 Font  
	}

}
