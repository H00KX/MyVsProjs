#include <iostream>

/*
    7. ʹ������ĺ���չ��ʹ�õ�ʱ���Ƿ�������⣬�����˵����
```
#define X(n) ((n)+(n+1))
```

*/

#define X(n) ((n) + (n+1))

int main()
{
    int nNum = 5;

    printf("%d", X(++nNum));

}