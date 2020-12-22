/**
 * Decode binary space partitioning airline seating assignments, 
 * and find your seat
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include <boost/algorithm/string.hpp>

void decode(const std::string &spec, int &row, int &col)
{
    if(spec.length() != 10) { return; }

    const std::string rowspec = spec.substr(0, 7);
    const std::string colspec = spec.substr(7, 3);

    row = 0;
    for(int i=0; i<7; ++i)
    {
        row <<= 1;

        //std::cout << rowspec.at(i) << std::endl;
        if(rowspec.at(i) == 'F')
        {
            row |= 0;
        }
        else
        {
            row |= 1;
        }
    }

    col = 0;
    for(int i=0; i<3; ++i)
    {
        col <<= 1;

        //std::cout << colspec.at(i) << std::endl;
        if(colspec.at(i) == 'R')
        {
            col |= 1;
        }
        else
        {
            col |= 0;
        }
    }
}

void usage()
{
    std::cout << "day5 <input.txt>" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    int row, col;

    struct seat
    {
        int row;
        int col;
        int id;
    };
    std::set<int> ids;

    std::ifstream ifs(argv[1], std::ifstream::in);
    std::string line;
    while(std::getline(ifs, line))
    {
        decode(line, row, col);
        int id = row * 8 + col;
        ids.insert(id);
    }

    int lastId = *(ids.begin()) - 1;
    for(std::set<int>::const_iterator it=ids.begin(); it!=ids.end(); ++it)
    {
        //std::cout << *it << std::endl;
        if(*it != lastId + 1) 
        {
            std::cout << "missing id might be: " << lastId + 1 << std::endl;
        }
        lastId = *it;
    }

    ifs.close();
}
