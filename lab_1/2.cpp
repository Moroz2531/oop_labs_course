#include <iostream>
#include <vector>
#include <time.h>

using std::cout, std::endl;

int** genRandMatrix(int size, int maxValue);
void printMatrix(int** matrix);
void freeMatrix(int **matrix);

int main()
{
    srand(time(NULL));

    int size= rand() % 10;
    int maxValue = 100;
    int** matrix = genRandMatrix(size, maxValue);

    printMatrix(matrix);
    freeMatrix(matrix);

    return 0;
}

int** genRandMatrix(int size, int maxValue)
{
    int** arr = new int* [size + 1];
    arr[0] = new int;
    arr[0][0] = size;

    for (int i = 1; i < size + 1; i++) {
        int cols = rand() % 10;
        arr[i] = new int[cols + 1];
        arr[i][0] = cols;

        for (int j = 1; j < cols + 1; j++) {
            arr[i][j] = rand() % maxValue;
        }
    }
    return arr;
}

void printMatrix(int **matrix)
{
    cout << matrix[0][0] << endl;

    for (int i = 1; i < matrix[0][0] + 1; i++) {
        cout << matrix[i][0] << ": ";

        for (int j = 1; j < matrix[i][0] + 1; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void freeMatrix(int **matrix)
{
    for (int i = 1; i < matrix[0][0] + 1; i++) {
        delete[] matrix[i];
    }
    delete matrix[0];
    delete[] matrix;
}
