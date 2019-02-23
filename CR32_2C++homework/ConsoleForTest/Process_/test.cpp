#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include "stdio.h"

#pragma comment(lib,"kernel32.lib")

int PrintModules(DWORD processID)
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Print the process identifier.

    printf("\nProcess ID: %u\n", processID);

    // Get a handle to the process.

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                           PROCESS_VM_READ,
                           FALSE, processID);
    if (NULL == hProcess)
        return 1;

    // Get a list of all the modules in this process.

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];

            // Get the full path to the module's file.

            if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
                                    sizeof(szModName) / sizeof(TCHAR)))
            {
                // Print the module name and handle value.

                _tprintf(TEXT("\t%s (0x%08X)\n"), szModName, hMods[i]);
            }
        }
    }

    // Release the handle to the process.

    //CloseHandle(hProcess);


    THREADENTRY32 te;
    te = { sizeof(THREADENTRY32) };
    int t = GetLastError();
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processID);
    t = GetLastError();

    if (Thread32First(hSnap, &te))
    {
        do
        {
            _tprintf(TEXT("\t%x  %s\n"), te.th32ThreadID, te.tpBasePri);
        }
        while (Thread32Next(hSnap, &te));
    }

    return 0;
}


int main()
{
    //**********************************   1
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (INVALID_HANDLE_VALUE == hSnap)
    {
        MessageBox(NULL, TEXT("创建进程失败"), TEXT("错误"), MB_ICONERROR);
        return FALSE;
    }

    if (Process32First(hSnap, &pe))
    {
        do
        {
            {
                printf("%ws\r\n", pe.szExeFile);
                PrintModules(pe.th32ProcessID);

            }
        }
        while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);



    //**********************************   2
    DWORD aProcesses[1024];
    DWORD cbNeeded;
    DWORD cProcesses;
    unsigned int i;

    // Get the list of process identifiers.

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
        return 1;

    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the names of the modules for each process.

    for (i = 0; i < cProcesses; i++)
    {
        PrintModules(aProcesses[i]);
    }


    system("pause");
}