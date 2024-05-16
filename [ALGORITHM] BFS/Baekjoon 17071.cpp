/*
문제 링크: https://www.acmicpc.net/problem/17071
문제 이름: [17071번] 숨바꼭질 5
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.16
버전: v1
*/

/*접근 방식: 수빈이가 14초에 x라는 지점을 방문했고, 동생이 20초에 그 x지점을 방문한다면 둘은 만날 수 있다.
왜냐하면 수빈이는 x-1, x+1을 계속 반복하면서 x지점에 짝수 번째마다 머물 수 있기 때문이다.
같은 원리로 수빈이가 15초에 x라는 지점을 방문했고, 동생이 21초에 그 x지점을 방문한다면 둘은 만날 수 있다.
이때 BFS에서 깊이를 조정하기 위해서 큐의 사이즈를 사용해준다.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 500000;
bool visited[2][MAX + 1]; // 수빈이가 방문하는 위치

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

    queue<int> q;
    int young = k; // 동생의 처음 위치
    int accel = 1; // 동생의 가속도
    int time = 1;  // 동생이 움직인 횟수
    q.push(n);

    while (!q.empty()) {
        // 동생이 먼저 움직임
        young += accel;

        // 동생이 움직인 결과가 범위 바깥이라면 종료
        if (!checkRange(young))
            return -1;

        // 짝수나 홀수 시간에 이미 방문된 곳을 동생이 방문한다면 그게 정답
        if (visited[time % 2][young]) {
            return time;
        }

        // 큐에 들어있는 같은 깊이만큼의 노드를 한번에 사용하기
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int curr = q.front();
            q.pop();

            for (int nx : {curr + 1, curr - 1, curr * 2}) {
                if (nx == young) {
                    return time;
                }
                // 범위 바깥이라면 계산하지 않음
                if (!checkRange(nx)) {
                    continue;
                }
                // 짝수나 홀수 시간에 이미 방문했던 곳이라면 pass
                if (visited[time % 2][nx])
                    continue;

                visited[time % 2][nx] = true;
                q.push(nx);
            }
        }

        accel++;
        time++;
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