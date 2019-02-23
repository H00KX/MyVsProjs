#include <time.h> 

#include <windows.h> 

#include <iostream>

#include <stdio.h>  

#include <tchar.h>  

#include <fstream>

#include <queue>



#define MAX_KEY_LENGTH 255  

#define MAX_VALUE_NAME 16383  

DWORD dwType = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;

std::queue<std::wstring> keystack;



//#define COMMAND_OUTPUT



void query(HKEY rootKey, const wchar_t* path)

{

#ifdef COMMAND_OUTPUT

    _tprintf(TEXT("\nProcess: %s :\n"), path);

#endif

    HKEY hKey;

    if (RegOpenKeyEx(rootKey, path, 0, KEY_READ, &hKey) != ERROR_SUCCESS)

    {

        RegCloseKey(hKey);

        return;

    }



    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name  

    DWORD    cbName;                   // size of name string   

    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name   

    DWORD    cchClassName = MAX_PATH;  // size of class string   

    DWORD    cSubKeys = 0;               // number of subkeys   

    DWORD    cbMaxSubKey;              // longest subkey size   

    DWORD    cchMaxClass;              // longest class string   

    DWORD    cValues;              // number of values for key   

    DWORD    cchMaxValue;          // longest value name   

    DWORD    cbMaxValueData;       // longest value data   

    DWORD    cbSecurityDescriptor; // size of security descriptor   

    FILETIME ftLastWriteTime;      // last write time   



    DWORD i, retCode;



    TCHAR  achValue[MAX_VALUE_NAME];

    DWORD cchValue = MAX_VALUE_NAME;



    // Get the class name and the value count.   

    retCode = RegQueryInfoKey(

        hKey,                    // key handle   

        achClass,                // buffer for class name   

        &cchClassName,           // size of class string   

        NULL,                    // reserved   

        &cSubKeys,               // number of subkeys   

        &cbMaxSubKey,            // longest subkey size   

        &cchMaxClass,            // longest class string   

        &cValues,                // number of values for this key   

        &cchMaxValue,            // longest value name   

        &cbMaxValueData,         // longest value data   

        &cbSecurityDescriptor,   // security descriptor   

        &ftLastWriteTime);       // last write time   



                                 // Enumerate the subkeys, until RegEnumKeyEx fails.  

    if (cSubKeys)

    {

#ifdef COMMAND_OUTPUT

        printf("Number of subkeys: %d\n", cSubKeys);

#endif

        for (i = 0; i < cSubKeys; i++)

        {

            cbName = MAX_KEY_LENGTH;

            retCode = RegEnumKeyEx(hKey, i,

                                   achKey,

                                   &cbName,

                                   NULL,

                                   NULL,

                                   NULL,

                                   &ftLastWriteTime);

            if (retCode == ERROR_SUCCESS)

            {

#ifdef COMMAND_OUTPUT

                _tprintf(TEXT("(%d) %s\n"), i + 1, achKey);

#endif

                //use achKey to build new path and input it into stack.

                std::wstring newPath = L"";

                newPath.append(path);

                newPath.append(L"\\");

                newPath.append(achKey);

                keystack.push(newPath);

            }

        }

    }



    // Enumerate the key values.   

    if (cValues)

    {

#ifdef COMMAND_OUTPUT

        printf("Number of values: %d\n", cValues);

#endif

        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)

        {

            cchValue = MAX_VALUE_NAME;

            achValue[0] = '\0';

            unsigned char vari[70];

            retCode = RegEnumValue(hKey, i,

                                   achValue,

                                   &cchValue,

                                   NULL,

                                   NULL,

                                   NULL,

                                   NULL);

            if (retCode == ERROR_SUCCESS)

            {

                TCHAR szBuffer[255] = { 0 };

                DWORD dwNameLen = 255;

                DWORD rQ = RegQueryValueEx(hKey, achValue, 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);

                if (rQ == ERROR_SUCCESS)

                {

                    _tprintf(TEXT("(%d) %s %s\n"), i + 1, achValue, szBuffer);

                }



            }

        }

    }

    //release.

    RegCloseKey(hKey);

}



void regQuery(HKEY beginKey, TCHAR* path)

{

    //Begin to get HKEY of path.

    query(beginKey, path);

    while (!keystack.empty())

    {

        std::wstring newPath = keystack.front();

        keystack.pop();

        query(beginKey, newPath.c_str());

    }



    //Release.

    RegCloseKey(beginKey);

}



int _tmain(int argc, _TCHAR* argv[])

{



    regQuery(HKEY_CURRENT_USER, L"Control Panel");

    //fs.close();

    return 0;

}
