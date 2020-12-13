/**
 * Given a list of numbers, find two that add up to 2020 and multiply them
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

void usage()
{
    std::cout << "day1 <input.txt>" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    std::vector<int> numbers;

    std::ifstream ifs(argv[1], std::ifstream::in);
    std::string line;
    int number;
    while(std::getline(ifs, line))
    {
        std::istringstream iss(line);
        iss >> number;
        numbers.push_back(number);
    }

    ifs.close();

    std::cout << "read " << numbers.size() << " numbers" << std::endl;

    size_t n = numbers.size();
    int a, b;
    for(int i=0; i<n; ++i)
    {
        a = numbers[i];
        for(int j=i+1; j<n; ++j)
        {
            b = numbers[j];

            if(a + b == 2020)
            {
                std::cout << "a=" << a << ",b=" << b << ",product=" << a * b << std::endl;
            }
        } 
    }
}
