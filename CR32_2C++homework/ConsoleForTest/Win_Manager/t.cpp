//#include <iostream>
//#include <Windows.h>
//
//using namespace std;
//
//BOOL CALLBACK EnumChildProc(_In_ HWND   hwnd, _In_ LPARAM lParam)
//{
//    char szTitle[MAX_PATH] = { 0 };
//    char szClass[MAX_PATH] = { 0 };
//    int nMaxCount = MAX_PATH;
//
//    LPSTR lpClassName = szClass;
//    LPSTR lpWindowName = szTitle;
//
//    GetWindowTextA(hwnd, lpWindowName, nMaxCount);
//    GetClassNameA(hwnd, lpClassName, nMaxCount);
//    cout << "[Child window] window handle: " << hwnd << " window name: "
//        << lpWindowName << " class name " << lpClassName << endl;
//
//    return TRUE;
//}
//
//
//BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
//{
//
//    /*
//    * Remarks
//    The EnumWindows function does not enumerate child windows,
//    with the exception of a few top-level windows owned by the
//    system that have the WS_CHILD style.
//    */
//    char szTitle[MAX_PATH] = { 0 };
//    char szClass[MAX_PATH] = { 0 };
//    int nMaxCount = MAX_PATH;
//
//    LPSTR lpClassName = szClass;
//    LPSTR lpWindowName = szTitle;
//
//    GetWindowTextA(hwnd, lpWindowName, nMaxCount);
//    GetClassNameA(hwnd, lpClassName, nMaxCount);
//    cout << "[Parent window] window handle: " << hwnd << " window name: "
//        << lpWindowName << " class name " << lpClassName << endl;
//
//    EnumChildWindows(hwnd, EnumChildProc, lParam);
//    cout << "\r\n**********************************" << endl;
//    return TRUE;
//}
//
//int main(int argc, char *argv[])
//{
//    EnumWindows(EnumWindowsProc, 0);
//    return 0;
//}


//���������Ӵ��ڵ��Ӵ��� , Z�����
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

void print_window2(HWND parent, int level)
{

    HWND child = NULL;
    TCHAR buf[MAX_PATH];
    DWORD pid = 0, tid = 0;

    char szTitle[MAX_PATH] = { 0 };
    char szClass[MAX_PATH] = { 0 };
    int nMaxCount = MAX_PATH;
    LPSTR lpClassName = szClass;
    LPSTR lpWindowName = szTitle;

    do
    {
        child = FindWindowEx(parent, child, NULL, NULL);
        if (child == NULL)
            break;
        int ret = GetWindowText(child, buf, MAX_PATH);
        GetClassNameA(child, lpClassName, nMaxCount);
        buf[ret] = 0;
        //tid = GetWindowThreadProcessId(child, &pid);





        for (int i = 0; i < level; ++i)
            cout << "\t";

        printf("%ws     ", buf);
        cout << child << "  " << lpClassName << endl;
        //cout << "    pid:" << pid << "   tid" << tid << endl;
        //_tprintf(L"%s ,  pid:%d, tid:%d\n", buf, pid, tid);

        if (child)
            print_window2(child, level + 1);
    }
    while (child);
}



//�������� explore �µĴ��� , Z�����

void print_window()
{
    HWND child = NULL;
    TCHAR buf[MAX_PATH];
    DWORD pid = 0, tid = 0;

    char szTitle[MAX_PATH] = { 0 };
    char szClass[MAX_PATH] = { 0 };
    int nMaxCount = MAX_PATH;
    LPSTR lpClassName = szClass;
    LPSTR lpWindowName = szTitle;

    do
    {
        //���� Explore �µ�һ������,������ҵ������ Explore �µ�child ������
        child = FindWindowEx(NULL, child, NULL, NULL);
        int ret = GetWindowText(child, buf, MAX_PATH);
        GetClassNameA(child, lpClassName, nMaxCount);
        buf[ret] = 0;
        //tid = GetWindowThreadProcessId(child, &pid);

        printf("%ws     ", buf);
        cout << child << "  " << lpClassName << endl;
        //cout << "    pid:" << pid << "   tid" << tid << endl;
        //_tprintf(L"%s ,  pid:%d, tid:%d\n", buf, pid, tid);

        //�����Ӵ�����
        if (child)
            print_window2(child, 1);
    }
    while (child);

}

int main()
{
    print_window();
    return 0;
}