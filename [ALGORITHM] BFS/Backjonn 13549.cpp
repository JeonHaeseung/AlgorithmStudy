/*
문제 링크: https://www.acmicpc.net/problem/13549
문제 이름: [13549번] 숨바꼭질 3
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.07
버전: v1
*/

/*접근 방식:
 */
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int MAX = 100000;

bool checkRange(int n) {
    if (n >= 0 && n <= MAX) {
        return true;
    }
    return false;
}

int solution(int n, int k) {
    // 코너 케이스(n >= k)
    if (n >= k) {
        return n - k;
    }

    // 초기화
    vector<int> time(MAX + 1, -1);
    time[n] = 0;
    queue<int> q;
    q.push(n);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        int nx[3] = {curr * 2, curr - 1, curr + 1};
        for (int i = 0; i < 3; i++) {
            // 범위 벗어났거나 방문했던 곳이라면 continue
            if (!checkRange(nx[i]) || time[nx[i]] != -1) {
                continue;
            }
            // 범위 안이라면
            else {
                // 순간 이동의 경우에는 0초
                if (i == 0) {
                    time[nx[i]] = time[curr];
                }
                // 다른 경우에는 1초
                else {
                    time[nx[i]] = time[curr] + 1;
                }
                q.push(nx[i]);
            }
        }
    }

    return time[k];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;

    cin >> n >> k;

    cout << solution(n, k);
}