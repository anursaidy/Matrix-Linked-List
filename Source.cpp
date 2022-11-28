#include "Matrix.hpp"




int main() {
	/*
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
	}*/


	int** arr3 = new int* [2];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			arr3[i] = new int[2];

		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> arr3[i][j];
		}
	}
	
	/*int* arr4 = new int[9];
	for(int i = 0; i<9;i++)
	{
		cin >> arr4[i];
	}*/	
	//Matrix<int> matrix(arr, 3, 2);
	//Matrix<int> matrix2(arr2, 2, 3);
	//Matrix<int> matrix3;
	Matrix<int> matrix4(arr3, 2, 2);
	//matrix3 = matrix * matrix2;
	//cout << matrix3;
	matrix4.Delete();
	for (int i = 0; i < matrix4.numRows; i++)
	{
		for (int j = 0; j < matrix4.numCols; j++)
		{
			cout << matrix4.at(i, j) << " | ";
		}
		cout << endl;
	}

	
    //cout << "working";
return 0;
}