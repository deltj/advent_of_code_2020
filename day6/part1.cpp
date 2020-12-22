/**
 * Count customs declaration answers
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include <boost/algorithm/string.hpp>

void usage()
{
    std::cout << "day6 <input.txt>" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1], std::ifstream::in);
    std::string line;
    std::set<char> groupCounter;
    int total = 0;
    while(std::getline(ifs, line))
    {
        std::cout << line << std::endl;

        //  Treat an empty line as a record separator
        if(line.length() == 0)
        {
            std::cout << "group count: " << groupCounter.size() << std::endl;
            total += groupCounter.size();
            groupCounter.clear();
        }
        else
        {
            for(int i=0; i<line.length(); ++i)
            {
                groupCounter.insert(line.at(i));
            }
        }
    }
    std::cout << "group count: " << groupCounter.size() << std::endl;
    total += groupCounter.size();

    std::cout << "total " << total << std::endl;

    ifs.close();
}
