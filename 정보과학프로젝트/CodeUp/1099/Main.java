
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int a=2, b=2;
	    int[][] Board = new int[15][15];
	    for(int i=1; i<=10; i++) for(int j=1; j<=10; j++) 
	    Board[i][j]=input.nextInt();
	    
	    while(true){
	        if(Board[a][b]==2){ Board[a][b]=9; break; } 
	        Board[a][b]=9;
	        if(Board[a][b+1]!=1){ b++; continue; }
	        if(Board[a+1][b]!=1){ a++; continue; }
	        break;
	    }
	    
	    for(int i=1; i<=10; i++){
	        for(int j=1; j<=10; j++) System.out.printf("%d ", Board[i][j]);
	        System.out.printf("\n");
	    }
	}
}
