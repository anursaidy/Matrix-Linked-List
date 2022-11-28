#include "Matrix.hpp"


template<typename T>
Matrix<T>::Matrix()
{
	headMatrix = nullptr;
	rowsOfMatrix = nullptr;
	numRows = 0;
	numCols = 0;
}

template <typename T>
Matrix<T>::Matrix(T** arr, int r, int c)
{

	numRows = r;
	numCols = c;

	if (*arr == nullptr)
		throw invalid_argument("Input arr is empty"); //error;


	Node<T>* newNode = new Node<T>(arr[0][0]);
	headMatrix = newNode;
	rowsOfMatrix = new Node<T>*[numRows];  //seperating each rows.
	//newRow[0] = firstNode;

	//Store each rowsOfMatrix[i] with its corresponding Rows and each of their ->nextInRow
	for (int i = 0; i < numRows; i++)
	{
		if (newNode != headMatrix) {
			newNode = new Node<T>(arr[i][0]);//First Node of each row
		}
		rowsOfMatrix[i] = nullptr;
		for (int j = 0; j < numCols; j++) {
			if (rowsOfMatrix[i] == nullptr) {
				rowsOfMatrix[i] = newNode;
			}
			else {
				newNode->nextInRow = new Node<T>(arr[i][j]);
				newNode = newNode->nextInRow;
			}
		}
	}

	//Assigning nextInColumn
	for (int i = 0; i < numRows; i++)
	{
		Node<T>* temp = rowsOfMatrix[i];
		Node<T>* temp2 = rowsOfMatrix[i + 1];

		while (temp->nextInRow != nullptr) {
			if (i != numRows - 1) { //not last row
				rowsOfMatrix[i]->nextInColumn = rowsOfMatrix[i + 1];
				temp->nextInRow->nextInColumn = temp2->nextInRow;

				temp2 = temp2->nextInRow;
				temp = temp->nextInRow;
			}
			else {
				break;
			}
		}
	}
}

template <typename T>
Matrix<T>::~Matrix()
{

	if (headMatrix != nullptr) {
		Delete();
	}

}


template <typename T>
Matrix<T>::Matrix(const Matrix<T>& obj)
{
	if (obj.headMatrix != nullptr)
		Copy(obj);

}

template <typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& obj) {

	if (this != &obj) {

		cout << rowsOfMatrix[0]->nextInRow->value;
		Delete();
		Copy(obj);
	}
	return *this;
}


template <typename T>
void Matrix<T>::Delete() {

	if (headMatrix == nullptr) {
		return;
	}

	Node <T>* nodeToDelete = nullptr, * prev = nullptr;

	nodeToDelete = prev = getRow(0);

	int currentRow = 0;


	while (currentRow < numRows) {

		if (nodeToDelete->nextInRow == nullptr) {

			prev->nextInRow = prev->nextInColumn = nullptr;
			delete prev;
			currentRow++;
			if (currentRow < numRows)
				nodeToDelete = prev = (getRow(currentRow));
			else
				break;
		}

		nodeToDelete = nodeToDelete->nextInRow;


		
		prev->nextInRow = prev->nextInColumn = nullptr;
		delete prev;   

		prev = nodeToDelete;

	}


}

template <typename T>
void Matrix<T>::Copy(const Matrix<T>& obj) {

	// ** newRow

	numRows = obj.numRows;
	numCols = obj.numCols;

	MatrixIterator<T> RowIterator(obj.getRow(0));
	rowsOfMatrix = new Node<T>*[obj.numRows];

	Node<T>* current = nullptr;
	int indexOfRow = 0;
	for (int rowsCount = 0; rowsCount < obj.numRows; RowIterator++) {


		//end of my row
		if (indexOfRow == obj.numCols) {
			rowsCount++;
			indexOfRow = 0;


			if (rowsCount == obj.numRows) {
				current = nullptr;
				break;
			}

			RowIterator = obj.getRow(rowsCount);



		}

		Node<T>* newNode = new Node<T>(*RowIterator);



		if (indexOfRow > 0) {

			current->nextInRow = newNode;
			current = newNode;
			indexOfRow++;
		}

		if (indexOfRow == 0) {

			rowsOfMatrix[rowsCount] = current = newNode;
			indexOfRow++;



		}

	}

	headMatrix = rowsOfMatrix[0];


	// Connect eachrow

	MatrixIterator<T> iteratorRow1;
	MatrixIterator<T> iteratorRow2;


	indexOfRow = 0;
	for (int rowsCount = 0; (rowsCount < numRows - 1 && iteratorRow1 != nullptr); iteratorRow1++, iteratorRow2++) {



		if (indexOfRow == 0) {

			iteratorRow1 = rowsOfMatrix[rowsCount];
			iteratorRow2 = rowsOfMatrix[rowsCount + 1];
		}

		if (indexOfRow == numCols) {

			indexOfRow = 0;
			rowsCount++;

		}
		else {

			iteratorRow1.getCurrent()->nextInColumn = iteratorRow2.getCurrent();
			indexOfRow++;


		}




	}




}

template <typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& obj) {
	if (this != &obj) {
		numRows = obj.numRows;
		numCols = obj.numCols;

		headMatrix = obj.headMatrix;
		rowsOfMatrix = obj.rowsOfMatrix;

		obj.headMatrix = nullptr;
		obj.rowsOfMatrix = nullptr;
		//
		obj.numCols = 0;
		obj.numRows = 0;

	}
	return *this;


}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& obj) {

	if (obj.headMatrix != nullptr) {
		numRows = obj.numRows;
		numCols = obj.numCols;

		headMatrix = obj.headMatrix;
		rowsOfMatrix = obj.rowsOfMatrix;

		obj.headMatrix = nullptr;
		obj.rowsOfMatrix = nullptr;
		//
		obj.numCols = 0;
		obj.numRows = 0;
	}

}


template <typename T>
Node<T>* Matrix<T>::getRow(int i) const {
	return rowsOfMatrix[i];
}

template <typename T>
Node<T>* Matrix<T>::getColumn(int i) const {
	Node<T>* temp = rowsOfMatrix[0];
	for (int indexOfCol = 0; indexOfCol < i; temp = temp->nextInRow, indexOfCol++)
		;//blank statement
	return temp;
}

template <typename T>
T Matrix<T>::at(int const row, int const col) {
	Node<T>* temp = rowsOfMatrix[row];
	int count = 0;
	while (count < col) {
		temp = temp->nextInRow;
		count++;
	}
	return temp->value;
}

template <typename T>
bool Matrix<T>::addNewRow(Matrix<T>& object, Node<T>* headRow, int newRows, int i, int newCols) {

	// i would change to a matrix itertor
	if (i == 0) {
		object.rowsOfMatrix = new Node<T>*[newRows];
		object.headMatrix = headRow;
		object.numRows = newRows;
		object.numCols = newCols;
	}

	object.rowsOfMatrix[i] = headRow;



	if (i != 0) {
		// i would like to use here matrix iterator
		Node<T>* prevRow, * currentRow = nullptr;
		prevRow = object.rowsOfMatrix[(i - 1)];
		currentRow = object.rowsOfMatrix[i];

		for (int j = 0; j < object.numCols; j++) {
			prevRow->nextInColumn = currentRow;
			prevRow = prevRow->nextInRow;
			currentRow = currentRow->nextInRow;

		}

		currentRow = nullptr;




		return true;

	}
	else {

		return true;
	}



}

template <typename T>
Matrix<T>& Matrix<T>::transpose() {

	Matrix<T> temporalMatrix;
	MatrixIterator<T> columnIterator(getColumn(0));
	Node<T>* headRow = nullptr;
	Node<T>* current = nullptr;


	int indexOfColumn = 0;
	for (int colCounter = 0; colCounter < numCols; columnIterator++) {

		if (indexOfColumn == numRows) {
			indexOfColumn = 0;
			colCounter++;
			columnIterator = getColumn(colCounter);

			if (!addNewRow(temporalMatrix, headRow, numCols, colCounter - 1, numRows))
			{
				throw runtime_error("Error in transaction");
				current = nullptr;
			}

			if (colCounter == numCols) {
				break;
			}

		}

		Node<T>* newNode = new Node<T>(*columnIterator);



		if (indexOfColumn == 0) {
			headRow = current = newNode;
			indexOfColumn++;

		}

		if (indexOfColumn > 0) {
			current->nextInRow = newNode;
			current = newNode;
			indexOfColumn++;
		}
	}
	return temporalMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& obj) {
	if (numRows != obj.numRows || numCols != obj.numCols)
		throw invalid_argument("Matrix is not compatible.");

	if (headMatrix == nullptr) //if matrix is empty then return the empty matrix
		return *this;

	for (int indexOfRow = 0; indexOfRow < numRows; indexOfRow++)
	{
		MatrixIterator curIter(rowsOfMatrix[indexOfRow]);
		MatrixIterator objIter(obj.rowsOfMatrix[indexOfRow]);
		for (int indexOfCol = 0; indexOfCol < numCols; indexOfCol++)
		{
			*curIter = *curIter + *objIter;
			curIter++;
			objIter++;
		}
	}
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& obj) {

	//If not using iterator
	/*  Node<T>* rowsM;
		  Node<T>* colsM;*/

		  //Create a dynamic array for new matrix
	int** arr = new int* [numRows];
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			arr[i] = new int[numCols];

		}
	}

	int sum = 0;
	int j = 0;
	for (int i = 0; i < numRows; )
	{
		//Has to remain in the same row until we iterate through all columns of the obj
		if (j == obj.numCols) {

			i++;
			j = 0;
		}

		//Without Iterators: 
	   /* rowsM = getRow(i);
		colsM = obj.getColumn(j);*/

		//With Iterators
		MatrixIterator<T> rowIterator(getRow(i));
		MatrixIterator<T> columnIterator(obj.getColumn(j));

		while (columnIterator != nullptr) {
			//With Iterators
			sum += *rowIterator * *columnIterator;
			rowIterator++;
			columnIterator.Down();

			//Without Iterators
		   /* sum += rowsM->value * colsM->value;
			rowsM = rowsM->nextInRow;
			colsM = colsM->nextInColumn;*/

		}

		//Assigning sum to array
		arr[i][j] = sum;

		//Resetting sum for next row
		sum = 0;

		//At the end of the matrix
		if (i == numRows - 1 and j == obj.numCols - 1) {
			break; //end
		}
		j++;

	}
	//A new matrix with values of arr
	return Matrix(arr, numRows, numCols);
}


template <typename T>
ostream& operator<< (ostream& out, const Matrix<T>& matrix) {
	ostream_iterator<T> os(out);

	int j = 0;
	MatrixIterator<T> RowIterator(matrix.headMatrix);
	while (j < matrix.numRows - 1) {


		//temp = RowIterator.getCurrent();
		if (RowIterator.getCurrent()->nextInRow == nullptr)
		{
			j++;

			RowIterator = matrix.rowsOfMatrix[j];
			*os << endl;
		}

		*os << *RowIterator << ", ";

	}
	return out;
}
