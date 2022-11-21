#include "Matrix.hpp"

//template <typename TwoD>
//void fill(TwoD& matrix)
//{
//	unsigned int counter = 1;
//	for (unsigned int i = 0; i < rows; i++)
//	{
//		for (unsigned int j = 0; j < columns; j++)
//		{
//			matrix[i][j] = counter++;
//		}
//	}
//}

int main() {
	//
	//int** arr = new int*[3];
	//for (int i = 0; i < 2; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		arr[i] = new int [3];
	//		
	//	}
	////}


	int arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> arr[i][j];
		}
	}


	/*int arr[3][3];
	fill(arr);*/


	Matrix<int> matrix(arr, 3, 3);
	Matrix<int> matrix2(arr, 3, 3);

	matrix* matrix2;

}