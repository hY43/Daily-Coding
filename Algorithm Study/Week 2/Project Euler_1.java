/**********************************************
Project Euler 1)
url: https://projecteuler.net/problem=1
**********************************************/

public class p1 {
	public static void main(String[] args)
	{
		int sum = 0;
		for(int i=0; i<1000; i++)
		{
			if((i%3)==0 || (i%5)==0)
				sum += i;
		}
		System.out.println("sum of all the multiples of 3 or 5 below 1000 : " + sum);
	}
}