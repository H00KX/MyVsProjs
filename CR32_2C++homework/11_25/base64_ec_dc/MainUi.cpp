#include <iostream>
#include <fstream>
#include <string>
#include "base64.h"

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;

int main()
{

    std::string PwStr = "test";
    char str[256] = "";

    //std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(MyStr.c_str()), MyStr.length());
    //std::string decoded = base64_decode(encoded);

    std::string encoded;
    fstream fsR;
    fstream fsW;
    fsR.open("测试账号.txt", ios::in);
    fsW.open("Encode.txt", ios::in | ios::out | ios::trunc);

    fsR.read(str, 3);
    int UnCount = 0;

    do
    {
        fsR.getline(str, 256);
        if (*str == '\0')
        {
            break;
        }
        UnCount = (int)strstr(str, "----") - (int)str;
        fsW.write(str, UnCount);
        fsW << "----";
        PwStr = (char*)((int)str + UnCount + 4);
        encoded = base64_encode(reinterpret_cast<const unsigned char*>(PwStr.c_str()), PwStr.length());
        fsW << encoded;
        fsW << endl;

    }
    while (UnCount > 0);


    fsW.close();
    fsR.close();

    // std::cout << "encoded :" << std::endl << encoded << std::endl;

    // std::cout << "decoded :" << std::endl << decoded << std::endl;

    system("pause");
}