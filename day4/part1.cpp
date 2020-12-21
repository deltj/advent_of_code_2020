/**
 * Validate some passports
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include <boost/algorithm/string.hpp>

class Passport
{
public:
    static Passport parse(const std::string &rec) {
        Passport p;

        std::vector<std::string> tokens;
        boost::split(tokens, rec, boost::is_any_of(" "));

        for(std::vector<std::string>::const_iterator it=tokens.begin(); it!=tokens.end(); ++it)
        {
            std::vector<std::string> rectokens;
            boost::split(rectokens, *it, boost::is_any_of(":"));

            if(rectokens.size() != 2)
            {
                continue;
            }

            if(it->find("byr") != std::string::npos)
            {
                p.byr = rectokens[1];
            }
            
            else if(it->find("iyr") != std::string::npos)
            {
                p.iyr = rectokens[1];
            }

            else if(it->find("eyr") != std::string::npos)
            {
                p.eyr = rectokens[1];
            }

            else if(it->find("hgt") != std::string::npos)
            {
                p.hgt = rectokens[1];
            }

            else if(it->find("hcl") != std::string::npos)
            {
                p.hcl = rectokens[1];
            }

            else if(it->find("ecl") != std::string::npos)
            {
                p.ecl = rectokens[1];
            }

            else if(it->find("pid") != std::string::npos)
            {
                p.pid = rectokens[1];
            }

            else if(it->find("cid") != std::string::npos)
            {
                p.cid = rectokens[1];
            }
        }

        return p;
    }

    bool isValid() const {
        return byr.length() > 0 &&
               iyr.length() > 0 &&
               eyr.length() > 0 &&
               hgt.length() > 0 &&
               hcl.length() > 0 &&
               ecl.length() > 0 &&
               pid.length() > 0;
    }

    std::string byr;
    std::string iyr;
    std::string eyr;
    std::string hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    std::string cid;
};

void usage()
{
    std::cout << "day4 <input.txt>" << std::endl;
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
    std::string rec;
    std::vector<Passport> passports;
    while(std::getline(ifs, line))
    {
        rec.append(line);
        rec.append(" ");

        //  Treat an empty like as a record separator
        if(line.length() == 0)
        {
            //  We've accumulated a full passport record, parse it
            std::cout << "record: " << rec << std::endl;
            Passport p = Passport::parse(rec);
            passports.push_back(p);
            rec.clear();
        }
    }

    if(ifs.eof())
    {
        Passport p = Passport::parse(rec);
        passports.push_back(p);
    }


    std::cout << "read " << passports.size() << " passports" << std::endl;

    int validPassports = 0;
    for(std::vector<Passport>::const_iterator it=passports.begin(); it!=passports.end(); ++it)
    {
        if(it->isValid())
        {
            validPassports++;
        }
    }

    std::cout << validPassports << " valid" << std::endl;

    ifs.close();
}
