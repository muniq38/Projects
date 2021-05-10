package application;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class FirstTest extends Application {
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		// VBOX 생성
		VBox root = new VBox(); 
		root.setPrefWidth(350);
		root.setPrefHeight(150);
		root.setAlignment(Pos.CENTER); // Pos 열거형
		root.setSpacing(20);
		
		// label + button = control 
		Label label = new Label(); // label 생성
		label.setText("Hello Label");
		label.setFont(new Font(50));
		
		Button button = new Button(); // button 생성
		button.setText("ㅇㅇ");
		button.setOnAction(event->Platform.exit());
		
		// root에 모든 control 추가
		root.getChildren().add(label);
		root.getChildren().add(button);
		
		Scene scene = new Scene(root); // 설정 root로 scene 생성
		
		primaryStage.setScene(scene); // 만든 scene 윈도우에 부여 
		primaryStage.setTitle("app main"); // 윈도우 title 부여
		primaryStage.show(); // 윈도우(Stage) 보여주기
		
	}
	
	public static void main(String[] args) {
		launch(args); // 생성
	}

}
