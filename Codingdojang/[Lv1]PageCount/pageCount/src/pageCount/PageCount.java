package pageCount;

public class PageCount {
	public static void main(String[] args){}

	int PageCount(int contents, int conLimit)
	{
	    int pageCount = contents/conLimit;
	    // pageCount: �ּ� ������ ���� ��� ���� ����
	    pageCount = (pageCount%conLimit == 0) ? pageCount : pageCount+1;
	    // �������� ���ٸ� ������ �������� �ʿ� ���� ������ ������ pageCount�� ��ȯ�ϰ�, �������� �ִٸ� �߰��� ���������� �� �ʿ��ϱ� ������ pageCount+1�� ��ȯ�ؾ��Ѵ�.
	    return pageCount;
	}
}
