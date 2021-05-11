package application;
	
import javafx.application.Application;

import javafx.scene.control.Button;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;

public class HelloWorld extends Application { // 반드시 Application 상속!
	
	public static void main(String[] args) { launch(args); }
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		// root의 내용물 생성 (FXML로 커버할 수 있는 부분)
		Button btn = new Button("Click me");
		
		EventHandler<ActionEvent> hello = new EventHandler<ActionEvent>(){
			@Override
			public void handle(ActionEvent event) {
				System.out.println("hello world"); }
		}; // EventHandler<ActionEvent>는 인터페이스, 구현부 재정의한것
		
		btn.setOnAction( hello ); // 버튼에 동작을 추가하기 위함 
		
		StackPane root = new StackPane(); // Step #1 root 생성 
		root.getChildren().add(btn); // root에 버튼 추가 
		
		Scene scene = new Scene(root, 500, 300); // Step #2 Scene 생성
		primaryStage.setScene(scene); // Step #3 Stage에 Scene 추가
		primaryStage.show(); // Stage = Window
	
	}
	
}
