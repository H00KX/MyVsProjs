// class_5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class AddrInfo
{
public:
    int nPubl;

    void showMap();

private:
    int nPriv;


protected:
    int nProt;

};



int main()
{
    AddrInfo a;
    a.showMap();

    return 0;
}

void AddrInfo::showMap()
{
    cout << "public nPubl: " << &nPubl << endl;
    cout << "private nPriv: " << &nPriv << endl;
    cout << "protect nProt: " << &nProt << endl;

}
