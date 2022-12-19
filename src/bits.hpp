#include <iostream>

// Tema 1 - Arreglo en base unaria

inline bool access(const uint8_t *e, const size_t p) 
{
    return 0 != ((e[p / 8] & (uint8_t) 1 << (8 - 1 - (p % 8))));
}

inline void BitSet(uint8_t *e, const size_t p) 
{
    e[p / 8] |= ((uint8_t) 1 << (8 - 1 - (p % 8)));
}


inline void BitClear(uint8_t *e, const size_t p) 
{
    e[p / 8] &= ~((uint8_t) 1 << (8 - 1 - (p % 8)));
}

/***Variacion de printBitArray que permite definir el tamaño de**** 
****los bloques a imprimir. Siempre imprime 6 bloques por linea***/ 

void printBitArray(const uint8_t *T, size_t T_size, size_t block) 
{
    for (int i = 0; i < T_size; i++) 
    {
        std::cout << access(T, i);
        if ((i + 1) % block == 0) 
        {
            std::cout << " ";
        } 
        if ((i + 1) % ((block * 6 )) == 0) 
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

// Tema 2 - 5bit blocks

/***Implementacion para bloques de 5 bits almacenados****
****en un arreglo de tipo uint8_t. *********************/

void bitsWrite(uint8_t *e, size_t p, size_t q, uint8_t x)
{
    e[(q - 1) / 8] |= x << 7 - ((q - 1) % 8);
    
    if(((p - 1) / 8) != ((q - 1) / 8))
        e[(p - 1) / 8] |= x >> q % 8;
}

uint8_t bitsRead(uint8_t* e, size_t p, size_t q)
{
    uint8_t x = e[(p - 1) / 8] << ((p - 1) % 8);

    if(((p - 1) / 8) != ((q - 1) / 8))
        x |= e[(q - 1) / 8] >> ((8 - (p - 1)) % 8);
    
    return (x >> 3);
}

void write(uint8_t* e, size_t i, uint8_t x)
{
    bitsWrite(e, (i * 5) + 1,((i + 1) * 5), x);
}

uint8_t read(uint8_t* e, size_t i)
{
    return(bitsRead(e, (i*5)+1,((i+1)*5)));
}
