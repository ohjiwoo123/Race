# Race (Critical Section, Mutex 사용)

유저모드를 동기화화해서 사용하려면 Critical Section 사용  
(일반적으로 다른 커널 객체 동기화 함수보다 빠르다고 한다.)  

**단 동일한 프로세스 내에서만 동기화할 수 있다**  
**다른 쓰레드(Thread)에게 방해 받지 말아야 할 작업을 CS로 감싸둔다**   
```
Critical_Section cs;  // 크리티컬 섹션 선언
VOID InitalizeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);  // 크리티컬 섹션 초기화

VOID EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
//… 이 사이에서 공유자원을 안전하게 액세스한다.(임계영역)
VOID LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

VOID DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection); // 
```
--|Mutex(뮤텍스) | Semaphore(세마포어) | Event(이벤트)
---|------------ | -------------|-------------
|Cell 1 | Cell 2 | 
|Cell 1 | Cell 2 | 

WaitForSingObject();  
WaitForMultipleObjects();  
