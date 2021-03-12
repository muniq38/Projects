
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int N = input.nextInt(), A;
	    int[] Line = new int[30];
	    for(int i=0; i<N; i++){
	        A = input.nextInt();
	        Line[A]++;
	    }for(int i=1; i<=23; i++) System.out.printf("%d ", Line[i]);
	}
}
