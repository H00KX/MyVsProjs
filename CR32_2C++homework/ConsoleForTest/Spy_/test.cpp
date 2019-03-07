#include <Windows.h>
#include "stdio.h"

int main()
{
    char a[] = "\xc6";
    for (int i = 0; i < 4; i++)
    {
        printf("%02x ", a[i]);
    }

    return 0;
}