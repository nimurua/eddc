#include <sdsl/bit_vectors.hpp>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;
using namespace sdsl;

class Louds
{
    private:

        vector<string> names;
        bit_vector map;
        select_support_mcl<0> selectB0;
        rank_support_v5<1> rankB1;

        void recursivePrint(int i, int k, int lvl)
        {
            while(map[k] != 0){
                for(int j=0;j<lvl;j++)
                        cout << "\t";

                cout << names[i] << endl;

                int pos = selectB0(rankB1(k)+1) + 1;
            
                if(map[pos])
                    recursivePrint(rankB1(pos), pos, lvl + 1);

                i++;
                k++;
            }
             
        }

    public:

        Louds(vector<string> names, vector<pair<string, string>> relations)
        {

            this->names = names;
            map = bit_vector(2*names.size() + 1,0);

            int j = 0;
            int cont = 2;
            map[0] = 1;
            
            for(int i = 0; i < names.size(); i++)
            {
                while(relations[j].first == names[i])
                {
                    map[cont] = 1;
                    cont++;
                    j++;
                }
                cont++;
            }

            selectB0 = select_support_mcl<0>(&map);
            rankB1 = rank_support_v5<1>(&map);

        }

        void print()
        {
            recursivePrint(0, 0,  0);
        }

        vector<string> subordinados(string name)
        {
            vector<string> subordinados;
            int i = 0;
            int n =0;

            while(names[i] != name){
                i++;
            };

            int pos = selectB0(i+1) + 1;
            i = rankB1(pos);

            while(map[pos]!=0)
            {
                subordinados.push_back(names[i]);
                i++;
                pos++;
            }

            return subordinados;
        }

        bool esJefe(string leader, string sub)
        {
            int i = 0;
            int n =0;

            while(names[i] != leader){
                i++;
            };

            int pos = selectB0(i+1) + 1;
            i = rankB1(pos);

            while(map[pos]!=0)
            {
                if(names[i] == sub)
                {
                    return true;
                }

                i++;
                pos++;
            }

            return false;
        }

};

int main()
{
    //Cargos representados por una letra.

    vector<string> names = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};

    //Relaciones Jerarquicas. (x, y) = x ---> y

    vector<pair<string, string>> relations = {{"A","B"},{"A","C"},{"A","D"},{"B","E"},{"B","F"},{"C","G"},{"G","H"},{"G","I"}};

    //Construccion

    Louds louds = Louds(names, relations);

    //Impresion

    cout << "Representacion de arbol sucinto construido: " << endl << endl;

    louds.print();

    //Busqueda de subordinados directos

    string leader = "A";

    auto subordinados = louds.subordinados(leader);

    cout << endl;
    cout << "Subordinados de " << leader << ": ";

    for(int i=0; i<subordinados.size(); i++)
    {
        cout << subordinados[i] << ", ";
    }

    cout << "\b\b " << endl << endl;

    //Consulta de Jefe
    
    leader = "G";
    string sub = "H";

    cout << "Comprobando si " << leader << " es jefe de " << sub << endl << endl;

    if(louds.esJefe(leader, sub)){
        cout << "Si es jefe" << endl;
    }else
    {
        cout << "No es jefe" << endl;
    }
        
}