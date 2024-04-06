/*
문제 링크: https://www.acmicpc.net/problem/1414
문제 이름: [1414번] 불우이웃돕기
카테고리: BEAKJOON
최종 업로드 날짜: 2023.04.05
버전: v1
*/

/*문제 풀이: 가중치가 있다는 것을 완전히 무시하고(...) BFS로 풀어도 된다고 생각했다.
 */

#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int char_to_num(char a) {
    if (a >= 'a' && a <= 'z') {
        return a - 96;
    } else if (a >= 'A' && a <= 'Z') {
        return a - 38;
    } else {
        return 0;
    }
}

int bfs(int n, int start, vector<vector<int>> &computers) {
    vector<bool> visited(n, false); // 방문 체크
    queue<int> que;
    int result = 0;

    // 시작점 넣어주기
    que.push(start);
    visited[start] = true;

    while (!que.empty()) {
        int curr = que.front();
        que.pop();

        for (int next = 0; next < n; next++) {
            // 간선이 존재하고, 아직 방문하지 않은 컴퓨터라면
            if (computers[curr][next] || visited[next]) {
                continue;
            }
            visited[next] = true;
            que.push(next); // 큐에 삽입
            result += computers[curr][next];
        }
    }

    return result;
}

int solution(int n, int total_lenght, vector<vector<int>> &computers) {
    int min_answer = INT_MAX;

    // 모든 시작 정점에 대해서 bds 테스트하기
    for (int i = 0; i < n; i++) {
        int bfs_result = total_lenght - bfs(n, i, computers); // 남는 간선이 필요하다.
        if (min_answer > bfs_result) {
            min_answer = bfs_result;
        }
    }
    return min_answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    int total_length = 0;
    cin >> n;
    vector<vector<int>> computers(n, vector(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char temp;
            cin >> temp;
            computers[i][j] = char_to_num(temp);
            total_length += computers[i][j];
        }
    }

    cout << solution(n, total_length, computers);
}