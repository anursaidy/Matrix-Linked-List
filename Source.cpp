#include "Matrix.hpp"

int main() {
	
	int** arr = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[i] = new int [3];
			
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> arr[i][j];
		}
	}

	int** arr2 = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr2[i] = new int[3];

		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> arr2[i][j];
		}
	}



	Matrix<int> matrix(arr, 3, 3);
	Matrix<int> matrix2(arr2, 3, 3);

	matrix* matrix2;

}