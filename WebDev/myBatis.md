#MyBatis#
## 1. ORM, Object-Relational Mapping ##
1-1. ORM은 데이터베이스와 객체 지향 언어 간의 호환되지 않는 데이터를 변환하는 프로그래밍 기법을 말하며,
iBatis와 MyBatis은 이를 위한 프레임 워크이다.
1-2. iBatis VS MyBatis: 원래는 iBatis 라는 이름으로 서비스를 제공하였으나, 구글에서 인수하게 되면서 서비스를 종료하고
MyBatis 라는 이름으로 다시 서비스를 제공하게 되었다.
두 가지 모두 ORM 에 대한 프레임워크로, JDBC를 좀더 쉽게 접근하기 위한 프레임 워크이다.
## 2. MyBatis의 기본 폴더 트리 ##
2-1. config
1) db.properties: database와의 연결을 위한 정보를 입력하는 파일
```
driver=oracle.jdbc.driver.OracleDriver
url=jdbc:oracle:thin:@192.168.0.74:1521:orcl
username=scott
password=tiger
```
2) SqlMapConfig: database와의 연결 방식과 쿼리문을 작성할 mapper.xml등의 정보 등을 기록하는 xml 설정 파일
```
<?xml version="1.0" encoding="UTF-8"?>
<!-- DTD, xml-schema -->
<!-- http://www.mybatis.org/mybatis-3/getting-started.html -->
<!DOCTYPE configuration
  PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
	<!-- db 정보가 있는 파일의 위치 -->
	<properties resource="config/db.properties" />
	<environments default="dev">
		<environment id="dev">
		<!-- 트랜잭션관리는 JDBC 방식으로 -->
			<transactionManager type="JDBC" />
			<!-- db 연결은 Connection Pooling 방식으로 -->
			<dataSource type="POOLED">
				<property name="driver" value="${driver}"/>
				<property name="url" value="${url}"/>
				<property name="username" value="${username}"/>
				<property name="password" value="${password}"/>
			</dataSource>
		</environment>
	</environments>
	
	<!-- sql 문을 한 곳에 모아서 관리 
		db에 접근해서 사용할 모든 sql문을 미리 xml 파일에 등록하고,
		등록한 문장의 별칭 명을 코드에서 사용
	-->
	<mappers>
		<mapper resource="mapper/Mapper.xml"/>
	</mappers>
</configuration>
```
2-2. mapper
2-3. vo
## 3. 응용 어플리케이션에서의 MyBatis 사용 ##
## 4. 웹 어플리케이션에서의 MyBatis 사용 ##

