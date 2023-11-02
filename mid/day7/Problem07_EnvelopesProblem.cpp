/*
最长递增子序列问题
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Envelope {
    int l;
    int h;

    Envelope(int weight, int height) : l(weight), h(height) {}
};

struct EnvelopeComparator {
    bool operator()(const Envelope& e1, const Envelope& e2) {
        return (e1.l != e2.l) ? (e1.l < e2.l) : (e1.h > e2.h);
    }
};

vector<Envelope> getSortedEnvelopes(vector<vector<int>>& matrix) {
    vector<Envelope> res;
    for (const auto& envelope : matrix) {
        res.emplace_back(envelope[0], envelope[1]);
    }
    sort(res.begin(), res.end(), EnvelopeComparator());
    return res;
}

int maxEnvelopes(vector<vector<int>>& matrix) {
    vector<Envelope> envelopes = getSortedEnvelopes(matrix);
    int n = envelopes.size();
    if (n == 0) return 0;
    
    vector<int> ends(n, 0);
    ends[0] = envelopes[0].h;
    int right = 0;
    
    for (int i = 1; i < n; i++) {
        int l = 0;
        int r = right;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (envelopes[i].h > ends[m]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        right = max(right, l);
        ends[l] = envelopes[i].h;
    }
    
    return right + 1;
}

int main() {
    vector<vector<int>> matrix = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    int result = maxEnvelopes(matrix);
    cout << "Maximum Envelopes: " << result << endl;
    return 0;
}

