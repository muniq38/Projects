
import java.util.Scanner;

class Gshs { }

public class StringExercise {
	public static void main(String args[]) {
		char ch = 'A'; 
		ch = 65; // 'A' = ASCII 65
		ch = '\u0041'; // 'A' = unicode 0x0041
		
		Gshs a = new Gshs();
		Gshs b = new Gshs();
		Gshs c = null; // ok, 하지만 사용할 순 없음
		
		String st11 = "Hello ";
		String st12 = "World";
		System.out.println(st11+st12+"\n");
		
		String st3 = "Hello World";
		System.out.println(st3.length());
		System.out.println(st3.replace('l', 'k'));
		System.out.println(st3.substring(3,8));
		System.out.println(st3.charAt(2)+"\n");
		
		String st4 = "hello world";
		String st5 = new String("Hello World"); // 새로운 선언방식
		System.out.println(st3.contentEquals(st4));
		System.out.println(st3.equalsIgnoreCase(st4)+"\n");
		System.out.println(st3==st5); // 메모리가 다르면 다른거임
		
		StringBuffer sb1 = new StringBuffer();
		sb1.append("Java");
		sb1.append("+Programming"); 
		sb1.delete(1,5); // 1부터 5-1까지 삭제 (1,2,3,4)
		System.out.println(sb1); // "JProgramming"
		System.out.println(sb1.length());
		System.out.println(sb1.reverse());
		st5 = sb1.toString();
		
		String code = "20119";
		int codenum = Integer.parseInt(code);
		System.out.println(codenum+1);
		System.out.println(code+1);
	
		String integer;
		integer = Integer.toString(30); // "30"
		integer = String.valueOf(45); // "45"
		
		int num=100, result=0;
		for(int i=1; i<=5; i++) { // try & catch
			try {
				result = num/(int)(Math.random()*10);
				System.out.println(result);
			}catch(ArithmeticException e) { System.out.println("0"); } // 예외 탐지
		}
		
	}
}
