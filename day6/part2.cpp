/**
 * Count customs declaration answers
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>

bool everyoneSaysYes(std::vector<std::set<char> > responses, char q)
{
    for(std::vector<std::set<char> >::const_iterator it=responses.begin(); it!=responses.end(); ++it)
    {
        if(it->count(q) == 0)
        {
            return false;
        }
    }

    return true;
}

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
    int total = 0;
    std::vector<std::set<char> > groupResponse;
    while(std::getline(ifs, line))
    {
        std::set<char> singleResponse;

        //  Treat an empty line as a record separator
        if(line.length() == 0)
        {
            int groupCount = 0;

            if(groupResponse.size() > 0)
            {
                //  Loop over the first person's responses; any question that 
                //  everyone in the group responded 'yes' to will be in this set
                for(std::set<char>::const_iterator it=groupResponse[0].begin(); it!=groupResponse[0].end(); ++it)
                {
                    if(everyoneSaysYes(groupResponse, *it))
                    {
                        groupCount++;
                    }
                }
            }

            groupResponse.clear();
            std::cout << "group count: " << groupCount << std::endl;
            std::cout << "-----------------------" << std::endl;

            total += groupCount;
        }
        else
        {
            std::cout << line << std::endl;

            for(int i=0; i<line.length(); ++i)
            {
                singleResponse.insert(line.at(i));
            }
            groupResponse.push_back(singleResponse);
        }
    }

    int groupCount = 0;

    if(groupResponse.size() > 0)
    {
        //  Loop over the first person's responses; any question that 
        //  everyone in the group responded 'yes' to will be in this set
        for(std::set<char>::const_iterator it=groupResponse[0].begin(); it!=groupResponse[0].end(); ++it)
        {
            if(everyoneSaysYes(groupResponse, *it))
            {
                groupCount++;
            }
        }
    }

    groupResponse.clear();
    std::cout << "group count: " << groupCount << std::endl;
    std::cout << "-----------------------" << std::endl;

    total += groupCount;

    std::cout << "total " << total << std::endl;

    ifs.close();
}
