# JSP, Java Server Page #
### 1. JSP 사용 이유?? ###
JSP란 Java Server Page의 약어로, Servlet 만으로는 HTML 페이지를 표현하기 어렵기 때문에 HTML 페이지 자체에 Java 문법을 사용하기 위해 사용한다.

### 2. JSP의 구성요소 ###
##### 2-1. 지시어(Directive) #####
- Page Directive, 페이지의 기본 정보를 나타내는 지시어로 일반적으로 페이지의 상단부에 <%@page ~~~ %>로 작성되는 지시어를 말한다.
```
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<!-- HTML 주석: Browser에서 확인 가능 --> 
	<%-- JSP 주석: Browser에서 확인 불가능 --%>
	
	<hr>
	<% 
		int c = a + b;
		out.println("합계: " + c);
	%>
		<h3>합계는 <%=c %></h3>
	<%!
		int a = 20;
		int b = 10;
	%>
</body>
</html>
```
##### 2-2. Scriptlet #####
자바의 문법을 사용할 수 있도록 영역을 표시하는 것으로 일반적으로 <% 자바문법 %> 과 같이 사용된다.

##### 2-3. Expression #####
데이터를 출력하는데 불필요한 출력 문을 줄이고자 사용되며 예를 들어 **_<% out.println(x) %>_**를 Expression을 통해 작성하면
**_<%=x %>_**과 같다.

##### 2-4. Declaration
Scriptlet이나 표현식에서 사용할 수 있는 인스턴스 변수나 메서드를 정의할 때 사용하며 일반적으로
<%! %>와 같이 작성하여 사용한다.
