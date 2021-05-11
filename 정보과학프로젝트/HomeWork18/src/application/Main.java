package application;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
	
	public static void main(String[] args) { launch(args); }
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		String dir = "view/fruitView.fxml";
		Parent root = FXMLLoader.load(getClass().getResource(dir)); 
		// FXML 파일에서 내용 불러와 root에 씌우기
		
		Scene scene = new Scene(root); // scene에 root의 내용 씌우기
		primaryStage.setScene(scene); // Stage(창)는 하나의 Scene을 가질 수 있음
		primaryStage.setTitle("Fruit");
		primaryStage.setOnCloseRequest(event->System.out.println("종료")); 
		primaryStage.show(); // Stage 띄우기 
		// new 함수형인터페이스(){ 메소드(매개변수){ 내용  } }
		// (매개변수) -> { 내용  }                        
		
	}

}
