
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int N = input.nextInt();
		if(N<0) System.out.println("minus");
		else System.out.println("plus");
		if(N%2==0) System.out.println("even");
		else System.out.println("odd");
	}
}
