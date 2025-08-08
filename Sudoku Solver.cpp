#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> board(9, vector<int>(9));
vector<vector<set<int>>> candidates(9, vector<set<int>>(9));
set<int> all_numbers = {1,2,3,4,5,6,7,8,9};

vector<pair<int, int>> get_unfilled_cells() {
    vector<pair<int, int>> unfilled;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0)
                unfilled.emplace_back(row, col);
        }
    }
    return unfilled;
}

set<int> get_row(int row) {
    set<int> s;
    for (int col = 0; col < 9; ++col)
        if (board[row][col]) s.insert(board[row][col]);
    return s;
}

set<int> get_col(int col) {
    set<int> s;
    for (int row = 0; row < 9; ++row)
        if (board[row][col]) s.insert(board[row][col]);
    return s;
}

set<int> get_square(int row, int col) {
    set<int> s;
    int sr = (row / 3) * 3, sc = (col / 3) * 3;
    for (int r = sr; r < sr + 3; ++r)
        for (int c = sc; c < sc + 3; ++c)
            if (board[r][c]) s.insert(board[r][c]);
    return s;
}

void initialize_candidates() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                set<int> row_vals = get_row(row);
                set<int> col_vals = get_col(col);
                set<int> square_vals = get_square(row, col);
                candidates[row][col] = all_numbers;

                for (int val : row_vals) candidates[row][col].erase(val);
                for (int val : col_vals) candidates[row][col].erase(val);
                for (int val : square_vals) candidates[row][col].erase(val);
            } else {
                candidates[row][col].clear();
            }
        }
    }
}

bool solve() {
    int min_size = 10;
    int target_row = -1, target_col = -1;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                int sz = candidates[row][col].size();
                if (sz == 0) return false; 
                if (sz < min_size) {
                    min_size = sz;
                    target_row = row;
                    target_col = col;
                }
            }
        }
    }

    if (target_row == -1) return true;

    int row = target_row, col = target_col;
    set<int> backup = candidates[row][col];

    for (int val : backup) {
        board[row][col] = val;

        vector<tuple<int, int, set<int>>> modified;

        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == 0 && candidates[row][i].count(val)) {
                modified.emplace_back(row, i, candidates[row][i]);
                candidates[row][i].erase(val);
            }
            if (board[i][col] == 0 && candidates[i][col].count(val)) {
                modified.emplace_back(i, col, candidates[i][col]);
                candidates[i][col].erase(val);
            }
        }

        int sr = (row / 3) * 3, sc = (col / 3) * 3;
        for (int i = sr; i < sr + 3; ++i) {
            for (int j = sc; j < sc + 3; ++j) {
                if (board[i][j] == 0 && candidates[i][j].count(val)) {
                    modified.emplace_back(i, j, candidates[i][j]);
                    candidates[i][j].erase(val);
                }
            }
        }

        candidates[row][col].clear();

        if (solve()) return true;

        // Backtrack
        board[row][col] = 0;
        for (auto &[i, j, old_set] : modified) {
            candidates[i][j] = old_set;
        }
        candidates[row][col] = backup;
    }

    return false;
}

void print_board() {
    for (int i = 0; i < 9; ++i) {
        if (i && i % 3 == 0) cout << "------+-------+------\n";
        for (int j = 0; j < 9; ++j) {
            if (j && j % 3 == 0) cout << "| ";
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Input the board (0 = empty)
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            cin >> board[i][j];

    initialize_candidates();

    if (solve()) {
        print_board();
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
