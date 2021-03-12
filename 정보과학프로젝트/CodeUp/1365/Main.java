
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int N = input.nextInt();
	    for(int i=1; i<=N; i++){
	        for(int j=1; j<=N; j++){
	            if(i==1 || i==N || j==1 || j==N || i+j==N+1 || i==j)
	            System.out.printf("*");
	            else System.out.printf(" ");
	        }System.out.printf("\n");
	    }
	}
}
