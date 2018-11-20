#include "ToolsFun.h"

KIRQL WPOFFx64()
{
	KIRQL irql = KeRaiseIrqlToDpcLevel();
	UINT64 cr0 = __readcr0();
	cr0 &= 0xfffffffffffeffff;
	__writecr0(cr0);
	_disable();
	return irql;
}

void WPONx64(KIRQL irql)
{
	UINT64 cr0 = __readcr0();
	cr0 |= 0x10000;
	_enable();
	__writecr0(cr0);
	KeLowerIrql(irql);
}


PVOID GetKeProcAddr(PCWSTR funName) {
	UNICODE_STRING FunNameUnicode;

	RtlInitUnicodeString(&FunNameUnicode, funName);
	return MmGetSystemRoutineAddress(&FunNameUnicode);
}


ULONGLONG SearchCode(PUCHAR StartAddr, int SearchLength, PUCHAR SigCode) {
	PUCHAR endAddr = StartAddr + SearchLength;
	PUCHAR c = 0; int i = 0;	//c为当前搜索位置的那个字节
	UCHAR byte[10];		//byte当前搜索位置的10个字节暂时保持
	int flag = 0;			//尝试与10个特征字节匹配，全匹配则为1，有不匹配则为0
	for (c = StartAddr; c < StartAddr + SearchLength; c++) {
		for (i = 0; i < 10; i++) {
			byte[i] = *(c + i);

			if (SigCode[i] != '?') {
				flag = (byte[i] == SigCode[i]);
				if (!flag)
					break;
			}
		}

		if (flag)
			return (ULONGLONG)c;
	}
	return c = -1;

}


