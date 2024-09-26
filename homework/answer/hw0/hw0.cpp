#include <iostream>

int main(int argc, char *argv[])
{
    std::cout <<  "Hello World!" << std::endl;
    
    if (argc > 0)
    {
        for (int i = 0; i < argc; i++)
        {
            std::cout << i << ": " << argv[i] << std::endl; //name of executable is argv[0]
        }
    }
    else
    {
        std::cout << "No line arguments provided." << std::endl;
    }

    return 0;
}