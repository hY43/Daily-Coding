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

