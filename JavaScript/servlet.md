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
