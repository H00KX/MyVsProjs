#include <iostream>

/*
    6. ����һ��������ʹ����char&���������޸ĸò�������main()�����
    ��ӡһ��char������ʹ���������������������������Ƶĺ�����
    Ȼ���ٴδ�ӡ�˱�����֤�����ѱ��ı䡣������Ӱ���˳���Ŀɶ�����

*/


void fun(char &pc)
{
    pc += 1;
}

int main()
{
    char ch = 'a';
    printf("%c", ch);

    fun(ch);
    printf("%c", ch);

}