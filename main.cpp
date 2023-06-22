#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[])
{
    std::ifstream myfile;
    myfile.open(argv[1], std::ios::in);
    if (myfile.is_open() == false)
    {
        std::cout << "file " << argv[1] << " not opened" << std::endl;
        return 1;
    }

    std::string line;
    std::string str1 = "0 Zangdar";
    std::size_t pos = 0;
    std::size_t f1;
    int n = 0;

/*
    Rank Name                          Elo     +/-   Games   Score    Draw
       0 Zangdar 2.17.09               108      91      40   65.0%   35.0%

    On cherche toutes les lignes donnant un elo, et le delta
    Puis tracer 3 courbes : elo-delta/elo/elo+delta
*/

    while ( getline(myfile, line) )
    {
        f1 = line.find(str1, pos);
        if (f1 == std::string::npos)
        {
            continue;
        }

        std::stringstream ss(line);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> tokens(begin, end);

        if (tokens[4] != "nan")
        {
            int elo   = stoi(tokens[3]);
            int delta = stoi(tokens[4]);

            std::cout << n << " " << elo-delta << "  " << elo << "  " << elo+delta << std::endl;

            n++;
        }



    }

    /*
        Pour visualiser :

          ./a.out 2.1709-1.txt > log.dat
          xmgrace -nxy log.dat
          charger les paramètres (menu Plot/Load Parameters)
    */

    myfile.close();
    return 0;
}
