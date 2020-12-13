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
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

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

        std::string bounds = tokens[0];
        std::string letter = tokens[1];
        std::string password = tokens[2];

        boost::replace_all(letter, ":", "");

        //std::cout << "bounds: " << bounds << std::endl;
        //std::cout << "letter: " << letter << std::endl;
        //std::cout << "password: " << password << std::endl;

        splitvec boundsTokens;
        boost::split(boundsTokens, bounds, boost::is_any_of("-"));

        if(boundsTokens.size() != 2) continue;

        std::stringstream ss;
        ss << letter << "{" << boundsTokens[0] << "," << boundsTokens[1] << "}";

        std::cout << "regex: " << ss.str() << std::endl;

        boost::regex e(ss.str());

        for(int i=97; i<123; ++i)
        {
            std::stringstream css;
            css << (char)i;
            std::string c = css.str();
            if(letter.compare(c) != 0)
            {
                boost::erase_all(password, c);
            }
        }
        std::cout << password << std::endl;

        if(boost::regex_match(password, e))
        {
            std::cout << "pass" << std::endl;
            validCounter++;
        }
        else
        {
            std::cout << "fail" << std::endl;
        }
    }

    std::cout << "Found " << validCounter << " valid passwords" << std::endl;

}
