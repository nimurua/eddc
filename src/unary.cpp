#include <iostream>
#include "bits.hpp"

#define SIZE 24

int main()
{
    int arr[SIZE];
    int sum = 0;

    for(int i=0;i<SIZE; i++)
    {
        sum += (arr[i] = rand() % 7) + 1; 
    }

    uint8_t arrBit[(sum + 7)/8];
    sum = 0;

    for(int i=0;i<SIZE; i++)
    {
        BitSet(arrBit, (sum += (arr[i] + 1)));
    }

    printBitArray(arrBit, sum, 8);
}
