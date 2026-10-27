#include <iostream>
#include <stack>
using namespace std;

stack<int> peg[3];   // peg 0 = A, 1 = B, 2 = C

// makes the only legal move between two pegs (in either direction)
void makeMove(int p, int q) {
    int disk;
    if (peg[p].empty()) {
        disk = peg[q].top();
        peg[q].pop();
        peg[p].push(disk);
        cout << "Move disk " << disk << " from " << char('A' + q) << " to " << char('A' + p) << endl;
    }
    else if (peg[q].empty()) {
        disk = peg[p].top();
        peg[p].pop();
        peg[q].push(disk);
        cout << "Move disk " << disk << " from " << char('A' + p) << " to " << char('A' + q) << endl;
    }
    else if (peg[p].top() > peg[q].top()) {
        disk = peg[q].top();
        peg[q].pop();
        peg[p].push(disk);
        cout << "Move disk " << disk << " from " << char('A' + q) << " to " << char('A' + p) << endl;
    }
    else {
        disk = peg[p].top();
        peg[p].pop();
        peg[q].push(disk);
        cout << "Move disk " << disk << " from " << char('A' + p) << " to " << char('A' + q) << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
    if (n < 1 || n > 20) {
        cout << "Please enter between 1 and 20 disks" << endl;
        return 0;
    }

    // put all disks on peg A, biggest at the bottom
    for (int d = n; d >= 1; d--) {
        peg[0].push(d);
    }

    int source = 0, aux = 1, dest = 2;
    if (n % 2 == 0) {
        // for even number of disks swap dest and aux
        int temp = dest;
        dest = aux;
        aux = temp;
    }

    // total moves = 2^n - 1
    long long totalMoves = 1;
    for (int i = 0; i < n; i++) totalMoves = totalMoves * 2;
    totalMoves = totalMoves - 1;

    for (long long i = 1; i <= totalMoves; i++) {
        if (i % 3 == 1) makeMove(source, dest);
        else if (i % 3 == 2) makeMove(source, aux);
        else makeMove(aux, dest);
    }

    cout << "Total moves: " << totalMoves << endl;
    return 0;
}