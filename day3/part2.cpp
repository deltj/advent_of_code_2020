/**
 * Given a map describing the locations of trees (#), identify the number of 
 * trees encountered by traversing a path from the top-left to the bottom right
 * with various slopes
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

int checkSlope(const cv::Mat &mat, int drow, int dcol)
{
    const int rows = mat.size().height;
    //std::cout << rows << std::endl;
    const int cols = mat.size().width;
    //std::cout << cols << std::endl;
    int treesHit = 0;
    int row = 0;
    int col = 0;
    for(int idx=0; row<rows; ++idx)
    {
        row = idx * drow;
        col = (idx * dcol) % cols;
        //std::cout << "checking " << row << "," << col << std::endl;
        if(mat.at<uchar>(row, col) == 1) treesHit++;
    }

    return treesHit;
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

    int rows = 0;
    int cols = testLine.length();
    cv::Mat treemat(rows, cols, CV_8UC1);

    std::string line;
    while(std::getline(ifs, line))
    {
        if(line.length() != cols)
        {
            std::cerr << "unexpected line length: " << line.length() << std::endl;
            break;
        }

        std::vector<unsigned char> row;
        for(int col=0; col<cols; ++col)
        {
            if(line.at(col) == '#')
            {
                //  This cell contains a tree
                //treemat.at<uchar>(row, col) = 1;
                row.push_back(1);
            }
            else
            {
                //  This cell does not contain a tree
                //treemat.at<uchar>(row, col) = 0;
                row.push_back(0);
            }
        }

        treemat.push_back(row);
        rows++;
    }
    std::cout << "rows: " << rows << std::endl;
    cv::Mat m = treemat.reshape(1, rows);
    std::cout << m.size() << std::endl;

    int th1 = checkSlope(m, 1, 1);
    std::cout << th1 << std::endl;
    int th2 = checkSlope(m, 1, 3);
    std::cout << th2 << std::endl;
    int th3 = checkSlope(m, 1, 5);
    std::cout << th3 << std::endl;
    int th4 = checkSlope(m, 1, 7);
    std::cout << th4 << std::endl;
    int th5 = checkSlope(m, 2, 1);
    std::cout << th5 << std::endl;

    std::cout << "result: " << th1 * th2 * th3 * th4 * th5 << std::endl;

    ifs.close();
}
