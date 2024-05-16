/*
문제 링크: https://www.acmicpc.net/problem/17071
문제 이름: [17071번] 숨바꼭질 5
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.16
버전: v1
*/

/*접근 방식:
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 500000;

bool checkRange(int n) {
    if (n >= 0 && n <= MAX)
        return true;
    return false;
}

int solution(int n, int k) {
    // 코너케이스: 둘이 서로 같은 위치라면 바로 리턴
    if (n == k) {
        return 0;
    }

    vector<int> time(MAX + 1, -1);
    queue<int> q;
    int young = k; // 동생의 처음 위치
    int accel = 1; // 동생의 가속도
    time[n] = 0;
    q.push(n);

    while (!q.empty()) {
        // 동생이 먼저 움직임
        young += accel;
        accel++;

        // 동생이 움직인 결과가 범위 바깥이라면 종료
        if (!checkRange(young))
            return -1;

        int curr = q.front();
        q.pop();

        for (int nx : {curr + 1, curr - 1, curr * 2}) {
            // 이미 방문했거나 범위 바깥이라면 계산하지 않음
            if (time[nx] != -1 || !checkRange(nx)) {
                continue;
            } else {
                time[nx] = time[curr] + 1;
                q.push(nx);

                cout << "수빈이: " << nx << " 동생: " << young << "\n";

                // 수빈이와 동생이 움직인 결과의 위치가 같다면 종료
                if (young == nx) {
                    return time[nx];
                }
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;

    cin >> n >> k;

    cout << solution(n, k);
}