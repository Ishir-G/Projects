#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

vector<vector<int>> board(9, vector<int>(9, 0));
vector<vector<set<int>>> candidates(9, vector<set<int>>(9));
set<int> all_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

set<int> get_row(int row) {
    set<int> row_set;
    for (int col = 0; col < 9; ++col) {
        if (board[row][col] != 0) {
            row_set.insert(board[row][col]);
        }
    }
    return row_set;
}

set<int> get_col(int col) {
    set<int> col_set;
    for (int row = 0; row < 9; ++row) {
        if (board[row][col] != 0) {
            col_set.insert(board[row][col]);
        }
    }
    return col_set;
}

set<int> get_square(int row, int col) {
    set<int> square_set;
    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int r = start_row; r < start_row + 3; ++r) {
        for (int c = start_col; c < start_col + 3; ++c) {
            if (board[r][c] != 0) {
                square_set.insert(board[r][c]);
            }
        }
    }
    return square_set;
}

void get_candidates() {
    for (int row = 0; row < 9; row ++) {
        for (int col = 0; col < 9; col ++) {
            if (board[row][col] != 0) continue;

            set<int> row_set = get_row(row);
            set<int> col_set = get_col(col);
            set<int> square_set = get_square(row, col);
            candidates[row][col] = all_numbers;
            
            for (int num : row_set) candidates[row][col].erase(num);
            for (int num : col_set) candidates[row][col].erase(num);
            for (int num : square_set) candidates[row][col].erase(num);

            if (candidates[row][col].size() == 1) {
                board[row][col] = *candidates[row][col].begin();
                candidates[row][col].clear();
            }
        }
    }
}

void backtrack(int row, int col) {
    if (row == 9) return;
    if (col == 9) return backtrack(row + 1, 0);

    if (board[row][col] != 0) return backtrack(row, col + 1);

    for (int num : candidates[row][col]) {
        board[row][col] = num;

        backtrack(row, col + 1);
        if (board[8][8] != 0) return;
    }

    board[row][col] = 0;
    return;
}

int main() {
    // Input the Sudoku board
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cin >> board[i][j];
        }
    }

    get_candidates();
    backtrack(0, 0);

    for (int i = 0; i < 9; ++i) {
        if (i > 0 && i % 3 == 0) {
            cout << "------+-------+------" << endl;
        }
        for (int j = 0; j < 9; ++j) {
            if (j > 0 && j % 3 == 0) cout << "| ";
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}