package pageCount;

public class PageCount {
	public static void main(String[] args){}

	int PageCount(int contents, int conLimit)
	{
	    int pageCount = contents/conLimit;
	    // pageCount: 최소 페이지 수를 얻기 위한 변수
	    pageCount = (pageCount%conLimit == 0) ? pageCount : pageCount+1;
	    // 나머지가 없다면 여분의 페이지가 필요 없기 때문에 기존의 pageCount를 반환하고, 나머지가 있다면 추가로 한페이지가 더 필요하기 때문에 pageCount+1을 반환해야한다.
	    return pageCount;
	}
}
