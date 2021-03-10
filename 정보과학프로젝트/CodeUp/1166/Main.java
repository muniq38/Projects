
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int N = input.nextInt();
		if(N%400==0) System.out.println("yes");
		else if(N%100==0) System.out.println("no");
		else if(N%4==0) System.out.println("yes");
		else System.out.println("no");
	}
}
