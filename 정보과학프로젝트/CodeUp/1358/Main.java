
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int N = input.nextInt();
	    int Blnk = (N-1)/2, Star = 1;
	    for(int i=0; i<(N+1)/2; i++){
	        for(int j=0; j<Blnk; j++) System.out.printf(" ");
	        for(int j=0; j<Star; j++) System.out.printf("*");
	        System.out.printf("\n"); Blnk--; Star+=2;
	    }
	}
}
