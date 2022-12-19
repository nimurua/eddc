#include "bits.hpp"

#define BITS 5
#define SIZE 20

int main()
{
    uint8_t A[] = {20, 18, 22, 22, 16, 21, 11, 23, 21, 21, 20, 18, 22, 22, 16, 21, 11, 23, 21, 21};
    uint8_t *B = new uint8_t[((BITS*SIZE)+31)/32]();

    for(int i = 0; i < SIZE; i++)
    {
        write(B, i, A[i]);
    }

    printBitArray(B, BITS*SIZE, 5);

    for(int i = 0; i < SIZE; i++)
    {
        std::cout << unsigned(read(B, i)) << " ";
    }
    std::cout << std::endl;    
}
