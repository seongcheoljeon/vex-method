# Houdini VEX Method

자주 사용하는 Houdini VEX 메소드 정의 파일이다.

- method.h : 여러가지 정의.
- PriorityQueue.h : Heap 자료구조를 이용한 우선순위 큐 정의. 성능: O(nlog2n)

```cpp
#include "PriorityQueue.h"

PQueue pq;
PQueueInit(pq);
// 데이터 삽입
PEnqueue(pq, 10);
PEnqueue(pq, 8);
PEnqueue(pq, 2);
PEnqueue(pq, 5);

// 데이터 출력
while(!PQIsEmpty(pq)){
    printf("%d ", PDequeue(pq));
}

/* 출력결과
2 5 8 10
*/
```
