## JQuery ##
1. JQuery 란?
Java Script의 라이브러리의 일종

2. 사용 방법
```
**<script type="text/javascript" src = "http://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.0.0.min.js"></script>**
<script type="text/javascript">
	$(function(){
		$("#btn1").on("click",function(){
			/* $("h1").attr("class","red"); */
			$("h1").addClass("red");
			$("h1").addClass("blue");
		});
		$("#btn2").on("click",function(){
			/* $("h1").attr("class","red"); */
			$("h1").removeClass("red");
			$("h1").removeClass("blue");
		});
		$("#btn3").on("click",function(){
			/* $("h1").attr("class","red"); */
			$("h1").toggleClass("red");
			$("h1").toggleClass("blue");
		});
		
	});
</script>
```
위의 굵은 글씨로 작성된 CDN을 추가해주면 되는데, 직접 JQuery의 Library 파일을 경로에 넣고 사용해도 되지만
이 경우 브라우저의 사용자에게 JQuery의 Library 파일을 임시파일로 생성해주어야 하므로 부하가 올 수도 있다.
때문에 URL 타입의 CDN을 작성하는 편이 좋다.
