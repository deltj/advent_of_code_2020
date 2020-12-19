/**
 * Given a map describing the locations of trees (#), identify the number of 
 * trees encountered by traversing a path from the top-left to the bottom right
 * with a slope of -1/3.
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include <opencv2/core.hpp>

void usage()
{
    std::cout << "day3 <input.txt>" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1], std::ifstream::in);
    std::string testLine;
    std::getline(ifs, testLine);
    ifs.seekg(0, std::ios::beg);

    int rows = 1000;
    int cols = testLine.length();
    cv::Mat treemat(rows, cols, CV_8UC1);

    std::string line;
    int row = 0;
    while(std::getline(ifs, line))
    {
        if(line.length() != cols)
        {
            std::cerr << "unexpected line length: " << line.length() << std::endl;
            break;
        }

        for(int col=0; col<cols; ++col)
        {
            if(line.at(col) == '#')
            {
                //  This cell contains a tree
                treemat.at<uchar>(row, col) = 1;
            }
            else
            {
                //  This cell does not contain a tree
                treemat.at<uchar>(row, col) = 0;
            }
        }

        row++;
    }
    rows = row;

    std::cout << "read " << rows << " lines" << std::endl;

    int treesHit = 0;
    for(int row=0; row<rows; row += 1)
    {
        int col = (row * 3) % cols;
        std::cout << "checking row/col: " << row << "/" << col << std::endl;
        if(treemat.at<uchar>(row, col) == 1) treesHit++;
    }

    std::cout << "hit " << treesHit << " trees" << std::endl;

    ifs.close();
}
