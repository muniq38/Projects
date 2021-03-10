
public class ArrayExercise {
	public static void main(String[] args) {
		int[] score = {10, 20, 30};
		int sum = 0;
		for(int x:score) sum += x; // 새로운 for문 (편리)
		System.out.println(sum); // 60
		
		int[] intArray;
		intArray = new int[10];
		int[] intOnce = new int[20];
		
		String[] names = null;
		names = new String[] {"AAA","BBB","CCC"};
		System.out.println(names[1]);
		
		int[][] scores = new int[2][3]; // 2차원 배열
		System.out.println(scores[0].length); // 3
		System.out.println(scores.length); // 2
		
		int[][] dynamic = new int[2][];
		dynamic[0] = new int[2];
		dynamic[1] = new int[3];
		System.out.println(dynamic[0].length); // 2
		
		int[][] multiArr = {{2,3},{4,5,6}};
		System.out.println(multiArr[1][1]); // 5
	}
}
