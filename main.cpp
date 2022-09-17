#include "bits/stdc++.h"
using namespace std;

int n;
vector<vector<int>> board;
bool found = false;
int cnt;
int searched;

ifstream fin("sudoku.in");
ofstream fout("sudoku.out");

bool isValid() {
    for (int i = 0; i < n; i++) {

        vector<bool> foundRow(10);
        vector<bool> foundCol(10);

        for (int j = 0; j < n; j++) {

            if (board[i][j]) {
                if (foundRow[board[i][j]]) {
                    return false;
                }
                foundRow[board[i][j]] = true;
            }

            if (board[j][i]) {
                if (foundCol[board[j][i]]) {
                    return false;
                }
                foundCol[board[j][i]] = true;
            }
        }
    }


    for (int i = 0; i < n; i+=3) {
        for (int j = 0; j < n; j+=3) {
            vector<bool> foundSquare(10);

            for (int k = i; k < i+3; k++) {
                for (int l = j; l < j+3; l++) {
                    if (board[k][l]) {
                        if (foundSquare[board[k][l]]) {
                            return false;
                        }
                        foundSquare[board[k][l]] = true;
                    }
                }
            }
        }
    }

    return true;
}

pair<int,int> nextSquare(int x, int y) {
    x++;
    if (x == n) {
        x = 0;
        y++;
    }
    return {x, y};
}

void search(int x, int y) {
    searched++;

    if (y == n) {
        if (isValid()) {
            if (!found) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        fout << board[i][j] << " ";
                    }
                    fout << endl;
                }
            }

            cnt++;
            found = true;
        }
        return;
    }

    if (board[y][x]) {
        pair<int,int> nextS = nextSquare(x, y); 
        search(nextS.first, nextS.second);
        return;
    }

    for (int i = 1; i <= 9; i++) {
        board[y][x] = i;
        if (isValid()) {
            pair<int,int> nextS = nextSquare(x, y);
            search(nextS.first, nextS.second);
        }
        board[y][x] = 0;
    }
}

int main() {

    fin >> n;

    board.resize(n);

    if (n == 0 || n % 3 != 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        board[i].resize(n);
        for (int j = 0; j < n; j++) {
            char c;
            fin >> c;
            if (c == '.') {
                board[i][j] = 0;
            }
            else {
                board[i][j] = c - '0';
            }
        }
    }

    search(0, 0);
    cout << cnt << " possibilities" << endl;
    cout << searched << " boards searched" << endl;

    return 0;
}
