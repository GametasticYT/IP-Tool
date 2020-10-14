#include <iostream>
#include <cstdio>

// Check which OS to not run into errors when using clearScreen()
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
const std::string OS = "win";
#elif __linux__
const std::string OS = "linux";
#elif __unix__
const std::string OS = "unix";
#else
#error "Unknown Compiler"
#endif


std::string numToBitStr(unsigned short x);
void clearScreen();

int main()
{
    std::string hinweis = "nix";
    
    char IPaddr[15];
    
    // IP numbers
    unsigned short i_part1, i_part2, i_part3, i_part4;

    std::cout << "IP-Tool\n\n";

    // Take input from user
    std::cout << "Ip mit '.' getrennt eingeben: \n\n";
    std::cout << "> ";
    std::cin >> IPaddr;

    // divide IP-String to the IP Numbers
    sscanf(IPaddr, "%hu.%hu.%hu.%hu", &i_part1, &i_part2, &i_part3, &i_part4);

    // Strings to store the divided and decoded IP things
    std::string bit_part1;
    std::string bit_part2;
    std::string bit_part3;
    std::string bit_part4;
    

    // Convert all the IP-Address parts into binary strings
    bit_part1 = numToBitStr(i_part1);
    bit_part2 = numToBitStr(i_part2);
    bit_part3 = numToBitStr(i_part3);
    bit_part4 = numToBitStr(i_part4);

    // Erase the first 8 bits (and one space) bc they're empty 
    bit_part1.erase(0, 9);
    bit_part2.erase(0, 9);
    bit_part3.erase(0, 9);
    bit_part4.erase(0, 9);


    //Check if any number is bigger than 255 [Not possible bc 1111 1111 == 255]
    if (i_part1 > 255 || i_part2 > 255 || i_part3 > 255 || i_part4 > 255)
    {
        std::cout << "\nHm nö, ne IP-Adress-Part kann nicht über 255 sein :)" << std::endl;
        return 1;
    }
    else
    {   
        // If the first bit is 0 it's a Class-A network
        if (bit_part1[0] == '0')
        {
            // Extra checks
            std::cout << "Klasse: A" << std::endl;
            if (i_part2 == 0 && i_part3 == 0 && i_part4 == 0)
            {
                hinweis = "Netz-ID";
            }
            else if (i_part2 == 255 && i_part3 == 255 && i_part4 == 255)
            {
                hinweis = "Broadcast-Adresse";
            }
        }
        else if (bit_part1[1] == '0')
        {
            std::cout << "Klasse: B" << std::endl;
        }
        else if (bit_part1[2] == '0')
        {
            std::cout << "Klasse: C" << std::endl;
        }
        else if (bit_part1[3] == '0')
        {
            std::cout << "Klasse: D" << std::endl;
        }
        else
        {
            std::cout << "Klasse: E" << std::endl;
        }
    }
    if (!(hinweis == "nix"))
    {
        std::cout << "Hinweis: " << hinweis << std::endl;
    }
    return 0;
}


void clearScreen()
{
    if (OS == "win")
    {
        system("cls");
    }
    else if (OS == "linux" || OS == "unix")
    {
        system("clear");
    }
}

std::string numToBitStr(unsigned short x)
{
    int i;
    std::string outStr;
    for(i=8*sizeof(x)-1; i>=0; i--) {
        if (x & (1 << i))
        {
            outStr.append("1");
        } else {
            outStr.append("0");
        }
        if(i == 8 || i == 16 || i == 24 || i == 32)
        {
            outStr.append(" ");
        }
    }
    return outStr;
}