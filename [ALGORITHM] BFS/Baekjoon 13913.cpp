/*
문제 링크: https://www.acmicpc.net/problem/13913
문제 이름: [13913번] 숨바꼭질 3
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.16
버전: v1
*/

/*접근 방식: 이동한 경로를 찾기 위해서는 이동한 노드에 이동하기 전 위치를 기록해 준 후,
최종적으로 이동한 노드부터 경로를 다시 되집어 가면 된다.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 100000;

bool checkRange(int n) {
    if (n >= 0 && n <= MAX)
        return true;
    return false;
}

void solution(int n, int k) {
    queue<int> q;
    vector<int> time(MAX + 1, -1); // 최단 시간
    vector<int> path(MAX + 1, -1); // 방문 경로
    time[n] = 0;
    path[n] = 0;
    q.push(n);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int nx : {curr + 1, curr - 1, curr * 2}) {
            // 범위 바깥이거나 이미 방문한 곳이라면 패스
            if (!checkRange(nx) || time[nx] != -1) {
                continue;
            }
            // 첫 방문이라면 최단 시간 업데이트
            else {
                time[nx] = time[curr] + 1;
                path[nx] = curr; // 이전 방문점 업데이트
                q.push(nx);
            }
        }
    }

    cout << time[k] << "\n";
    int a = k;
    vector<int> answer;
    answer.push_back(k);

    while (a != n) {
        a = path[a];
        answer.push_back(a);
    }

    for (int i = answer.size() - 1; i >= 0; i--) {
        cout << answer[i] << " ";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;

    cin >> n >> k;

    // 코너 케이스(n >= k)
    if (n >= k) {
        cout << n - k << "\n";

        for (int i = n; i >= k; i--) {
            cout << i << " ";
        }
    } else {
        solution(n, k);
    }
}