
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int N = input.nextInt();
	    int M = input.nextInt();
	    int[][] Board = new int[N][M];
	    for(int i=0; i<N; i++) for(int j=0; j<M; j++)
	    Board[i][j] = input.nextInt();
	    for(int i=0; i<N; i++) for(int j=1; j<M; j++) Board[i][j] += Board[i][j-1];
	    for(int j=0; j<M; j++) for(int i=1; i<N; i++) Board[i][j] += Board[i-1][j];
	    for(int i=0; i<N; i++){
	        for(int j=0; j<M; j++) System.out.printf("%d ", Board[i][j]);
	        System.out.printf("\n");
	    }
	}
}
