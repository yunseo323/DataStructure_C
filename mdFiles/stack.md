## 스택 ADT
<**후입선출**> 삽입과 삭제는 스택의 top 위치에서 수행
- 배열 이용
- 단일 연결리스트를 사용해 스택 구현
: 삽입과 삭제가 특정위치에서만 수행되어, header은 불필요하다.
  top 원소를 연결리스트의 첫 노드에 저장하고 t로 가리키게 한다.
**<주요 Method>**
- push
- pop
- isEmpty / size
- 