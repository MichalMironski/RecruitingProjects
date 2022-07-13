#include <iostream>
#include <vector>
class Matrix
{
private:
    unsigned int height, width;
    std::vector<std::vector<double>> matrix;
public:
    Matrix(); //Constructor - creates matrix 0x0, need to be set by setter later
    Matrix(int, int); //Create matrix of ints [height x width]
    ~Matrix(); //Destructor

    void print(); //Print matrix to console
    void fill(double); //Fill matrix with given number
    void fillWithRandomNumbers(int = 100, int = 1); //Fill matrix with random number (range, shift) - default (100,1)
    void fillFromKeyboard(); //Fill every matrix element from keyboard

    void calculateSize(); //Function to recalculate size
    //getters
    int getSize(); //Get size - height x width
    int getHeight();
    int getWidth();
    //setters
    int setHeight(int);
    int setWidth(int);

    Matrix operator * (Matrix);
    Matrix operator + (Matrix);
    Matrix operator - (Matrix);
};

