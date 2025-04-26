#include <iostream>
#include <time.h>

using std::cout, std::endl;

int* genRandArray(int size, int maxValue);
void print(int* arr);

int main()
{
    srand(time(NULL));

    int size = rand()%10;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);

    print(arr);
    delete[] arr;

    return 0;
}

int* genRandArray(int size, int maxValue)
{
	int* arr = new int [size + 1];

	arr[0] = size;
	for (int i = 1; i < arr[0] + 1; i++) {
		arr[i] = rand() % maxValue;
    }
	return arr;
}

void print(int* arr)
{
	cout << arr[0] << ": ";
	for (int i = 1; i < arr[0] + 1; i++)
		cout << arr[i] << ' ';
	cout << endl;
}
