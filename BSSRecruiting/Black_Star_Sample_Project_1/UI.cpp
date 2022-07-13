#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "matrix.h"

void initializeMatrices();

void fillMenu(Matrix* m)
{
    int range = 0, shift = 0, fillNumber = 0;
    char fillingChoice = ' ';
                std::cout << "1. Fill manually from keyboard\n";
                std::cout << "2. Fill with random numbers\n";
                std::cout << "3. Fill with one number\n";
                std::cin >> fillingChoice;

                switch(fillingChoice)
                {
                case '1':
                    {
                        std::cout << "Filling matrix from keyboard. Separate numbers with spaces.\n";
                        m -> fillFromKeyboard();
                        break;
                    }
                case '2':
                    {
                        std::cout << "Enter range(e.g. 10: 0-9)\n";
                        std::cin >> range;
                        std::cout << "Enter shift(e.g. for range 10, shift = -5: -5:5)\n";
                        std::cin >> shift;
                        m -> fillWithRandomNumbers(range, shift);
                        break;
                    }
                case '3':
                    {
                        std::cout << "Enter number\n";
                        std::cin >> fillNumber;
                        m -> fill(fillNumber);
                        break;
                    }
                default:
                    std::cout << "Pick correct option.\n";
                    system("pause");
                    break;
                }
}


void operationsMenu(Matrix* A, Matrix* B)
{
    Matrix result;
    char operationChoice = ' ';
    std::cout << "Pick operation to perform (+/-/*)\n";
    std::cout << "If you want to make new matrices, enter 'n'\n";
    std::cout << "If you want to quit, enter 'x'\n";
    std::cin >> operationChoice;
    switch(operationChoice)
    {
    case '+':
        result = (*A) + (*B);
        break;
    case '-':
        result = (*A) - (*B);
        break;
    case '*':
        result = (*A) * (*B);;
        break;
    case 'n':
        system("cls");
        initializeMatrices();
        break;
    case 'x':
        exit(0);
        break;
    default:
        std::cout << "Pick correct option.\n";
        system("pause");
        operationsMenu(A, B);
        break;
    }
    std::cout << "\nResult\n";
    result.print();
    system("pause");
    operationsMenu(A, B);
}

void initializeMatrices()
{
    int firstMatrixHeight = 0, firstMatrixWidth = 0;
    int secondMatrixHeight = 0, secondMatrixWidth = 0;

    std::cout << "Enter A matrix dimensions separated with space\n";
    std::cin >> firstMatrixHeight;
    std::cin >> firstMatrixWidth;
    Matrix firstMatrix(firstMatrixHeight, firstMatrixWidth);
    fillMenu(&firstMatrix);

    std::cout << "Enter B matrix dimensions separated with space\n";
    std::cin >> secondMatrixHeight;
    std::cin >> secondMatrixWidth;
    Matrix secondMatrix(secondMatrixHeight, secondMatrixWidth);
    fillMenu(&secondMatrix);
    Sleep(500);
    system("cls");

    std::cout << "Matrix A\n";
    firstMatrix.print();
    std::cout << "Matrix B\n";
    secondMatrix.print();

    operationsMenu(&firstMatrix, &secondMatrix);
}
