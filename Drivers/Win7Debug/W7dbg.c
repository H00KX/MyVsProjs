#include <ntddk.h>
#include "DbgVars.h"
#include "ToolsFun.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString) {
	
	ULONGLONG baseFunAddr = 0, VarAddrOpcd = 0, VarOffset = 0, BaseofOffset=0;
	
	baseFunAddr = (ULONGLONG)GetKeProcAddr(L"KeUpdateRunTime");
	VarAddrOpcd = SearchCode((PUCHAR)baseFunAddr, 0x100, &sig_KDdebuggerEnabled);
	DbgPrint("\n\nVarAddrOpcd is		%llx\n\n", VarAddrOpcd);
	DbgPrint("\n\nMyVarAddr is		%llx\n\n", &g_myKdDebuggerEnabled);
	
	BaseofOffset = VarAddrOpcd + 7;

	KIRQL l=WPOFFx64();
	*(PULONGLONG)(VarAddrOpcd + 2) = &g_myKdDebuggerEnabled - BaseofOffset;

	WPONx64(l);
	DbgBreakPoint();

	



	return STATUS_SUCCESS;
}