#include <iostream>
#include <winsock2.h>
#include "Monster.h"
#include "Mon_Dog.h"

int main(int argc, char* argv[])
{
    {
        Monster *pmt =
            new Mon_Dog(5, 77);

        pmt->Move();
        pmt->Say();
    }

    std::cout << "main ui" << std::endl;

}

