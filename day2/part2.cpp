/**
 * Given a list of password policies and passwords, find passwords that do not
 * match their policy.
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include <boost/algorithm/string.hpp>

void usage()
{
    std::cout << "day2 <input.txt>" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    std::vector<std::string> pwRecords;

    std::ifstream ifs(argv[1], std::ifstream::in);
    std::string line;
    while(std::getline(ifs, line))
    {
        pwRecords.push_back(line);
    }

    ifs.close();

    std::cout << "read " << pwRecords.size() << " password records" << std::endl;

    int validCounter = 0;
    typedef std::vector<std::string> splitvec;
    for(std::vector<std::string>::const_iterator it=pwRecords.begin();
        it!=pwRecords.end(); ++it)
    {
        std::string record = *it;
        splitvec tokens;
        boost::split(tokens, record, boost::is_any_of(" "));

        if(tokens.size() != 3) continue;

        std::string indices = tokens[0];
        std::string letter = tokens[1];
        std::string password = tokens[2];

        boost::replace_all(letter, ":", "");

        //std::cout << "indices: " << indices << std::endl;
        //std::cout << "letter: " << letter << std::endl;
        //std::cout << "password: " << password << std::endl;

        splitvec indexTokens;
        boost::split(indexTokens, indices, boost::is_any_of("-"));

        if(indexTokens.size() != 2) continue;

        int index1, index2;
        std::istringstream tok1ss(indexTokens[0]);
        std::istringstream tok2ss(indexTokens[1]);
        tok1ss >> index1;
        tok2ss >> index2;

        char c = letter[0];
        bool found1 = (password.at(index1 - 1) == c);
        bool found2 = (password.at(index2 - 1) == c);
        if((found1 && !found2) || (found2 && !found1))
        {
            validCounter++;
        }
    }

    std::cout << "Found " << validCounter << " valid passwords" << std::endl;

}
