package scenebuild;

import javafx.application.Application;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class Main extends Application { // 반드시 Application 상속!
	
	public static void main(String[] args) { launch(args); }
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		// Step #1 root (FXML로 한방에 처리)
		Parent root = FXMLLoader.load(getClass().getResource("/scenebuild_event/Main.fxml"));
		
		// Step #2 scene (CSS 파일로 추가 처리)
		Scene scene = new Scene(root,400,400); // Step #2 Scene
		scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		
		primaryStage.setTitle("My title"); // Step #3 Stage
		primaryStage.setScene(scene);
		primaryStage.show();
		
	}

}

// 이제 fxml과 css 파일 경로만 바꾸면 
// 자유롭게 JavaFX 어플리케이션을 돌릴 수 있음