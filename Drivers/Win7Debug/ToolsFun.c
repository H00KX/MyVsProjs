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
	PUCHAR c = 0; int i = 0;	//cΪ��ǰ����λ�õ��Ǹ��ֽ�
	UCHAR byte[10];		//byte��ǰ����λ�õ�10���ֽ���ʱ����
	int flag = 0;			//������10�������ֽ�ƥ�䣬ȫƥ����Ϊ1���в�ƥ����Ϊ0
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


