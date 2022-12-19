#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector.hpp>
#include <sdsl/rank_support.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>

class pHash
{
    private:
        sdsl::int_vector<> Array;
        sdsl::bit_vector BitMap;
        sdsl::rank_support_v<> rankB;

    public:
        pHash(sdsl::int_vector<> Array, sdsl::int_vector<> Keys)
        {
            this->Array = Array;

            BitMap = sdsl::bit_vector(Keys[Keys.size()-1],0);
            for(int i=1; i<Keys.size(); i++)
                BitMap[Keys[i]-1] = 1;

            rankB = sdsl::rank_support_v<>(&BitMap);
        }

        inline int getValue(int i)
        {
            return Array[rankB(i)-1];
        }

        inline int size()
        {
            return Array.size();
        }

        inline int bitMapSize()
        {
            return BitMap.size();
        }
};

int main()
{

    /* Tamano de los vectores y seed para aleatoriedad en la generacion de valores y claves*/

    int size = 64;
        srand((unsigned int)time(NULL));

    /*Array y claves generadas arbitrariamente, pHash asocia cada valor de Array con una clave en Keys */

    sdsl::int_vector<> Array = sdsl::int_vector<>(size, 0);
    sdsl::int_vector<> Keys = sdsl::int_vector<>(size+1, 0);

    /* Generando valores y su clave asociada */

    std::cout << "Valores y datos:" << std::endl << std::endl;

    for(int i =0; i<size; i++)
    {
        Array[i] = rand()%128;
        Keys[i+1] = rand()%8 + Keys[i] + 1;
        std::cout << "Value: " << Array[i] << " and Key: " << Keys[i+1] << std::endl;
    }

    /* Comprimiendo vector de valores y generando perfectHash */

    pHash perf = pHash(Array, Keys);

    std::cout << std::endl;
    std::cout << "Probando implementacion orientada a objetos: " << std::endl << std::endl;

    for(int i = 1; i<Keys.size(); i++)
        std::cout << "getValue(" << Keys[i] << "): " << perf.getValue(Keys[i]) << std::endl;

    std::cout << std::endl;
    std::cout << "El tamano del bitmap generado es de: " << perf.bitMapSize() << " bits. El valor de la clave mas alta en Keys" << std::endl;

}