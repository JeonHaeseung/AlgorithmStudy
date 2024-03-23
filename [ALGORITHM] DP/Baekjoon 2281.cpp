#include <iostream>
#include <vector>

using namespace std;

int find_answer(int idx, int n, int m, vector<int> &names, vector<int> &dp) {
    // 이미 계산한 DP라면 pass
    if (dp[idx] != -1) {
        return dp[idx];
    }

    // 새로운 줄에 쓴다고 가정한 값
    int left = m - names[idx];

    for (int i = idx + 1; i <= n && left >= 0; i++) {
        if (i == n) {
            dp[idx] = 0;
            break;
        }
        dp[idx] = min(dp[idx], left * left + find_answer(i, n, m, names, dp));
        left -= names[i] + 1;
    }

    return dp[idx];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> names(n);

    // n번째 이름까지 계산한 결과를 저장하는 배열 dp
    vector<int> dp(n, -1);
    // 마지막 줄은 계산하지 않음
    dp[n - 1] = 0;

    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    cout << find_answer(0, n, m, names, dp);
}