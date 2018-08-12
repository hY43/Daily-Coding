## JUnit: A Cook's Tour

[원문보기](http://junit.sourceforge.net/doc/cookstour/cookstour.htm)

우연히 [okky의 게시물](http://okky.kr/article/366169)을 읽고, 번역 공부와 객체 지향 공부를 병행해보고자 작성합니다.
아무래도 첫 번역이다보니...오역이 많을 수도 있느니 메일 혹은 댓글로 피드백 부탁드립니다.ㅠㅠ

현재 작성중으로...문체는 조금씩 맞춰나갈 예정

------------------------------------------------------------------

Note: 이 글은 JUnit 3.8x 버전을 기반으로 작성되었습니다.

## 1. 소개
> Note : 이 글은 JUnit 3.8.x. 버전을 기반으로 작성되었습니다.

이전 글에서 우리는 간단한 프레임워크를 사용하여 반복적인 테스트를 작성하는 방법에 대해 이야기 해봤습니다. 그리고 이번 글에서는 그 프레임워크 자체가 어떻게 구성되어 있는지 알아보려 합니다.
우리는 JUnit Framework에 대해 아주 정성들여 연구했고, 어떻게 구성하였는지에 대해 되짚어보며 다양한 수준의 교훈을 얻을 수 있었습니다.
절망적이게도 우리는 이 문서에서 한번에 이 프레임워크를 설명하려고 하려고 합니다. 하지만 적어도 소프트웨어의 설계나 디자인을 보여주는 맥락으로 이를 진행할 것입니다.
이글에서 우리는 그 교훈 모두를 한번에 보여주려 하겠지만 이는 매우 어려운 일이기 때문에 최소한 소프트웨어의 작은 부분을 디자인하고 구성하는 것을 보여주는 방식으로 진행할 것입니다.
이 Framework의 목표에 대해 논의해봤는데 그 목표는 Framework 그자체를 설명하는 과정에서 여러번에 나누어 확인할 수 있을 것입니다.
그 후,  우리는 이 Framework의 디자인과 구현을 보여주고자 합니다. 이 디자인은 프로그램에서의 구현과 패턴적인 면에서 보여질 것입니다.
마지막으로 우리는 Framework에 대한 몇가지 생각을 제시하며 이 글을 마칠 것입니다.

## 2. 목표

JUnit의 목적은 뭘까요?
첫째로 개발 당시로 돌아가보도록 하겠습니다. 만약 한 프로그램이 자동화된 테스트가 부족하다면, 그 프로그램이 정상적으로 동작하지 않는다고 가정해보겠습니다.
이러한 가정은 개발자가 우리에게 프로그램은 현재부터 영원이 잘동작할 것이라 단언하는 것보다 훨씬 안전해보입니다.
이러한 관점에서 개발자는 그들이 코드를 작성하고 디버깅할때, 그 프로그램이 잘동작한다는 것을 증명하기 위해 테스트 역시 작성해야합니다.
하지만 모두 할일은 많고, 바쁘기 때문에 테스트에 투자할 시간이 충분하지 않습니다.
“난 이미 너무 많은 코드를 작성했는데.. 어떻게 테스트 코드를 또 작성하죠? 대답해주세요 Mr.Hard-case PM님ㅠㅠ" 

그래서 첫번째 목표는 개발자가 실제로 테스트를 작성할 것이라는 희미한 희망을 가질 수 있는 Framework를 작성하는 것입니다..
이 Framework는 친숙한 도구들을 사용하기 때문에 새로 배울 것이 거의 없습니다.. 이 말은 새로운 테스트를 작성하는데 필요 이상의 작업을 할 필요가 없다는 것을 의미합니다. 그리고 이는 중복된 수고를 제거하게 됩니다.
만약 모든 테스트들이 진행되어야 한다면, 당신은 디버거에 표현식을 작성하는 것만으로 이를 진행할 수 있습니다. 하지만 이는 테스트에 충분하지 않습니다.
당신의 프로그램이 지금 당장은 동작한다해도 일분뒤, 5년뒤, 혹은 오랫동안 자리를 비웠을때에도 동작하리라고 확신할 수 없기 때문에 이러한 사실은 나에겐 그다지 도움이 되지 않습니다.

다음으로 Testing의 두번째 목표는 시간이 지나더라도 그 가치가 유지되는 테스트를 생성하는 것입니다. 최초 작성자보다 다른 누군가가 테스트를 실행할 수 있어야하며 그 결과를 이해할 수 있어야 합니다. 이는 다양한 사람들에 의해 작성된 테스트가 서로에게 영향을 주지 않고 결합/실행되어야 합니다.

마지막으로 기존에 작성된 테스트를 통해 새로운 테스트를 만들 수 있어야합니다. Setup 이나 Fixture를 새로 생성하는 것은 비용이 많이 들기 때문에 Framework는 기존의 Fixture를 재사용하여 다른 테스트를 실행할 수 있어야 합니다.

흠.. 이게 전분가??

## 3. JUnit 의 디자인

JUnit의 디자인은 최초에 “Patterns Generate Architectures”에서 사용된 스타일로 제시된다. 이 스타일은 아무 것도 없는 상태에서 시작하여 시스템의 아키텍쳐가 완성될 때까지 차례로 패턴을 적용하는 방식으로 설명하는 것입니다.
우리는 해결하고자 하는 설계적인 문제를 제공하고, 이 를 해결하기 위한 패턴을 요약해서 이 패턴을 어떻게 JUnit에 적용하는지를 보여줄 것입니다.

### 3.1 시작하기 - TestCase
첫째로 우리는 TestCase라는 기본 개념을 표현할 객체를 만들어야 합니다. 개발자들은 테스트 케이스를 염두해두고 여러가지 방식으로 이를 실행한다.

* 상태 출력
* 디버거 표현식
* 테스트 스트립트