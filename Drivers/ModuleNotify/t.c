#include <ntddk.h>
#include <ntimage.h>

PVOID GetDriverEntryByImageBase(PVOID ImageBase)
{
	PIMAGE_DOS_HEADER pDOSHeader; 
	PIMAGE_NT_HEADERS64 pNTHeader;
	PVOID pEntryPoint;
	pDOSHeader = (PIMAGE_DOS_HEADER)ImageBase;
	pNTHeader = (PIMAGE_NT_HEADERS64)((ULONG64)ImageBase + pDOSHeader->e_lfanew);
	pEntryPoint = (PVOID)((ULONG64)ImageBase +
	pNTHeader->OptionalHeader.AddressOfEntryPoint);
	return pEntryPoint;
}


VOID MyLoadImageNotifyRoutine
(
	__in_opt PUNICODE_STRING  FullImageName,
	__in HANDLE  ProcessId,
	__in PIMAGE_INFO  ImageInfo
)
{
	PVOID pDrvEntry;
	char szFullImageName[260] = { 0 };
	if (FullImageName != NULL && MmIsAddressValid(FullImageName))
	{
		if (ProcessId == 0)
		{
			DbgPrint("[LoadImageNotifyX64]%wZ\n", FullImageName);
			pDrvEntry = GetDriverEntryByImageBase(ImageInfo->ImageBase);
			DbgPrint("[LoadImageNotifyX64]DriverEntry: %p\n", pDrvEntry);
		}
	}
}





NTSTATUS DriverEntry(
	_In_ struct _DRIVER_OBJECT *DriverObject,
	_In_ PUNICODE_STRING       RegistryPath
) {

	PsSetLoadImageNotifyRoutine((PLOAD_IMAGE_NOTIFY_ROUTINE)MyLoadImageNotifyRoutine);
}