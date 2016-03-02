public class convert_StoI {
	public static void main(String[] args)
	{
		int sum = 0;
		int[] fibo = new int[100];
		fibo[0] = 1; fibo[1] = 2;
		
		for(int i=2;fibo[i-1]<4000000;i++)
		{
			fibo[i] = fibo[i-1] + fibo[i-2];
			if(fibo[i]%2 == 0)
				sum += fibo[i];
		}
		
		System.out.println("Sum = " + (sum+2));
	}
}