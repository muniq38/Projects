
import java.util.Scanner; // 입력을 받는 스캐너 불러오기

public class Classroom {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in); // input = Scanner 클래스 객체
		Scanner st = new Scanner(System.in);
		
		int a = input.nextInt(); // 정수 입력
		int b = input.nextInt();
		String str = st.nextLine(); // 개행을 구분 문자열 입력
		String word = st.next(); // 공백 or 개행을 구분 문자열 입력
		
		System.out.println(a+b);
		System.out.println(str);
		System.out.println(word);
		
		input.close(); // Scanner 객체 닫기
		st.close();
	}
}
