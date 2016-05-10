package Algorithm;
import java.util.Scanner;

public class Algospot_LectureNote {
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		String input = sc.nextLine();
		char[] strToChar = input.toCharArray();
		String[] target = new String[input.length()/2+1];
		int j=0;
		for(int i=0;i<input.length();i+=2)
		{
			target[j] = "" + strToChar[i] + strToChar[i+1];
			j++;
		}
		for(int i=0;i<input.length()/2;i++)
			System.out.println(target[i]);
	}
}
