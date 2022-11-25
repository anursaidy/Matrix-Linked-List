#include "Matrix.hpp"


template<typename T>
Matrix<T>::Matrix()
{
    headMatrix = nullptr;
}

template <typename T>
Matrix<T>::Matrix(T** arr, int r, int c)
{

    rows = r;
    cols = c;

    //if (*arr = nullptr)
    //    throw; //error;

   
    Node<T>* firstNode = new Node<T>(arr[0][0]);
    headMatrix = firstNode;
    newRow = new Node<T>*[rows];  //seperating each rows.
    //newRow[0] = firstNode;

    //Store each newRow[i] with its corresponding Rows and each of their ->nextInRow
    for (int i = 0; i < rows; i++)
    {
        if (firstNode != headMatrix) {
            firstNode = new Node<T>(arr[i][0]);//First Node of each row
        }
        newRow[i] = nullptr;
        for (int j = 0; j < cols; j++) {
            if (!newRow[i]) {
                newRow[i] = firstNode;
            }
            else {
                firstNode->nextInRow = new Node<T>(arr[i][j]);
                firstNode = firstNode->nextInRow;
            }
        }
    }

    //Assigning nextInColumn
    for (int i = 0; i < rows; i++)
    {
        Node<T>* temp = newRow[i];
        Node<T>* temp2 = newRow[i + 1];

        while (temp->nextInRow != nullptr) {
            if (i != rows - 1) { //not last row
                newRow[i]->nextInColumn = newRow[i + 1];
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

    if(headMatrix != nullptr){
        Delete();
    }
    
}


template <typename T>
Matrix<T>::Matrix(const Matrix& obj)
{
    if(obj.headMatrix != nullptr)
        Copy(obj);

}

template <typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& obj){
    
    if (this != &obj){
        
        cout << newRow[0] -> nextInRow -> value;
        
        Delete();
        
        Copy(obj);
        
        
        
      
    }
    return *this;
    
    
}

template <typename T>
void Matrix<T>::Delete(){
    
 
    if(headMatrix == nullptr){
        return ;
   }
    
    Node <T>* nodeToDelete = nullptr ,*prev = nullptr ;
    
    nodeToDelete = prev = getRow(0);
    
    int currentRow = 0;
    
    
    while(currentRow < rows){
        
      
        if((nodeToDelete -> nextInRow)== nullptr ){
           
            prev -> nextInRow = prev-> nextInColumn = nullptr;
            delete prev;
            currentRow++;
            if(currentRow< rows)
            nodeToDelete = prev = (getRow(currentRow));
            else
                break;
        }
        
        nodeToDelete = nodeToDelete-> nextInRow;
        
     
        cout << prev-> value;
        
        prev -> nextInRow = prev-> nextInColumn = nullptr;
        delete prev;
        
        prev = nodeToDelete;
        
    }
    
    
}

template <typename T>
void Matrix<T>::Copy(const Matrix<T>& obj){
    
    // ** newRow
    
    rows = obj.rows;
    cols = obj.cols;
    
    MatrixIterator<T> RowIterator(obj.getRow(0));
    newRow = new Node<T>*[obj.rows];
    
    Node<T>* current = nullptr;
    int indexOfRow = 0;
    for (int rowsCount = 0 ; rowsCount < obj.rows; RowIterator++  ){
        
        
        //end of my row
        if(indexOfRow == obj.cols){
            rowsCount++;
            indexOfRow = 0;
           
            
            if(rowsCount ==  obj.rows ){
                current = nullptr;
                break;
            }
            
            RowIterator = obj.getRow(rowsCount);
            
            
            
        }
        
        Node<T>* newNode = new Node<T>(*RowIterator);
      
      
        
        if(indexOfRow > 0){
           
            current -> nextInRow = newNode;
            current = newNode;
            indexOfRow++;
        }
        
        if(indexOfRow == 0){
         
            newRow[rowsCount]= current = newNode;
            indexOfRow++;
            
            
            
        }
        
    }
    
    headMatrix = newRow[0];
    
    
    // Connect eachrow
    
    MatrixIterator<T> iteratorRow1;
    MatrixIterator<T> iteratorRow2;
    
   
    indexOfRow =0;
    for ( int rowsCount = 0 ;( rowsCount < rows -1 && iteratorRow1!= nullptr); iteratorRow1++, iteratorRow2++ ){
        
      
       
        if( indexOfRow ==0){
           
             iteratorRow1 = newRow[rowsCount];
             iteratorRow2 = newRow[rowsCount+1];
        }
        
        if(indexOfRow == cols){
          
            indexOfRow = 0;
            rowsCount++;
            
        }else{
            
            iteratorRow1.getCurrent() -> nextInColumn = iteratorRow2.getCurrent();
            indexOfRow++;
          
            
        }
        
       
        
        
    }
    
    
    
        
}

template <typename T>
Matrix<T>& Matrix<T>::operator = ( Matrix<T>&& obj){
    
    
    if(this != &obj){
    rows = obj.rows;
    cols = obj.cols;
    
    headMatrix = obj.headMatrix;
    newRow = obj.newRow;
    
    obj.headMatrix = nullptr;
    obj.newRow = nullptr;
    //
    obj.cols = 0;
    obj.rows = 0;
        
    }
    return *this;
    
    
}

template <typename T>
Matrix<T>::Matrix(Matrix&& obj) {

    if(obj.headMatrix != nullptr){
        rows = obj.rows;
        cols = obj.cols;
        
        headMatrix = obj.headMatrix;
        newRow = obj.newRow;
        
        obj.headMatrix = nullptr;
        obj.newRow = nullptr;
        //
        obj.cols = 0;
        obj.rows = 0;
    }
    
}


template <typename T>
Node<T>* Matrix<T>::getRow(int i) const {
    return newRow[i];
}
template <typename T>
Node<T>* Matrix<T>::getColumn(int i) const{
    Node<T>* temp = newRow[0];
    int count = 0;
    while (count < i) {
        temp = temp->nextInRow;
        count++;
    }
    return temp;


}
template <typename T>
T Matrix<T>::at(int const row, int const col) {
    Node<T>* temp = newRow[row];
    int count = 0;
    while (count < col) {
        temp = temp->nextInRow;
        count++;
    }
    return temp;
}

template <typename T>
bool Matrix<T>::addNewRow(Matrix& object, Node<T>*headRow, int newRows, int i , int newCols){
    
    // i would change to a matrix itertor
    if(i == 0){
        object.newRow = new Node<T>* [newRows];
        object.headMatrix = headRow;
        object.rows = newRows;
        object.cols = newCols ;
    }
    
    object.newRow[i] = headRow;
    
    
    
    if (i!= 0){
        // i would like to use here matrix iterator
        Node<T>* prevRow, *currentRow = nullptr  ;
        prevRow = object.newRow[(i-1)];
        currentRow = object.newRow[i];
        
        for (int j = 0 ; j < object.cols ;j++){
            prevRow -> nextInColumn = currentRow;
            prevRow = prevRow -> nextInRow;
            currentRow = currentRow -> nextInRow;
            
        }
        
         currentRow = nullptr;
        
        
        
        
        return true;
        
    }else{
        
        return true;
    }
    
    
    
}

template <typename T>
Matrix<T>& Matrix<T>::transpose() {

    Matrix<T> temporalMatrix;
    MatrixIterator<T> columnIterator(getColumn(0));
    Node<T>* headRow = nullptr;
    Node<T>* current =nullptr;
    
   
    int indexOfColumn = 0;
    for (int colCounter = 0 ; colCounter < cols; columnIterator++){
        
        if(indexOfColumn == rows){
            indexOfColumn = 0;
            colCounter++;
            columnIterator = getColumn(colCounter);
         
          if(! addNewRow(temporalMatrix,headRow, cols, colCounter -1, rows))
             { throw runtime_error("Error in transaction");
                 current  = nullptr;
             }
            
            if(colCounter == cols){
                break;
            }
            
        }
        
        Node<T>* newNode = new Node<T>(*columnIterator);
        
        
        
        if(indexOfColumn == 0){
            headRow = current = newNode;
            indexOfColumn++;
           
        }
        
        if(indexOfColumn >0 ){
            current -> nextInRow = newNode;
            current = newNode;
            indexOfColumn++;
        }
        
        
        
    }
    
    
    
    
    return temporalMatrix;
    
   

}
template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix& obj) {

}
template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix& obj) {
    Node<T>* rowsMatrix;
    Node<T>* colsMatrix;
    
    int sum = 0;
    
    int j = 0;
    for (int i = 0; i < rows-1; )
    {

        if (j == obj.cols) {
             //has to remain in the same row until we iterate through all columns
            i++;
            j = 0;
        }
        rowsMatrix = getRow(i);
        colsMatrix = obj.getColumn(j);

        while (colsMatrix != nullptr) {
            sum += rowsMatrix->value * colsMatrix->value;
            rowsMatrix = rowsMatrix->nextInRow;
            colsMatrix = colsMatrix->nextInColumn;
        }

        sum = 0;
        j++;
    }
    return (*this);

}
template <typename T>
istream& operator<< (ostream& os, const Matrix<T>& matrix) {
    
      
    
    
}
