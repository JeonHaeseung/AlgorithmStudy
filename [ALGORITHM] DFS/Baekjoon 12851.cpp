/*
문제 링크: https://www.acmicpc.net/problem/12851
문제 이름: [12851번] 숨바꼭질 2
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.06
버전: v1
*/

/*접근 방식: 1 14 -> (1, 2, 3, 6, 7, 14),  (1, 2, 4, 8, 7, 14) 이런 경우처럼 같은 time에 같은 장소를 방문하는 경우도
정답에 포함되는데, 일반적인 bfs는 한번 방문한 정점을 다시 방문하지 않으므로 이 경우를 고려하지 않는다.
이 경우를 고려하도록 만들어줘야 정답이다.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int MAX = 100000;

bool checkRange(int n) {
    if (n < 0 || n > MAX) {
        return false;
    }
    return true;
}

pair<int, int> solution(int n, int k) {
    // 코너 케이스(n >= k)
    if (n >= k) {
        return make_pair(n - k, 1);
    }

    // 초기화
    vector<int> time(MAX + 1, -1); // 최단 시간
    vector<int> cnt(MAX + 1, -1);  // 출발 장소에서 도달 가능한 방법 수
    time[n] = 0;
    cnt[n] = 1;
    queue<int> q;
    q.push(n);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int nx : {curr - 1, curr + 1, curr * 2}) {
            // 범위 벗어났다면 continue
            if (!checkRange(nx))
                continue;

            // 방문했던 곳이면
            if (time[nx] != -1) {
                if (time[curr] + 1 == time[nx]) // 최단 시간이 같은 경우(즉, 동시에 같은 지점 방문)
                    cnt[nx] += cnt[curr];
            }
            // 첫 방문이라면
            else {
                time[nx] = time[curr] + 1; // 최단 거리 갱신
                cnt[nx] = cnt[curr];       // 처음 간 경우
                q.push(nx);
            }
        }
    }

    return make_pair(time[k], cnt[k]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;

    cin >> n >> k;

    pair<int, int> answer = solution(n, k);
    cout << answer.first << "\n"
         << answer.second;
}