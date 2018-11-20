#include <ntddk.h>

BOOLEAN g_myKdDebuggerEnabled = TRUE;

//  KDdebuggerEnabled(fffff800`01c8e3f0)=fffff800`01a937c3+1fac2d
//fffff800`01a937bc 803d  2dac1f 0000       cmp     byte ptr [nt!KdDebuggerEnabled (fffff800`01c8e3f0)], 0
//fffff800`01a937c3 740b                 ie      nt!KeUpdateRunTime + 0xd0 (fffff800`01a937d0)
//fffff800`01a937c5 8b4324               mov     eax, dword ptr[rbx + 24h]

UCHAR sig_KDdebuggerEnabled[10] = { 0x80,0x3d,'?','?','?','?','?',0x74,0x0b,0x8b };

//错误方法。我的驱动和ntoskrl不在同一4GB地址内，无法直接从nt跳到我的驱动，因此需要想法在nt内申请我自己的变量
//nt!KeUpdateRunTime+0xbc:
//fffff800`01ad17bc 803d 3d28fa0880  cmp     byte ptr[fffff800`0aa74000], 80h
//fffff800`01ad17c3 0000            add     byte ptr[rax], al
//fffff800`01ad17c5 004324          add     byte ptr[rbx + 24h], al