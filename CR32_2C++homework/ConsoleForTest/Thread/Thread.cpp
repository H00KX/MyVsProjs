// Thread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

DWORD  MyTestThread(LPVOID);


int main()
{
    HANDLE hThread = 0;
    DWORD   Tid;

    MyTestThread((LPVOID)0x666888);

    //hThread = CreateThread(NULL, 0, MyTestThread, 0, 0, &Tid);
    WaitForSingleObject(hThread, INFINITE);
    return 0;
}

DWORD  MyTestThread(LPVOID)
{
    while (true)
    {
        Sleep(1000 * 5);
        cout << "ֻ��һ������" << endl;
    }



    return 0;
}
