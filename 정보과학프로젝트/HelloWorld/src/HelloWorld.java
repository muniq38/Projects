
public class HelloWorld { // 메인 클래스 - 모두 여기서 돌아가고 파일 이름과 일치해야 함
	public static void main(String[] args) {  // 메인 메소드(함수) - 처음 실행
		System.out.println("Hello World!");	
	}
}

// 항상 java의 모든 프로그램은 프로젝트 형식으로 돌아감
// 소스코드는 프로젝트 폴더 내부의 source폴더 안에 저장됨

// (1) source폴더 안의 .java 실행 - javac.exe에서 컴파일   
// (2) 컴파일 후 bin폴더에 .class로 저장 - java.exe (JVM)에서 실행 - 기계어로 처리

// 원격에서 실행하는 법 - bin에서 java "ClassName" 치면 (2)번과정 진행됨
// 또는 src에서 javac "javaName" 치면 (1)번과정부터 진행됨 
