#include <iostream>
#include <vector>

using namespace std;

/*
3 4
5 6 7 8 1 2 3 4 9 10 11 12 2 6 10 1 5 9 3 7 11 4 8 12

5 1 9


1	2	3	4
5	6	7	8
9	10	11	12
*/


void f(int* l, int* m, int rows, int cols) {
    for (int i = 0; i < rows * cols; i += cols) {
        int j = rows * cols;
        while (j < 2 * rows * cols && l[i] != l[j]) {
            j++;
        }
        int pos = i / cols;
        if (j < 2 * rows * cols) {
            pos = (j - rows * cols) % rows;
        }
        for (int j = i; j < i + cols; j++) {
            m[pos * cols + j - i] = l[j];
        }
    }
}

int rows, cols;

int main() {
    cin >> rows >> cols;
    vector<int> l(2 * rows * cols);
    vector<int> m(rows * cols);
    for (int& i : l) cin >> i;

    f(l.data(), m.data(), rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << m[i * cols + j] << '\t';
        }
        cout << '\n';
    }
}
