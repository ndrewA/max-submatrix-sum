#include <iostream>
#include <vector>

std::vector<std::vector<int>> makeSumMatrix(const std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>> sumMatrix;
    for(size_t i = 0; i < matrix.size(); i++) {
        sumMatrix.push_back(std::vector<int>(matrix.size()));
        for(size_t j = 0; j < matrix.size(); j++) {
            if(i == 0 && j == 0)
                sumMatrix[0][0] = matrix[0][0];

            else if(i == 0)
                sumMatrix[0][j] = sumMatrix[0][j-1] + matrix[0][j];

            else if(j == 0)
                sumMatrix[i][0] = sumMatrix[i-1][0] + matrix[i][0];

            else
                sumMatrix[i][j] = sumMatrix[i-1][j] + sumMatrix[i][j-1] - sumMatrix[i-1][j-1] + matrix[i][j];
        }
    }
    return sumMatrix;
}

int getSum(std::vector<std::vector<int>> sumMatrix, std::pair<size_t, size_t> corner1, std::pair<size_t, size_t> corner2)
{
    int curSum = sumMatrix[corner2.first][corner2.second];
    if(corner1.first > 0) curSum -= sumMatrix[corner1.first-1][corner2.second];
    if(corner1.second > 0) curSum -= sumMatrix[corner2.first][corner1.second-1];
    if(corner1.first > 0 && corner1.second > 0) curSum += sumMatrix[corner1.first-1][corner1.second-1];
    return curSum;
}

int findSum(const std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>> sumMatrix = makeSumMatrix(matrix);
    int maxSum = INT_MIN;

    for(size_t colIter = 0; colIter < matrix.size(); colIter++) {
        for(size_t len = 0; len < matrix.size()-colIter; len++) {
            int curSum = INT_MIN;
            for(size_t rowIter = 0; rowIter < matrix.size(); rowIter++) {
                int nextNum = getSum(sumMatrix, {rowIter, colIter}, {rowIter, colIter+len});

                if(curSum + nextNum > nextNum)
                    curSum += nextNum;

                else
                    curSum = nextNum;

                if(curSum > maxSum) maxSum = curSum;
            }
        }
    }
    return maxSum;
}


int main()
{
    std::vector<std::vector<int>> matrix {{0, -2, -7, 0},
                                          {9, 2, -6, 2 },
                                          {-4, 1, -4, 1},
                                          {-1, 8, 0, -2}};
    int res = findSum(matrix);
    std::cout << "==================\nRES = " << res << '\n';
    return 0;
}
