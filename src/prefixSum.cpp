#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector.hpp>
#include <sdsl/rank_support.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>

class prefSum
{
    private:
        sdsl::int_vector<> Array;
        sdsl::bit_vector BitMap;
        sdsl::rank_support_v<> rankB;
        sdsl::select_support_mcl<1> selectB1;
        sdsl::select_support_mcl<0> selectB0;

    public:
        prefSum(sdsl::int_vector<> Array)
        {
            this->Array = Array;
            int bitSize = 0;
            int cont = 0;

            for(int i=0; i<Array.size(); i++)
                bitSize +=Array[i] + 1;

            BitMap = sdsl::bit_vector(bitSize,0);

            for(int i=0; i<Array.size(); i++)
            {
                cont+= Array[i] + 1;
                BitMap[cont] = 1;
            }

            rankB = sdsl::rank_support_v<>(&BitMap);
            selectB1 = sdsl::select_support_mcl<1>(&BitMap);
            selectB0 = sdsl::select_support_mcl<0>(&BitMap);
        }

        int sum(int i)
        {
            return selectB1(i+1)-(i+1);
        }

        int search(int n)
        {
            return rankB(selectB0(n+1));
        }

        int size(){
            return Array.size();
        }
};

int main()
{
    int size = 16;
    srand((unsigned int)time(NULL));

    sdsl::int_vector<> Array = sdsl::int_vector<>(size+1, 0);

    for(int i = 1; i<Array.size(); i++)
            Array[i] = rand()%32 + 1;

    prefSum sumas = prefSum(Array);

    int cont = 0;
    for(int i=0; i<Array.size(); i++)
            std::cout << "Suma acumulada numero " << i << ": " << (cont+=Array[i]) << std::endl ;

    std::cout << std::endl;

    for(int i=0; i<sumas.size(); i++)
            std::cout << "sumas.sum(" << i << "): " << sumas.sum(i) << std::endl;

    std::cout << std::endl;

    for(int i = 1; i<sumas.size(); i++)
    {
        int a = rand()%20 * i;
        std::cout << "sumas.search(" << a << "): " << sumas.search(a) << std::endl;
    }

}