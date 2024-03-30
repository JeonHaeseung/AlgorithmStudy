/*
문제 링크: https://www.acmicpc.net/problem/13904
문제 이름: [13904번] 과제
카테고리: BEAKJOON
최종 업로드 날짜: 2023.03.30
버전: v1
*/

/*접근 방식: knapsack 문제에서 배낭의 물품이 과제로 변경되었음
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> hw; // pair는 미리 명시해두기

bool compair(const hw &a, const hw &b) {
    if (a.first == b.first) {
        a.second > b.second; // 두 번째 기준 감소하는 순서
    }

    return a.first < b.first; // 첫 번째 기준 증가하는 순서
}

int find_answer(int d, int w, vector<hw> &hw_list, vector<vector<int>> &dp) {
    for (int i = 1; i < d; i++) {
        for (int j = 1; j < w; j++) {

            int hwd = hw_list[i].first;
            int hww = hw_list[i].second;

            if (hwd < j) { // i번째 과제의 마감일이 지난 경우 할 수 없음( + knapsack의 (hwd > j) 조건과는 다르다)
                dp[i][j] = dp[i - 1][j];
            } else { // i번째 과제의 마감일이 지나지 않은 경우
                // i번째 과제의 점수+i번째 과제를 하기 전의 최대 점수
                // dp[i][j] = max(dp[i - 1][j], hww + dp[i - 1][j - hwd]);
                dp[i][j] = max(dp[i - 1][j], hww + dp[i - 1][j - 1]);
            }
        }

        for (int k = 1; k < d; k++) {
            for (int m = 1; m < w; m++) {
                cout << dp[k][m] << " ";
            }
            cout << "\n";
        }
    }

    return dp[d - 1][w - 1]; // 최종 값
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n; // 과제의 갯수
    vector<hw> hw_list(n);

    for (int i = 0; i < n; i++) {
        cin >> hw_list[i].first >> hw_list[i].second;
    }

    sort(hw_list.begin(), hw_list.end(), compair); // 과제 일수 기준 오름차순, 과제 점수 기준 내림차순 정렬
    int max = hw_list[n - 1].first;                // 가장 늦은 마감일

    int row = n;                                              // dp의 행은 과제 수
    int col = max;                                            // dp의 열은 마감일
    vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0)); // 0으로 초기화

    cout << find_answer(row, col, hw_list, dp);
}