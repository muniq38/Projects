package application;
	
import javafx.application.Application;

import javafx.scene.control.Button;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;

public class HelloAdvanced extends Application { // 반드시 Application 상속!
	
	public static void main(String[] args) { launch(args); }
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		// root의 내용물 생성 (FXML로 커버할 수 있는 부분)
		Button btn = new Button("Click me");
		Button exit = new Button("Exit");
		
		btn.setOnAction( event -> {   
			System.out.println("hello world"); });
		
		exit.setOnAction( event -> { 
			System.out.println("exit this app");
			System.exit(0); });
	
		VBox root = new VBox(); // Step #1 root 
		root.getChildren().addAll(btn, exit); // root에 버튼 추가 (한꺼번에 : addAll)
		
		Scene scene = new Scene(root, 500, 300); // Step #2 Scene 
		primaryStage.setScene(scene); // Step #3 Stage 
		primaryStage.setTitle("My title"); 
		primaryStage.show(); // Stage = Window
	
	}

}

//함수형 인터페이스 (구현할 메소드가 오직 하나인 인터페이스)에 람다식 적용

// new EventHandler<ActionEvent>(){ 
// 		public void handle(Actionevent event){ 구현 } } 

// event -> { 구현 } 
// 같은 표현식이다. 참고하면 훨씬 편하게 짤 수 있다.

