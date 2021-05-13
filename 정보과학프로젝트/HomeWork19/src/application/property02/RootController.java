package application.property02;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.beans.binding.Bindings;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;

public class RootController implements Initializable {

	@FXML private TextArea Area1;
	@FXML private TextArea Area2;
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		Bindings.bindBidirectional(Area1.textProperty(), Area2.textProperty());
		// Area1의 text <-동기화-> Area2의 text
	}

}
