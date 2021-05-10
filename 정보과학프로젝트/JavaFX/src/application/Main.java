package application;
	
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;


public class Main extends Application {
	public Main() { // App Thread 담당
		System.out.println(Thread.currentThread().getName() + ": Main() call"); 
	} 
	
	@Override
	public void init() throws Exception { // Launcher 실행
		System.out.println(Thread.currentThread().getName() + ": init() call");
	}
	
	@Override
	public void start(Stage primaryStage) throws Exception { // Stage = 윈도우 
		
		System.out.println(Thread.currentThread().getName() + ": start() call");
		BorderPane root = new BorderPane();
		Scene scene = new Scene(root,400,400); // scene 객체 생성
		
		primaryStage.setTitle("hello JavaFX"); // Stage에 title 설정
		primaryStage.setScene(scene); // Stage에 scene 설정
		primaryStage.show(); // 윈도우(Stage) 보여주기
		
	}
	
	@Override
	public void stop() throws Exception {
		System.out.println(Thread.currentThread().getName() + ": stop() call");
	}
	
	public static void main(String[] args) {
		launch(args); // App Thread + Launcher 생성
	}
}

//JAVAFX의 lifecycle - 주요 정적 메소드
	// launch() - 객체와 App Thread + Launcher 생성
	// init() - 객체 생성 후 호출, Launcher 실행
	// start() - App Thread에서 기본 윈도우창과 UI 호출
	// stop() - App Thread에서 마지막 Stage 닫힐때 호출

