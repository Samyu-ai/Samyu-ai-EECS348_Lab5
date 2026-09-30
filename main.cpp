/*
 * Name: Samyu Aitha
 * Lab: Lab 5: C++ Programming
 * Student ID: 3222133
 /*
 * Input: The name of the input file entered by the user.
 * Output: Results for all seven matrix operations.
 * Description: Reads the matrices and calls each function required for Lab 5.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

using Matrix = vector<vector<int>>;

// Problem 1: Read N and two N x N matrices from a file
bool readMatrices(const string& filename, Matrix& A, Matrix& B) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error: Could not open file." << endl;
        return false;
    }

    int N;
    if (!(inputFile >> N) || N <= 0) {
        cerr << "Error: Invalid matrix size." << endl;
        return false;
    }

    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(inputFile >> A[i][j])) {
                cerr << "Error: Not enough values for Matrix A." << endl;
                return false;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(inputFile >> B[i][j])) {
                cerr << "Error: Not enough values for Matrix B." << endl;
                return false;
            }
        }
    }

    return true;
}

// Helper function used by several problems
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << setw(4) << value;
        }
        cout << endl;
    }
}

// Problem 2: Add two matrices
Matrix addMatrices(const Matrix& A, const Matrix& B) {
    int N = static_cast<int>(A.size());
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

// Problem 3: Multiply two matrices
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int N = static_cast<int>(A.size());
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

// Problem 4: Calculate main and secondary diagonal sums
void diagonalSums(const Matrix& matrix) {
    int N = static_cast<int>(matrix.size());
    int mainSum = 0;
    int secondarySum = 0;

    for (int i = 0; i < N; i++) {
        mainSum += matrix[i][i];
        secondarySum += matrix[i][N - 1 - i];
    }

    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
}

// Problem 5: Swap two rows
bool swapRows(Matrix& matrix, int row1, int row2) {
    int N = static_cast<int>(matrix.size());

    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) {
        cout << "Invalid row index." << endl;
        return false;
    }

    swap(matrix[row1], matrix[row2]);
    return true;
}

// Problem 6: Swap two columns
bool swapColumns(Matrix& matrix, int col1, int col2) {
    int N = static_cast<int>(matrix.size());

    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) {
        cout << "Invalid column index." << endl;
        return false;
    }

    for (int i = 0; i < N; i++) {
        swap(matrix[i][col1], matrix[i][col2]);
    }

    return true;
}

// Problem 7: Update one matrix element
bool updateElement(Matrix& matrix, int row, int col, int newValue) {
    int N = static_cast<int>(matrix.size());

    if (row < 0 || row >= N || col < 0 || col >= N) {
        cout << "Invalid matrix index." << endl;
        return false;
    }

    matrix[row][col] = newValue;
    return true;
}

int main() {
    string filename;
    Matrix A, B;

    cout << "Enter input filename: ";
    cin >> filename;

    if (!readMatrices(filename, A, B)) {
        return 1;
    }

    // Problem 1
    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(B);
    cout << endl;

    // Problem 2
    Matrix sum = addMatrices(A, B);
    cout << "A + B:" << endl;
    printMatrix(sum);
    cout << endl;

    // Problem 3
    Matrix product = multiplyMatrices(A, B);
    cout << "A * B:" << endl;
    printMatrix(product);
    cout << endl;

    // Problem 4
    cout << "Diagonal sums for Matrix A:" << endl;
    diagonalSums(A);
    cout << endl;

    // Problem 5
    Matrix rowSwapped = A;
    if (swapRows(rowSwapped, 0, 2)) {
        cout << "Problem 5 - Rows 0 and 2 swapped:" << endl;
        printMatrix(rowSwapped);
        cout << endl;
    }

    // Problem 6
    Matrix columnSwapped = A;
    if (swapColumns(columnSwapped, 0, 2)) {
        cout << "Problem 6 - Columns 0 and 2 swapped:" << endl;
        printMatrix(columnSwapped);
        cout << endl;
    }

    // Problem 7
    Matrix updated = A;
    if (updateElement(updated, 1, 2, 99)) {
        cout << "Problem 7 - Updated matrix:" << endl;
        printMatrix(updated);
    }

    return 0;
}
