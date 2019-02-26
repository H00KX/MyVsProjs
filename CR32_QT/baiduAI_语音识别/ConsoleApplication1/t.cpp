//// ���滻�����ص�C++SDK·��
//#include "speech.h"
//
//#include <iostream>
//#include <string>
//#include <windows.h>
//#include <wininet.h>
//#include <Shlwapi.h>
//#pragma comment(lib, "Shlwapi.lib")
//#pragma comment(lib, "Wininet.lib")
//
//void ASR(aip::Speech* client);
//
//void ASR_url(aip::Speech* client);
//
//void TTS(aip::Speech* client);
//
//std::string WcsToUtf8(const std::wstring &wcs)
//{
//    char* pElementText;
//    int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wcs.c_str(), -1, NULL, 0, NULL, NULL);
//    pElementText = new char[iTextLen + 1];
//    memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
//    ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wcs.c_str(), -1, pElementText, iTextLen, NULL, NULL);
//    std::string strReturn(pElementText);
//    delete[] pElementText;
//    return strReturn;
//}
//
//std::string GBToUTF8(const std::string &strgb2312)
//{
//    int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strgb2312.c_str(), -1, NULL, 0);
//    unsigned short * wszUtf8 = new unsigned short[len];
//    //memset(wszUtf8, 0, len * 2 );
//    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strgb2312.c_str(), -1, (LPWSTR)wszUtf8, len);
//
//    len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
//    char *szUtf8 = new char[len];
//    //memset(szUtf8, 0, len);
//    WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);
//
//    std::string strutf8 = szUtf8;
//    delete[] szUtf8;
//    delete[] wszUtf8;
//    return strutf8;
//}
//
//// Unicode ת����UTF-8
//void UnicodeToUTF_8(char* pOut, WCHAR* pText)
//{
//    char* pchar = (char *)pText;
//    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
//    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
//    pOut[2] = (0x80 | (pchar[0] & 0x3F));
//    return;
//}
//
//unsigned char ToHex(unsigned char x)
//{
//    return  x > 9 ? x + 55 : x + 48;
//}
//
//
//
//int main()
//{
//    // ����滻�ٶ��ƿ���̨���½��ٶ�����Ӧ�õ� Api Key �� Secret Key
//    aip::Speech * client = new aip::Speech("15614741", "e50de6j2kep7srqeoq60VlYi", "eowesEB53oOKKixR09jVaWfKGGdA7cW9");
//
//
//    //ASR(client);
//
//    //ASR_url(client);
//
//    TTS(client);
//
//    return 0;
//}
//
//
///**
//* TTS�����ϳ�ʾ��
//*/
//void TTS(aip::Speech* client)
//{
//    std::ofstream ofile;
//    std::string file_ret;
//    std::map<std::string, std::string> options;
//    options["spd"] = "5";
//    options["per"] = "2";
//
//    std::string strtext = GBToUTF8("���ǽ����꣬����CR32�����㡣�ҵ�tel��132110110");
//    ofile.open("./tts.mp3", std::ios::out | std::ios::binary);
//
//    Json::Value result = client->text2audio(strtext, options, file_ret);
//    // ���file_retΪ��Ϊ����˵���ϳɳɹ�������mp3�ļ�����
//    if (!file_ret.empty())
//    {
//        // �ϳɳɹ������ļ�
//        ofile << file_ret;
//        std::cout << "�����ϳɳɹ�����Ŀ¼�µ�tts.mp3�ļ�������" << std::endl;
//    }
//    else
//    {
//        // �ϳɳ�����ӡ������Ϣ
//        std::cout << result.toStyledString();
//    }
//}

#include <iostream>
#include <string>
#include <windows.h>
#include <wininet.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Wininet.lib")
#define MAXBLOCKSIZE 1024

bool downLoadFile(const char *Url, const TCHAR *ptFilePath)
{
    bool bret = false;
    HINTERNET hSession = InternetOpenA("RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hSession != NULL)
    {
        HINTERNET handle2 = InternetOpenUrlA(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
        if (handle2 != NULL)
        {
            //printf("%s\n",Url);
            byte Temp[MAXBLOCKSIZE] = { 0 };
            ULONG Number = 1;

            DWORD  dwBytesWritten;
            HANDLE hFile;

            // Open the file, creating it if necessary
            if (INVALID_HANDLE_VALUE !=
                (hFile = CreateFile(ptFilePath, GENERIC_WRITE, 0,
                                    NULL, CREATE_ALWAYS, 0, NULL)))
            {
                while (Number > 0)
                {
                    InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);

                    WriteFile(hFile, Temp, Number * sizeof(byte),
                              &dwBytesWritten, NULL);
                }
                CloseHandle(hFile);
            }

            InternetCloseHandle(handle2);
            handle2 = NULL;

            bret = true;
        }
        InternetCloseHandle(hSession);
        hSession = NULL;
    }
    return bret;
}

std::string WcsToUtf8(const std::wstring &wcs)
{
    char* pElementText;
    int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wcs.c_str(), -1, NULL, 0, NULL, NULL);
    pElementText = new char[iTextLen + 1];
    memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
    ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wcs.c_str(), -1, pElementText, iTextLen, NULL, NULL);
    std::string strReturn(pElementText);
    delete[] pElementText;
    return strReturn;
}

std::string GBToUTF8(const std::string &strgb2312)
{
    int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strgb2312.c_str(), -1, NULL, 0);
    unsigned short * wszUtf8 = new unsigned short[len];
    //memset(wszUtf8, 0, len * 2 );
    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strgb2312.c_str(), -1, (LPWSTR)wszUtf8, len);

    len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
    char *szUtf8 = new char[len];
    //memset(szUtf8, 0, len);
    WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);

    std::string strutf8 = szUtf8;
    delete[] szUtf8;
    delete[] wszUtf8;
    return strutf8;
}

// Unicode ת����UTF-8
void UnicodeToUTF_8(char* pOut, WCHAR* pText)
{
    char* pchar = (char *)pText;
    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));
    return;
}

unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

int main()
{
    TCHAR ptExePath[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, ptExePath, MAX_PATH);
    PathRemoveFileSpec(ptExePath);
    lstrcat(ptExePath, TEXT("\\"));
    lstrcat(ptExePath, TEXT("��˼.mp3"));

    std::string strurl("http://tsn.baidu.com//text2audio");
    std::string strtext = GBToUTF8("������˿,��ɣ����֦.666666666666666,��檶ϳ�ʱ,���粻��ʶ,����������?");
    //strtext = UrlEncode(strtext);
    //strurl += strtext;
    strurl += "?lan=zh&ie=UTF-8&spd=2&text=";
    strurl += strtext;
    DWORD dwStart = GetTickCount();
    downLoadFile(strurl.c_str(), ptExePath);
    DWORD dwEnd = GetTickCount();
    printf("��ʱ:%d����\n", dwEnd - dwStart);
    system("pause");
    return 0;
}