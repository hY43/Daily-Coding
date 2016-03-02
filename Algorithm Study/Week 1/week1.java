// Algorithm Study Week 1
// Q1) 1,000 보다 작은 자연수 중에서 3 또는 5의 배수를 모두 더하면 얼마인가?
public class problem_1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int sum=0;
		
		for(int i=1;i<1000;i++)
		{
			if(i%3==0 || i%5==0)
			{
				sum+=i;
			}
		}
		System.out.println("1000보다 작은 자연수 중 3 또는 5의 배수의 합: " + sum);
		
	}
}

// Q2) Q2.jpg 파일 확인할 것

import java.util.ArrayList;
import java.util.Arrays;


public class convert_StoI {
	public static void main(String[] args)
	{
		
		String input = "Pfister";
		String[] output = new String[input.length()];
		String[] items = input.split("");
		// 문자열의 각 문자를 Split함수를 통해 items 배열에 하나씩 입력
		output[0] = items[0];
		ArrayList<String> myList = new ArrayList<String>(Arrays.asList(items));
		// 보다 편한 정리(모음, h, w 제거)를 위해 ArrayList 사용		
		
		// Array List의 크기 만큼의 루프
		for(int i=1;i<myList.size();i++)
		{
			switch(myList.get(i))
			{
			case "b":
			case "f":
			case "p":
			case "v":
				myList.set(i, "1");
				break;
			case "c":
			case "g":
			case "j":
			case "k":
			case "q":
			case "s":
			case "x":
			case "z":
				myList.set(i, "2");
				break;
			case "d":
			case "t":
				myList.set(i, "3");
				break;
			case "l":
				myList.set(i, "4");
				break;
			case "m":
			case "n":
				myList.set(i, "5");
				break;
			case "r":
				myList.set(i, "6");
				break;
			}
		}
		
		for(int i=1;i<myList.size();i++)
		{
			switch(myList.get(i))
			{
			case "a":
			case "i":
			case "e":
			case "o":
			case "u":
			case "y":
				myList.remove(i);
				break;
			case "h":
			case "w":
				if(myList.get(i-1) == myList.get(i+1))
				{
					myList.remove(i);
					myList.remove(i+1);
				}
				else
				{
					myList.remove(i);
				}
				break;
			}
		}
		for(int i=1;i<4;i++)
		{
			output[i] = myList.get(i);
		}
		
		System.out.println("Input: " + input);
		System.out.print("Output: ");
		for(int i = 0;i<4;i++)
			System.out.print(output[i]);
	}
}
