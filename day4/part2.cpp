/**
 * Validate some passports
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

class Passport
{
public:
    Passport() :
        byr(0),
        iyr(0),
        eyr(0),
        hgt(0),
        hcl(""),
        ecl(""),
        pid(""),
        cid("")
    {}

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

            if(boost::contains(*it, "byr"))
            {
                p.byr = boost::lexical_cast<int>(rectokens[1]);
            }
            
            else if(boost::contains(*it, "iyr"))
            {
                p.iyr = boost::lexical_cast<int>(rectokens[1]);
            }

            else if(boost::contains(*it, "eyr"))
            {
                p.eyr = boost::lexical_cast<int>(rectokens[1]);
            }

            else if(boost::contains(*it, "hgt"))
            {
                if(boost::contains(rectokens[1], "cm"))
                {
                    std::string hgt = rectokens[1];
                    boost::replace_all(hgt, "cm", "");
                    p.hgt = boost::lexical_cast<int>(hgt);
                }
                else if(boost::contains(rectokens[1], "in"))
                {
                    std::string hgt = rectokens[1];
                    boost::replace_all(hgt, "in", "");
                    int hgt_in = boost::lexical_cast<int>(hgt);
                    p.hgt = hgt_in * 2.54; //  convert inches to cm
                }
            }

            else if(boost::contains(*it, "hcl"))
            {
                p.hcl = rectokens[1];
            }

            else if(boost::contains(*it, "ecl"))
            {
                p.ecl = rectokens[1];
            }

            else if(boost::contains(*it, "pid"))
            {
                p.pid = rectokens[1];
            }

            else if(boost::contains(*it, "cid"))
            {
                p.cid = rectokens[1];
            }
        }

        return p;
    }

    bool isValid() const {
        static boost::regex hcl_regex("#[0-9a-f]{6}");
        static boost::regex ecl_regex("amb|blu|brn|gry|grn|hzl|oth");
        static boost::regex pid_regex("[0-9]{9}");

        return byr >= 1920 && byr <= 2002 &&
               iyr >= 2010 && iyr <= 2020 &&
               eyr >= 2020 && eyr <= 2030 &&
               hgt >= 150 && hgt <= 193 &&
               boost::regex_match(hcl, hcl_regex) &&
               boost::regex_match(ecl, ecl_regex) &&
               boost::regex_match(pid, pid_regex);
    }

    int byr;
    int iyr;
    int eyr;
    int hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    std::string cid;

    int birthYear;
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
    int validPassports = 0;
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

            if(p.isValid())
            {
                std::cout << "valid" << std::endl << std::endl;
                validPassports++;
            }
            else
            {
                std::cout << "invalid" << std::endl << std::endl;
            }
        }
    }

    if(ifs.eof())
    {
        Passport p = Passport::parse(rec);
        passports.push_back(p);

        if(p.isValid())
        {
            std::cout << "valid" << std::endl;
            validPassports++;
        }
        else
        {
            std::cout << "invalid" << std::endl;
        }
    }

    std::cout << "read " << passports.size() << " passports" << std::endl;

    std::cout << validPassports << " valid" << std::endl;

    ifs.close();
}
