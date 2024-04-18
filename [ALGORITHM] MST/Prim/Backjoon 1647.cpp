/*
문제 링크: https://www.acmicpc.net/problem/1647
문제 이름: [1647번] 도시 분할 계획
카테고리: BEAKJOON
최종 업로드 날짜: 2023.04.18
버전: v1
*/
/* 문제 풀이: 문제 설명에서 "어느 방향으로든지 다닐 수 있는 편리한 길", "두 집 사이에 경로가 항상 존재",
"임의의 두 집 사이에 경로가 항상 존재", "길의 유지비의 합을 최소로"라고 했으므로, 무방향 가중치 그래프에서 모든 노드를 한번씩 방문하는 최소 신장 트리(MST) 문제.
이때 "길이 너무 많다", 즉 간선이 많다고 했으므로, 간선의 개수가 많은 밀집 그래프(Dense Graph)에서 효율적인 프림 알고리즘 사용하기
*/

#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> ci;

int solution(int n, int start, vector<vector<ci>> &graph) {
    int answer = 0;
    int max = -1;
    vector<bool> visited(n + 1, false); // 정점 방문 여부
    vector<int> distance(n + 1, INT_MAX);
    // 큐에 저장되는 요소(ci), 내부 구현에 쓰는 컨테이너(vector), 정렬(오름차순)
    priority_queue<ci, vector<ci>, greater<>> pq;

    // 초기화
    pq.push(make_pair(0, start));
    distance[start] = 0;

    // 큐가 비어있지 않으면 실행
    while (!pq.empty()) {
        auto [curr_w, curr] = pq.top();
        pq.pop();

        // 이미 방문했었다면 continue
        if (visited[curr]) {
            continue;
        }

        // 처음 방문이라면 방문 처리 및 가중치 더하기
        visited[curr] = true;
        answer += curr_w;

        // 마을을 두 개로 나누어 줄 때 제거할 가장 큰 길(가중치)
        if (max < curr_w) {
            max = curr_w;
        }

        for (auto [next_w, next] : graph[curr]) {
            if (!visited[next] && next_w < distance[next]) {
                // 미방문 정점이면서 & 현재 기록된 간선보다 작은 가중치가 나왔을 경우
                pq.push(make_pair(next_w, next));
                distance[next] = next_w;
            }
        }
    }
    return answer - max;
}

// 시간 복잡도: 프림의 경우 우선순위 큐 구현 시 O(ElogV)이므로, worst case에서 1,000,000*log2(100,000) = 5,000,000
// 크루스칼의 경우 O(ElogE)이므로, 1,000,000*log2(1,000,000) = 6,000,000
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m; // 집의 개수 N(2 ≤ N ≤ 100,000), 길의 개수 M(1 ≤ M ≤ 1,000,000)
    cin >> n >> m;
    vector<vector<ci>> graph(n + 1, vector<ci>(0)); // 각 노드의 연결 된 노드 linked list

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back(make_pair(w, b));
        graph[b].push_back(make_pair(w, a));
    }

    cout << solution(n, 1, graph); // 무방향이므로 아무 노드에서나 시작해도 됨
}