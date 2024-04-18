/*
문제 링크: https://www.acmicpc.net/problem/2281
문제 이름: [2281번] 데스노트
카테고리: BEAKJOON
최종 업로드 날짜: 2024.03.23
버전: v1
*/

#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int final_answer(int n, int m, vector<int> &name, vector<vector<int>> &dp) {
    int answer = 0;
    vector<int> visited(n, 0);
    vector<int> space(m, m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 추가할 수 있는 가능성이 있음
            if (!visited[j] && space[i] - name[j] >= 0) {

                visited[j] = 1;
                if (space[i] - name[j] > 0) {
                    space[i] -= (name[j] + 1);
                } else {
                    space[i] -= name[j];
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 추가할 수 있는 가능성이 있음
            if (!visited[j] && space[i] - name[j] >= 0) {

                visited[j] = 1;
                if (space[i] - name[j] > 0) {
                    space[i] -= (name[j] + 1);
                } else {
                    space[i] -= name[j];
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (space[i] == 0) {
            answer += 0;
        }
        if (space[i] > 0) {
            answer += pow((space[i] + 1), 2);
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;

    cin >> n >> m;

    int row = m;
    int col = m;

    vector<int> name(n);
    vector<vector<int>> dp(row, vector<int>(col, 0));

    for (int i = 0; i < n; i++) {
        cin >> name[i];
    }

    // O(nlogn) 시간 복잡도
    sort(name.begin(), name.end(), greater<>()); // 내림차순

    cout << final_answer(n, m, name, dp);
}