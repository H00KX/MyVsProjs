#include <ntddk.h>

NTKERNELAPI PCHAR PsGetProcessImageFileName(PEPROCESS process);
NTKERNELAPI NTSTATUS PsLookupProcessByProcessId(HANDLE ProcessId, PEPROCESS *Process);

PCHAR GetProcessNameByProcessId(HANDLE ProcessId)
{
	NTSTATUS st = STATUS_UNSUCCESSFUL;
	PEPROCESS ProcessObj = NULL;
	PCHAR string = NULL;
	st = PsLookupProcessByProcessId(ProcessId, &ProcessObj);
	if (NT_SUCCESS(st))
	{
		string = PsGetProcessImageFileName(ProcessObj);
		ObfDereferenceObject(ProcessObj);
	}
	return string;
}


VOID MyCreateProcessNotifyEx(
	_Inout_  PEPROCESS              Process,
	_In_     HANDLE                 ProcessId,
	_In_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
) {
	NTSTATUS st = 0;
	HANDLE hProcess = NULL;
	OBJECT_ATTRIBUTES oa = { 0 };
	CLIENT_ID ClientId = { 0 };
	char xxx[16] = { 0 };
	if (CreateInfo != NULL) //进程创建事件 
	{
		DbgPrint("[monitor_create_process_x64][%ld]%s 创建进程: %wZ",
			CreateInfo->ParentProcessId,
			GetProcessNameByProcessId(CreateInfo->ParentProcessId),
			CreateInfo->ImageFileName);
		strcpy(xxx, PsGetProcessImageFileName(Process));
		if (!_stricmp(xxx, "calc.exe"))
		{
			DbgPrint("禁止创建计算器进程！");
			CreateInfo->CreationStatus = STATUS_UNSUCCESSFUL; //禁止创建进程 
		}
	}
	else
	{
		DbgPrint("[monitor_create_process_x64]进程退出: %s",PsGetProcessImageFileName(Process)); 
	}
}





NTSTATUS DriverEntry(
	_In_ struct _DRIVER_OBJECT *DriverObject,
	_In_ PUNICODE_STRING       RegistryPath
){

	PsSetCreateProcessNotifyRoutineEx(
		(PCREATE_PROCESS_NOTIFY_ROUTINE_EX)MyCreateProcessNotifyEx, FALSE);

	return STATUS_SUCCESS;
}
