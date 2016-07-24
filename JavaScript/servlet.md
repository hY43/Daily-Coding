# Servlet #
## 1. Servelet 이란 ##
Server Side Applet의 약어로, Web에서 동작하는 작은 Java 프로그램이라고 할 수 있다.

## 2. Web Service ##
Client(Web Browser) -------(요청)--------> Web Server --------(동적인 동작을 하기위해)-------> WAS(Web Application Server)
사용자가 자신의 Web Browser를 통해 페이지를 요청하면 Web Server에서 이 요청을 받게되는데 
Web Server의 경우 단순히 **_정적인 동작_**,  즉 단순히 보여주는 역할외에는 수행할 수 없다.
이 때문에 동적인 동작을 수행한 후, 그 결과를 Web Server를 통해 사용자에게 응답해주는 서버가 별도로 필요한데,
이러한 Server를 WAS(Web Application Server)라 한다.
WAS의 종류에는 여러가지가 있으나, 본 저장소의 코드는 JSP Servlet Container인 Tomcat을 사용한다.

## 3. 배포기술자(Deployment Descriptor) web.xml
web application 의 모든 환경 설정을 기록하는 파일로, Web Application 규약에는 반드시 META-INF와 WEB-INF 이라는 폴더가 존재해야하며 그 내부에는 반드시 web.xml 파일이 존재해야 한다.
예전엔 web project를 위해서는 이 배포 기술자에 반드시 매핑 작업이 필요했으나 현재는 Aunnotation을 통해서 간단히 적용시킬 수 있게 되었다.

```
package d20160623;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello.html") // Servlet 사용을 위한 Aunnotation!!
public class HelloWorld extends HttpServlet{ 
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		resp.setContentType("text/html;charset=UTF-8"); 
		PrintWriter pw = resp.getWriter();
		pw.println("<html>");
		pw.println("<head>");
		pw.println("<title> Hello world </title>");
		pw.println("</head>");
		pw.println("<body>");
		pw.println("<h1> My First Servlet </h1>");		
		pw.println("<h2> 안녕!! 서블릿 </h2>");		
		pw.println("</body>");
		pw.println("</html>");
	}
}
```
## 4. Servlet 사용 순서 ##
- HttpServlet Class 상속
- doGet(req, resp) 혹은 doPost(req, resp) Method Override
- WAS에 Servlet 등록(Annotation)
