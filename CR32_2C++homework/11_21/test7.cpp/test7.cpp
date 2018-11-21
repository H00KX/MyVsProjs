#include <iostream>

/*
    7. 使用下面的宏扩展在使用的时候是否存在问题，请举例说明：
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