
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int N = input.nextInt();
	    int M = input.nextInt();
	    for(int i=N; i<=M; i++) for(int j=1; j<=9; j++)
	    System.out.println(i+"*"+j+"="+i*j);
	}
}
