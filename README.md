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
1. 뮤텍스 (Mutex)  
1- 역할 - 한 개 자원의 소유 여부를 관리하는 동기화 객체  
2- 목적 - 하나의 공유 자원을 보호/관라하기 위해 사용됨  
3- 비고 - BOOL 형의 동기화 객체 (Thread의 실행 여부만을 통제)  
4- API - CreateMutex();, OpenMutex();, ReleaseMutex();  

2. 세마포어 (Semaphore)  
1- 역할 - 사용 가능한 자원의 개수를 카운트하는 동기화 객체  
2- 목적 - 제한된 일정 개수의 공유자원을 보호/관리하기 위해 사용됨  
3- 비고 - int 형의 동기화 객체 (실행 가능한 Thread 개수를 관리  
4- API - CreateSemaphore(); OpenSemaphore(); ReleaseSemaphore();  

3. 이벤트 (Event)  
1- 역할 - 어떤 사건이 일어났음을 알리는 동기화 객체  
2- 목적 Thread 간의 통신을 위한 신호를 보내기 위해 사용됨(작업순서, 시기조정 등)  
3- 비고 - 윈도우 메세지와 비슷한 역할의 동기화 객체  
4- API - CreateEvent(); OpenEvent(); SetEvent(); ResetEvent();  
`<HANDLE CreateEvent(NULL,FALSE,FALSE,NULL)>` 자동 리셋 이벤트  
`<HANDLE CreateEvent(NULL,TRUE,TRUE,NULL)>` 수동 리셋 이벤트  

---
WaitForSingObject();  
WaitForMultipleObjects();  
