#include "Matrix.hpp"

int main() {
	
	int** arr = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			arr[i] = new int [2];
			
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> arr[i][j];
		}
	}

	int** arr2 = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr2[i] = new int[3];

		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> arr2[i][j];
		}
	}



	Matrix<int> matrix(arr, 3, 2);
	Matrix<int> matrix2(arr2, 2, 3);
	Matrix<int> matrix3;
	matrix3 = matrix * matrix2;
	

//std::cout << "working";
}