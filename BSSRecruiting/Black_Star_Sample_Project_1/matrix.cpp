#include <iostream>
#include <vector>
#include <random>

#include "matrix.h"
#include "otherFunctions.h"

Matrix::Matrix()
{
    height = 0;
    width = 0;
    matrix.resize(height, std::vector<double>(width));
}
Matrix::Matrix(int h, int w)
{
    height = h;
    width = w;
    matrix.resize(h, std::vector<double>(w));
}

Matrix::~Matrix()
{
    matrix.clear();
    matrix.shrink_to_fit();
}

int Matrix::getHeight() { return height; }

int Matrix::getWidth() { return width; }

int Matrix::getSize() { return height * width; }

int Matrix::setHeight(int h) { height = h; }

int Matrix::setWidth(int w) { width = w; }

void Matrix::calculateSize() { matrix.resize(height, std::vector<double>(width)); }

void Matrix::fill(double d)
{
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++ )
                matrix[i][j] = d;
}

void Matrix::print()
{
    std::cout << (char)201 ;
    std::cout.width(width*5 + 1);
    std::cout << (char)187 << "\n";

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == 0)
                std::cout << (char)186;
            std::cout.width(5);
            if(j == width - 1)
                std::cout << matrix[i][j] << (char)186 << "\n";
            else
                std::cout << matrix[i][j];
        }
    }

    std::cout << (char)200;
    std::cout.width(width*5 + 1);
    std::cout << (char)188 << "\n";
}

void Matrix::fillWithRandomNumbers(int maxMinusOne, int shift)
{
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            matrix[i][j] = rand() % maxMinusOne + shift;
}

void Matrix::fillFromKeyboard()
{
    double input = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            std::cin >> input;
            matrix[i][j] = input;
            input = 0;
        }
    }
}

Matrix Matrix::operator + (Matrix mat)
{
    Matrix temp(mat.height, mat.width);
    if(height != mat.height || width != mat.width)
        std::cout << "ERROR\nMatrices MUST have the same dimensions for adding";
    else
    {
        for(int i = 0; i < height; i++)
            for(int j =0; j < width; j++)
                temp.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
    }
    return temp;
}

Matrix Matrix::operator - (Matrix mat)
{
    Matrix temp(mat.height, mat.width);
    if(height != mat.height || width != mat.width)
        std::cout << "ERROR\nMatrices MUST have the same dimensions for substaction.";
    else
    {
        for(int i = 0; i < height; i++)
            for(int j =0; j < width; j++)
                temp.matrix[i][j] = matrix[i][j] - mat.matrix[i][j];
    }
    return temp;
}

Matrix Matrix::operator * (Matrix mat)
{
    Matrix temp(height, mat.width);
    double sum = 0;
    int x = 0, y = 0;
    if(width != mat.height)
        std::cout << "ERROR\nCannot perform matrices multiplication. Number of columns in Matrix A must be equal to number of rows in column B.";
    else
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < mat.width; j++)
            {
                sum = 0;
                for(int k = 0; k < mat.height; k++)
                    sum += matrix[i][k] * mat.matrix[k][j];

                temp.matrix[i][j] = sum;
            }
        }
    }
    return temp;
}















