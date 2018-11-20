#include <ntddk.h>


KIRQL WPOFFx64();
void WPONx64(KIRQL irql);

PVOID GetKeProcAddr(PCWSTR funName);
ULONGLONG SearchCode(PUCHAR StartAddr, int SearchLength, PUCHAR SigCode);