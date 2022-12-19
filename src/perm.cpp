#include <sdsl/bit_vectors.hpp>

class Permutation
{
    private:
        sdsl::int_vector<> Perm;
        sdsl::bit_vector BitMap;
        sdsl::int_vector<> Reverse;
        sdsl::rank_support_v<> rankB;

    public:
        Permutation(sdsl::int_vector<> Perm)
        {
            int cont = 0;
            this->Perm = Perm;
            BitMap = sdsl::bit_vector(Perm.size(), 0);
            Reverse = sdsl::int_vector<>(Perm.size(), 0);
            sdsl::int_vector<> temp = sdsl::int_vector<>(Perm.size(),0);

            for(int i=0; i<Perm.size(); i++)
            {
                int aux = Perm[i];
                if(aux != i)
                {
                    BitMap[aux] = 1;
                    temp[aux] = i;
                    cont++;
                }
            }

            Reverse = sdsl::int_vector<>(cont, 0);
            rankB = sdsl::rank_support_v<>(&BitMap);

            int j = 0;
            for(int i=0; i<Perm.size(); i++)
            {
                if(temp[i]!=0)
                {
                    Reverse[j] = temp[i];
                    j++;
                }
            }
        }

        int pi(int i)
        {
            return Perm[i];
        }

        int invPi(int i)
        {
            if(BitMap[i] == 1)
            {
                return Reverse[rankB(i)];
            }
            return Perm[i];
        }

        int size()
        {
            return Perm.size();
        }
};


int main()
{
    sdsl::int_vector<> Array = {0,1,4,2,7,6,3,9,8,10,5};
    Permutation perm = Permutation(Array);

    for(int i=0; i<perm.size(); i++
    )
    {
        std::cout << "pi.(" << i << "): " << perm.pi(i) << std::endl;
        std::cout << "invPi.(" << i << "): " << perm.invPi(i) << std::endl;
    }
}