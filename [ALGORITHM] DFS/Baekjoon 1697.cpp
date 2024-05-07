/*
문제 링크: https://www.acmicpc.net/problem/1697
문제 이름: [1697번] 숨바꼭질
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

        for (int nx : {curr - 1, curr + 1, curr * 2}) {
            // 범위 벗어났거나 방문했던 곳이라면 continue
            if (!checkRange(nx) || time[nx] != -1) {
                continue;
            }
            // 범위 내 첫 방문이라면
            else {
                time[nx] = time[curr] + 1; // 최단 시간 갱신
                q.push(nx);
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