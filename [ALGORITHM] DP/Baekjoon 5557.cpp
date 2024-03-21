/*
문제 링크: https://www.acmicpc.net/problem/5557
문제 이름: [5557번] 1학년
카테고리: BEAKJOON
최종 업로드 날짜: 2023.03.21
버전: v1
*/

#include <iostream>
#include <vector>

using namespace std;

long long find_answer(int n, vector<vector<long long>> &dp, vector<int> &numbers) {
    // 맨 첫 줄 저장
    if (numbers[0] >= 0 && numbers[0] <= 20) dp[0][numbers[0]]++;

    // 답이 되어야 하는 맨 마지막
    int answer = numbers[n - 1];

    //
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= 20; j++) {
            // 앞서서 계산한 결과가 있다면
            if (dp[i][j] != 0) {
                // 0 이상 20이하 연산이 되는지 부분적으로 체크
                if (j + numbers[i + 1] >= 0 && j + numbers[i + 1] <= 20) dp[i + 1][j + numbers[i + 1]] += dp[i][j];
                if (j - numbers[i + 1] >= 0 && j - numbers[i + 1] <= 20) dp[i + 1][j - numbers[i + 1]] += dp[i][j];
            }
        }
    }

    return dp[n - 2][answer];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    // 행렬의 크기
    int rows = n;
    int cols = 20 + 1;

    // 행렬 선언 및 크기 지정, 0으로 초기화
    vector<vector<long long>> dp(rows, vector<long long>(cols, 0));
    vector<int> numbers(rows);

    // 연산해야 할 숫자 배열들 저장하기
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    cout << find_answer(n, dp, numbers);
}