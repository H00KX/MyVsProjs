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
	if (CreateInfo != NULL) //���̴����¼� 
	{
		DbgPrint("[monitor_create_process_x64][%ld]%s ��������: %wZ",
			CreateInfo->ParentProcessId,
			GetProcessNameByProcessId(CreateInfo->ParentProcessId),
			CreateInfo->ImageFileName);
		strcpy(xxx, PsGetProcessImageFileName(Process));
		if (!_stricmp(xxx, "calc.exe"))
		{
			DbgPrint("��ֹ�������������̣�");
			CreateInfo->CreationStatus = STATUS_UNSUCCESSFUL; //��ֹ�������� 
		}
	}
	else
	{
		DbgPrint("[monitor_create_process_x64]�����˳�: %s",PsGetProcessImageFileName(Process)); 
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
