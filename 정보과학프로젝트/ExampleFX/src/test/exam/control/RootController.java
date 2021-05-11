package test.exam.control;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;

public class RootController implements Initializable {
	@FXML TextField textfield;
	@Override
	public void initialize(URL location, ResourceBundle resources) { }
	public void handleBtnAction(ActionEvent event) {
		System.out.println(textfield.getText().toString());
	}
}
