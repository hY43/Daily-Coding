## JUnit: A Cook's Tour

[원문보기](http://junit.sourceforge.net/doc/cookstour/cookstour.htm)

우연히 [okky의 게시물](http://okky.kr/article/366169)을 읽고, 번역 공부와 객체 지향 공부를 병행해보고자 작성합니다.
아무래도 첫 번역이다보니...오역이 많을 수도 있느니 메일 혹은 댓글로 피드백 부탁드립니다.ㅠㅠ

------------------------------------------------------------------

Note: 이 글은 JUnit 3.8x 버전을 기반으로 작성되었습니다.

###1. Introduction

이전 글(see Test Infected: Programmers Love Writing Tests, Java Report, July 1998, Volume 3, Number 7)에서 반복적인 테스트를 하기 위한 간단한 프레임워크 사용법에 대한 내용을 작성했었다.
그리고 이번 글에서는 그 내부로 들어가 프레임워크 자체가 어떻게 구성되어 있는지 확인해보려 한다.
