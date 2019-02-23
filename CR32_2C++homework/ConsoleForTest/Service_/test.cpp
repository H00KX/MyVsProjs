// TestServices.cpp : 定义控制台应用程序的入口点。
#include <windows.h>
#include <stdio.h>
//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\

//GetWindowLong
//GetClassLong
//SetROP2
//WindowFromPoint


int EnumServices()
{

    char szDisplayName[256] = { 0 };
    char szServiceName[256] = { 0 };

    DWORD pcbBytesNeeded = 0;           // buffer size needed
    DWORD lpServicesReturned = 0;       // number of entries returned
    DWORD lpResumeHandle = 0;           // next entry


                                        //需要管理员权限
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                    // local machine 
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (schSCManager == NULL)
    {
        printf("OpenSCManager");
        return 0;
    }

    ENUM_SERVICE_STATUS ServiceStatus;
    ServiceStatus.lpDisplayName = szDisplayName;
    ServiceStatus.lpServiceName = szServiceName;
    BOOL bRet = FALSE;

    pcbBytesNeeded = 0;
    lpServicesReturned = 0;

    bRet = EnumServicesStatus(schSCManager,
                              SERVICE_WIN32,
                              SERVICE_STATE_ALL,
                              &ServiceStatus,
                              0,
                              &pcbBytesNeeded,
                              &lpServicesReturned,
                              &lpResumeHandle);

    ENUM_SERVICE_STATUS* pAry = NULL;
    ENUM_SERVICE_STATUS* pAryOrg = NULL;


    if (bRet == 0 && GetLastError() == ERROR_MORE_DATA)
    {
        //说明ServiceStatus空间不够
        pAry = (ENUM_SERVICE_STATUS*)new char[pcbBytesNeeded];
        pAryOrg = pAry;
    }


    bRet = EnumServicesStatus(schSCManager,
                              SERVICE_WIN32,
                              SERVICE_STATE_ALL,
                              pAry,
                              pcbBytesNeeded,
                              &pcbBytesNeeded,
                              &lpServicesReturned,
                              &lpResumeHandle);

    for (int i = 0; i < lpServicesReturned; i++)
    {
        printf(pAry->lpDisplayName);
        printf("\r\n");
        pAry++;
    }

    delete[] pAryOrg;

}


int main()
{
    EnumServices();


    return 0;
}

