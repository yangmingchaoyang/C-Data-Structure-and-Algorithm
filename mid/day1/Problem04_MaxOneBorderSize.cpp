/*
给定一个N*N的矩阵matrix，只有0和1两种值，返回边框全是1的最大正方形的边
长长度。
例如:
01111
01001
01001
01111
01011
其中边框全是1的最大正方形的大小为4*4，所以返回4。
*/
#include <iostream>
#include <vector>
using namespace std;

/*对于原始矩阵 m 中的每个元素为1的位置，计算从该位置出发，向右和向下所能延伸的连续1的数量。这个映射信息会被存储在矩阵 right 和 down 中。*/
void setBorderMap(vector<vector<int>>& m, vector<vector<int>>& right, vector<vector<int>>& down) {
    int r = m.size();
    int c = m[0].size();
    if (m[r - 1][c - 1] == 1) {
        right[r - 1][c - 1] = 1;
        down[r - 1][c - 1] = 1;
    }
    for (int i = r - 2; i != -1; i--) {
        if (m[i][c - 1] == 1) {
            right[i][c - 1] = 1;
            down[i][c - 1] = down[i + 1][c - 1] + 1;
        }
    }
    for (int i = c - 2; i != -1; i--) {
        if (m[r - 1][i] == 1) {
            right[r - 1][i] = right[r - 1][i + 1] + 1;
            down[r - 1][i] = 1;
        }
    }
    for (int i = r - 2; i != -1; i--) {
        for (int j = c - 2; j != -1; j--) {
            if (m[i][j] == 1) {
                right[i][j] = right[i][j + 1] + 1;
                down[i][j] = down[i + 1][j] + 1;
            }
        }
    }
}

bool hasSizeOfBorder(int size, vector<vector<int>>& right, vector<vector<int>>& down) {
    for (int i = 0; i != right.size() - size + 1; i++) {
        for (int j = 0; j != right[0].size() - size + 1; j++) {
            if (right[i][j] >= size && down[i][j] >= size
                && right[i + size - 1][j] >= size
                && down[i][j + size - 1] >= size) {
                return true;
            }
        }
    }
    return false;
}

int getMaxSize(vector<vector<int>>& m) {
    vector<vector<int>> right(m.size(), vector<int>(m[0].size()));
    vector<vector<int>> down(m.size(), vector<int>(m[0].size()));
    setBorderMap(m, right, down);
    for (int size = min(m.size(), m[0].size()); size != 0; size--) {
        if (hasSizeOfBorder(size, right, down)) {
            return size;
        }
    }
    return 0;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1}
    };

    int maxSize = getMaxSize(matrix);

    if (maxSize > 0) {
        cout << "The maximum square size with all 1s is: " << maxSize << endl;
    } else {
        cout << "No square with all 1s found." << endl;
    }

    return 0;
}

