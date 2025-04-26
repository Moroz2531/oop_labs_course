#include <iostream>
#include <time.h>

#define MAX_ROWS 6
#define MAX_VALUE 100

using std::cout, std::endl;

void spiralBegin(int* arr, int** matrix, int size) // 4 задание
{
    int start = 0, end = size - 1, indx = 0;

    while (end > 0) {
        for (int i = start; i <= end; i++)
            arr[indx++] = matrix[start][i];

        for (int i = start + 1; i <= end; i++)
            arr[indx++] = matrix[i][end];

        for (int i = end - 1; i >= start; i--)
            arr[indx++] = matrix[end][i];

        for (int i = end - 1; i >= start + 1; i--)
            arr[indx++] = matrix[i][start];

        end--;
        start++;
    }
}

void spiralCenter(int* arr, int** matrix, int size) // 3 задание
{
    int i = 1, indx = 0, x = size / 2, y = size / 2;

    arr[indx++] = matrix[x][y];
    while (i < size)
    {      
        if (i % 2 == 1) {
            for (int j = 0; j < 2 * i; j++) {
                (j < (2 * i) / 2) ? y-- : x--;
                arr[indx++] = matrix[x][y];
            }
        } else {
            for (int j = 0; j < 2 * i; j++) {
                (j < (2 * i) / 2) ? y++ : x++;
                arr[indx++] = matrix[x][y];
            }
        }
        i++;
    }
    for (int j = 1; j < size; j++) {
        (size % 2 == 0) ? y++ : y--; 
        arr[indx++] = matrix[x][y];
    }
}

void leftDiag(int* arr, int** matrix, int size) // 2 задание
{
    int count_iter = size * 2, indx = 0;
    for (int k = 0; k < count_iter; k++) {
        if (k < (count_iter / 2)) {
            for (int x = 0, y = k; y >= 0;) 
                arr[indx++] = matrix[x++][y--];
        } else {
            for (int x = k - size + 1, y = size - 1; x < size;)
                arr[indx++] = matrix[x++][y--];
        }
    }
}

void rightDiag(int* arr, int** matrix, int size) // 1 задание
{
    int count_iter = size * 2, indx = 0;
    for (int k = 0; k < count_iter; k++) {
        if (k < (count_iter / 2)) {
            for (int x = 0, y = (size - 1) - k; (x < size) && (y < size);) 
                arr[indx++] = matrix[x++][y++];
        } else {
            for (int x = k - (size - 1), y = 0; (x < size) && (y < size - 1);)
                arr[indx++] = matrix[x++][y++];
        }
    }
}

int **genRandMatrix(int size) // создание матрицы
{
    int **matrix = new int* [size];

    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % MAX_VALUE;
    }
    return matrix;
}

void print(int size, int* arr, int** matrix=nullptr) 
{
    for (int i = 0; i < size * size; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl << endl;

    if (matrix == nullptr)
        return;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl << endl;
}

void deleteMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void deleteArray(int *arr)
{
    delete[] arr;
}

int main()
{
    srand(time(NULL));

    int size = 1 + rand() % MAX_ROWS;
    if (size < 1)
        return 1;

    int **matrix = genRandMatrix(size);
    int *array = new int[size * size];

    rightDiag(array, matrix, size); 
    print(size, array, matrix);
    
    leftDiag(array, matrix, size);
    print(size, array); 

    if (size > 2) {
        spiralCenter(array, matrix, size);
        print(size, array);

        spiralBegin(array, matrix, size);
        print(size, array);
    }

    deleteArray(array);
    deleteMatrix(matrix, size);

    return 0;
}
