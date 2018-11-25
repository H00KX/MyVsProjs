#include <iostream>
#include "base64.h"

int main()
{
    const std::string MyStr = "qwerasdf";

    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(MyStr.c_str()), MyStr.length());
    std::string decoded = base64_decode(encoded);


    std::cout << "encoded :" << std::endl << encoded << std::endl;

    std::cout << "decoded :" << std::endl << decoded << std::endl;

    system("pause");
}