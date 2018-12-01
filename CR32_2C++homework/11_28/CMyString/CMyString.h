#pragma once
class CMystring
{
public:
    /* ���ص�ǰ��������С*/
    inline int GetBufferSize() const;

    /* ���ص�ǰ�ַ�������*/
    inline int GetStrlen() const;

    /* ��ʽ���ַ���������������printf�����ǽ��������m_pStr��*/
    int Format(const char* strFormat, ...);

    /*
    CMystring str;
    str.Format("%s:%d", "127.0.0.1", "8080");
    "127.0.0.1:8080"
    */

    /* �Ƚ��ַ������ο�strcmp */
    int Cmp(const char* strSrc) const;
    int Cmp(const CMystring &strCmp) const;

    /* ����һ�������������С����ΪnMinBuffLen(���Դ���nMinBuffLen)�����GetBuffer(0)���򷵻�
    ��ǰ������*/
    char* GetBuffer(int nMinBuffLen);

    /* ��ȡ��ǰm_pStr
    */
    char* GetStr() const;

    /* ����CMyString�ַ���(ע�⿼�������õ��ַ���strSrc���ڵ�ǰ�����������)*/
    int SetStr(const char* strSrc);

    /* ����strCat����ǰ��������strcat*/
    void Cat(const char* strCat);
    void Cat(const CMystring &strCat);

    /* ��ʼ����������ʵ�ֲο���*/
    void InitSelf();
    /* �ͷ���������ʵ�ֲο��� */
    void ReleaseSelf();

    /* ���ַ���ȫ��תΪ��д */
    void ToUpper();
    /* ���ַ���ȫ��תΪСд */
    void ToLower();

private:
    int m_nBuffLen;
    int m_nStrLen;
    char *m_pStr;

};