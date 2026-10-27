#include <iostream>
using namespace std;

int N;
int board[20][20];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(int x, int y) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == 0);
}

// plain backtracking, tries moves in fixed order (very slow for big N)
bool solvePlain(int x, int y, int step) {
    board[x][y] = step;
    if (step == N * N) return true;

    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (isSafe(nx, ny)) {
            if (solvePlain(nx, ny, step + 1)) return true;
        }
    }
    board[x][y] = 0;   // nothing worked, undo this square
    return false;
}

// how many moves are possible from (x, y)
int countMoves(int x, int y) {
    int c = 0;
    for (int k = 0; k < 8; k++) {
        if (isSafe(x + dx[k], y + dy[k])) c++;
    }
    return c;
}

// backtracking + Warnsdorff rule: go to the square with the fewest onward moves first
bool solveFast(int x, int y, int step) {
    board[x][y] = step;
    if (step == N * N) return true;

    int nextX[8], nextY[8], degree[8];
    int cnt = 0;
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (isSafe(nx, ny)) {
            nextX[cnt] = nx;
            nextY[cnt] = ny;
            degree[cnt] = countMoves(nx, ny);
            cnt++;
        }
    }

    // simple selection sort on degree
    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++) {
            if (degree[j] < degree[i]) {
                int t = degree[i]; degree[i] = degree[j]; degree[j] = t;
                t = nextX[i]; nextX[i] = nextX[j]; nextX[j] = t;
                t = nextY[i]; nextY[i] = nextY[j]; nextY[j] = t;
            }
        }
    }

    for (int i = 0; i < cnt; i++) {
        if (solveFast(nextX[i], nextY[i], step + 1)) return true;
    }
    board[x][y] = 0;
    return false;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] < 10) cout << " ";
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int x, y, choice;
    cout << "Enter board size N: ";
    cin >> N;
    if (N < 1 || N > 20) {
        cout << "N should be between 1 and 20" << endl;
        return 0;
    }
    cout << "Enter starting row (0 to " << N - 1 << "): ";
    cin >> x;
    cout << "Enter starting column (0 to " << N - 1 << "): ";
    cin >> y;
    if (x < 0 || x >= N || y < 0 || y >= N) {
        cout << "Starting position is outside the board!" << endl;
        return 0;
    }

    cout << "1) Plain backtracking (only try for N <= 6)" << endl;
    cout << "2) Optimized (Warnsdorff)" << endl;
    cout << "Your choice: ";
    cin >> choice;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    bool ok;
    if (choice == 1) ok = solvePlain(x, y, 1);
    else ok = solveFast(x, y, 1);

    if (ok) {
        cout << "Tour found:" << endl;
        printBoard();
    } else {
        cout << "No knight's tour exists from this starting square." << endl;
    }
    return 0;
}