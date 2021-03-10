
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int a = input.nextInt();
		int b = input.nextInt();
		int c = input.nextInt();
		
		if((a%2)==0) System.out.println(a);
		if((b%2)==0) System.out.println(b);
		if((c%2)==0) System.out.println(c);
	}
}
