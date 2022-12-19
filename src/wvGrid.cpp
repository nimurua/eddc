#include <sdsl/bit_vectors.hpp>
#include <sdsl/wavelet_trees.hpp>
#include <vector>
#include <iostream>

class waveletGrid
{
    private:

        sdsl::bit_vector map;
        sdsl::rank_support_v5<> rankB1;
        sdsl::rank_support_v5<0> rankB0;
        sdsl::select_support_mcl<1> selectB1;
        sdsl::select_support_mcl<0> selectB0;
        sdsl::wt_int<> wt;

    public:

        waveletGrid(std::vector<std::pair<int, int>> points, int gridSize)
        {
            //Crea int_vector con los valores de las filas y bit_vector para transformar de una grid a otra 
            
            sdsl::int_vector<> row = sdsl::int_vector<>(points.size(), 0);
            map = sdsl::bit_vector(points.size() + gridSize, 0);

            //Rellena el bitmap y el int_vector

            int col = 0;                    
            for(int i =0; i < points.size(); i++)
            {
                while(points[i].first > col)
                {
                    map[col + i] = 1;
                    col++;
                }
                row[i] = points[i].second;
            }            

            //Construye el Wavelet tree y los soportes Rank para la conversion entre grid en las consultas

            construct_im(wt, row);
            rankB1 = sdsl::rank_support_v5<>(&map);
            rankB0 = sdsl::rank_support_v5<0>(&map);
            selectB1 = sdsl::select_support_mcl<1>(&map);
            selectB0 = sdsl::select_support_mcl<0>(&map);

        };


        bool isIn(int x, int y)
        {
            //Obtener rango de columnas a evaluar

            int r1 = rankB0(selectB1(x));
            int r2 = rankB0(selectB1(x+1));

            //Comparar el valor en cada columna obtenida con la fila buscada. 

            for(r1; r1 < r2; r1++){
                if(wt[r1] == y){
                    return true;
                }
            }

            return false;
        }


        std::vector<std::pair<uint64_t,uint64_t>> rangeSearch(int x1, int x2, int y1, int y2)
        {
            //Obtiene los puntos en un rango. La conversion entre grids se realiza al pasar los parametros. 

            auto s = wt.range_search_2d(rankB0(selectB1(x1)), (rankB0(selectB1(x2)) + 1), y1, y2).second;
            
            //Transforma los puntos a la grid original

            for(int i = 0; i<s.size(); i++)
                s[i].first = rankB1(selectB0(s[i].first + 1));

            return s;
        }

};

int main()
{

    //Construccion

    static std::vector<std::pair<int, int>> points
    {
        {1,1},  {1,4},  {1,14}, {2,2},
        {2,12}, {3,3},  {3,6},  {4,10}, 
        {7,12}, {8,2},  {8,9},  {8,14}, 
        {9,7},  {9,11}, {10,5}, {10,8}
    };

    waveletGrid wvGrid = waveletGrid(points, 10);

    //Consulta por punto

    int x = 3;
    int y = 6;

    std::cout << "Comprobando la existencia de: (" << x << "," << y << ")" << std::endl;

    if(!wvGrid.isIn(x,y))
    {
        std::cout << "El punto ingresado se encuentra apagado" << std::endl;
    }else
    {
        std::cout << "El punto ingresado se encuentra encendido" << std::endl;
    }

    //Consulta por rango
    
    int x1 = 4;
    int x2 = 8;
    int y1 = 3;
    int y2 = 12;

    auto s = wvGrid.rangeSearch(x1,x2,y1,y2);
    
    std::cout << "Puntos en el area x1=" << x1 << " x2=" << x2 << " y1=" << y1 << " y2=" << y2 << ": " << std::endl;

    for(auto p: s)
    {
        std::cout << "(" << p.first << "," << p.second << ")" << std::endl;
    }

}

