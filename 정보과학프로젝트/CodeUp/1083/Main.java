
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int N; N = input.nextInt();
		for(int i=1; i<=N; i++){
		    if(i%3==0) System.out.printf("X ");
		    else System.out.printf("%d ", i);
		}
	}
}

