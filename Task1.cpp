#include <iostream>
using namespace std;

int arr[100][100];
int rows, cols;

// returns the row number of the biggest element in column c
int biggestInColumn(int c) {
    int best = 0;
    for (int i = 1; i < rows; i++) {
        if (arr[i][c] > arr[best][c]) {
            best = i;
        }
    }
    return best;
}

int main() {
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    if (rows <= 0 || cols <= 0 || rows > 100 || cols > 100) {
        cout << "Invalid size (max 100 x 100)" << endl;
        return 0;
    }

    cout << "Enter the elements row by row:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }

    int low = 0, high = cols - 1;
    bool found = false;

    while (low <= high && !found) {
        int mid = (low + high) / 2;
        int r = biggestInColumn(mid);
        int val = arr[r][mid];

        bool leftIsBigger = false;
        bool rightIsBigger = false;
        if (mid > 0 && arr[r][mid - 1] > val) leftIsBigger = true;
        if (mid < cols - 1 && arr[r][mid + 1] > val) rightIsBigger = true;

        if (!leftIsBigger && !rightIsBigger) {
            cout << "Peak element is " << val << " at row " << r + 1 << ", column " << mid + 1 << endl;
            found = true;
        }
        else if (leftIsBigger) {
            high = mid - 1;   // go to the left half
        }
        else {
            low = mid + 1;    // go to the right half
        }
    }

    if (!found) {
        cout << "No peak found (this should never happen)" << endl;
    }
    return 0;
}