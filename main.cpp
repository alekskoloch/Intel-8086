#include "Headers/headers.h"
#include "Intel8086.h"

int main()
{
    Intel8086 intel8086;
    intel8086.run();

    std::cout << "EXIT_SUCCES" << "\n";
    return EXIT_SUCCESS;
}