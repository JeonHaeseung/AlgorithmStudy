/*
문제 링크: https://www.acmicpc.net/problem/2406
문제 이름: [2406번] 안정적인 네트워크
카테고리: BEAKJOON
최종 업로드 날짜: 2024.04.19
버전: v1
*/
/* 문제 풀이: 1번 컴퓨터만 제외하면 MST 문제이다. 이때, 이미 연결되어 있는 쌍은 가중치가 0이라고 보면 된다.
즉, 반드시 크루스칼로만 풀어야 하는 문제는 아니고, 프림으로도 풀 수 있다.
1번 컴퓨터의 존재 때문에 코너 케이스를 잘 고려해야 한다.
 */

#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef pair<int, int> ci;       // <w, y>
typedef tuple<int, int, int> tp; //<w, x, y>

void solution(int n, int start, vector<vector<ci>> &graph) {

    // 코너 케이스-노드가 하나밖에 없다면 여기서 리턴
    if (n == 1) {
        cout << 0 << " " << 0 << '\n';
        return;
    }

    vector<bool> visited(n + 1, false);
    vector<int> distance(n + 1, INT_MAX);
    vector<ci> edge(0); // 연결해야 하는 쌍
    priority_queue<tp, vector<tp>, greater<>> pq;

    int x = 0;
    int k = 0;

    distance[start] = 0;
    pq.push(make_tuple(0, start, start));

    while (!pq.empty()) {
        auto [curr_w, curr_x, curr_y] = pq.top();
        pq.pop();

        if (visited[curr_y]) {
            continue;
        }

        visited[curr_y] = true;
        x += curr_w;

        // 원래 추가되어 있던 쌍이라면 count하지 않음
        if (curr_w != 0) {
            k++;
            edge.push_back(make_pair(curr_x, curr_y));
        }

        for (auto [linked_w, linked_n] : graph[curr_y]) {
            if (!visited[linked_n] && linked_w < distance[linked_n]) {
                pq.push(make_tuple(linked_w, curr_y, linked_n));
                distance[linked_n] = linked_w;
            }
        }
    }

    // 코너 케이스-이미 안정적인 네트워크라면
    if (x == 0) {
        cout << 0 << " " << 0 << '\n';
        return;
    }

    // 출력
    cout << x << " " << k << '\n';
    for (int i = 0; i < edge.size(); i++) {
        cout << edge[i].first << " " << edge[i].second << '\n';
    }

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m; // 컴퓨터 개수 n(1 ≤ n ≤ 1,000), 컴퓨터 쌍의 개수 m(0 ≤ m ≤ 10,000)
    cin >> n >> m;

    // vector<vector<ci>> graph(n + 1, vector<ci>(n + 1, {-1, 0}));
    vector<vector<ci>> graph(n + 1, vector<ci>(0));

    vector<ci> temp(0);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        temp.push_back(make_pair(x, y));
    }

    // 가중치 모두 저장
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            int w;
            cin >> w;
            if (i <= 1 || j <= 1) {
                continue;
            }
            graph[i].push_back(make_pair(w, j));
            graph[j].push_back(make_pair(w, i));
        }
    }

    for (int i = 0; i < temp.size(); i++) {
        // 가중치 0으로 만들어주기
        graph[temp[i].first][temp[i].second - 2] = make_pair(0, temp[i].second);
        graph[temp[i].second][temp[i].first - 2] = make_pair(0, temp[i].first);
    }

    // 어디서 시작해도 되므로, node 2에서 시작한다고 하기
    solution(n, 2, graph);
}