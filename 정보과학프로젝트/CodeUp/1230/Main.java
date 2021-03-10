
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int A = input.nextInt();
		int B = input.nextInt();
		int C = input.nextInt();
		
		if(A<=170) System.out.println("CRASH "+A); 
		else if(B<=170) System.out.println("CRASH "+B); 
		else if(C<=170) System.out.println("CRASH "+C);
		else System.out.println("PASS");
	}
}
