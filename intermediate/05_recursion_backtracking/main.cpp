#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// ---------- N-Queens ----------

int solutionCount = 0;
vector<int> firstSolution;

bool isSafe(vector<int>& cols, int row, int col) {
    for (int r = 0; r < row; r++) {
        int c = cols[r];
        if (c == col) return false;
        if (abs(c - col) == abs(r - row)) return false;
    }
    return true;
}

void solveQueens(vector<int>& cols, int row, int n, bool printSolutions) {
    if (row == n) {
        solutionCount++;
        if (firstSolution.empty()) firstSolution = cols;
        if (printSolutions) {
            cout << "Solution " << solutionCount << ": [";
            for (int i = 0; i < n; i++) cout << cols[i] << (i + 1 < n ? ", " : "");
            cout << "]" << endl;
        }
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(cols, row, col)) {
            cols[row] = col;
            solveQueens(cols, row + 1, n, printSolutions);
        }
    }
}

void printQueensBoard(const vector<int>& cols) {
    int n = cols.size();
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cout << (cols[row] == col ? "Q " : ". ");
        }
        cout << endl;
    }
}

// ---------- Sudoku ----------

const int SIZE = 9;

bool isValidPlacement(vector<vector<int>>& board, int row, int col, int val) {
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == val) return false;
        if (board[i][col] == val) return false;
    }
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int r = boxRow; r < boxRow + 3; r++) {
        for (int c = boxCol; c < boxCol + 3; c++) {
            if (board[r][c] == val) return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] != 0) continue;
            for (int val = 1; val <= 9; val++) {
                if (isValidPlacement(board, row, col, val)) {
                    board[row][col] = val;
                    if (solveSudoku(board)) return true;
                    board[row][col] = 0;
                }
            }
            return false; // no valid digit here, backtrack
        }
    }
    return true; // no empty cells left
}

void printBoard(vector<vector<int>>& board) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            cout << board[r][c] << " ";
            if (c == 2 || c == 5) cout << "| ";
        }
        cout << endl;
        if (r == 2 || r == 5) cout << "------+-------+------" << endl;
    }
}

int main() {
    cout << "N-Queens for N=8 (each line is one solution as column indices per row):" << endl;
    int n = 8;
    vector<int> cols(n, -1);
    solveQueens(cols, 0, n, true);
    cout << "\nTotal solutions found: " << solutionCount << endl;
    assert(solutionCount == 92);

    cout << "\nBoard for the first solution:" << endl;
    printQueensBoard(firstSolution);

    cout << "\n----------------------------------------\n" << endl;

    cout << "Sudoku solver on a hardcoded puzzle:" << endl;
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "\nPuzzle:" << endl;
    printBoard(board);

    bool solved = solveSudoku(board);
    cout << "\nSolved: " << (solved ? "yes" : "no") << endl;
    if (solved) {
        cout << "\nSolution:" << endl;
        printBoard(board);
    }
    assert(solved);

    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            assert(board[r][c] != 0);

    cout << "\nAll checks passed." << endl;
    return 0;
}
