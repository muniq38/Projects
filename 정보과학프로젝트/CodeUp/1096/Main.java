
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int N = input.nextInt(), a, b;
	    int[][] Board = new int[20][20];
	    for(int i=0; i<N; i++){
	        a = input.nextInt();
	        b = input.nextInt();
	        Board[a][b]=1;
	    }for(int i=1; i<=19; i++){
	        for(int j=1; j<=19; j++) System.out.printf("%d ", Board[i][j]);
	        System.out.printf("\n");
	    }
	}
}
