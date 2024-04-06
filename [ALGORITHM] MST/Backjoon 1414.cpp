/*
문제 링크: https://www.acmicpc.net/problem/1414
문제 이름: [1414번] 불우이웃돕기
카테고리: BEAKJOON
최종 업로드 날짜: 2023.04.06
버전: v2
*/

/*문제 풀이: 가중치가 있는 그래프에서 MST를 구해야 하므로 프림 또는 크루스칼로 구해야 한다.
나는 크루스칼로 풀었다. 다만 크루스칼은 무방향 그래프에서만 사용 가능하다고 들었는데 어째서 이 경우에도 가능한 건지는...모르겠다...
 */

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int, int> tp; // 가중치, 시작 노드, 끝 노드
vector<int> parent;

int char_to_num(char a) {
    if (a >= 'a' && a <= 'z') {
        return a - 96;
    } else if (a >= 'A' && a <= 'Z') {
        return a - 38;
    } else {
        return 0;
    }
}

int find_parent(int x) {
    if (parent[x] < 0) {
        return x;
    }
    return parent[x] = find_parent(parent[x]);
}

// 사이클이 아닌지 판단한다.
bool union_nodes(int x, int y) {
    int px = find_parent(x);
    int py = find_parent(y);

    if (px == py) {
        return false;
    }

    if (parent[px] < parent[py]) { // 새로운 루트 px
        parent[px] += parent[py];
        parent[py] = px;
    } else { // 새로운 루트 py
        parent[py] += parent[px];
        parent[px] = py;
    }
    return true;
}

int kruskal(int n, vector<tp> &edge) {
    int sum = 0, cnt = 0;

    for (auto [w, n1, n2] : edge) {
        if (!union_nodes(n1, n2)) { // 사이클이 생기는 경우 패스
            continue;
        }
        sum += w; // 사이클이 안 생긴다면
        cnt++;

        if (cnt == n - 1) { // 필요한 간선을 모두 찾은 경우
            return sum;
        }
    }

    // MST 못 만든 경우
    return 0;
}

int solution(int n, int total_lenght, vector<tp> &edge) {
    // 노드가 하나만 있을 경우에 -1이 아니라 그 노드 하나의 가중치가 반환되어야 함
    // 이 코너케이스를 빼먹으면 97%에서 틀림
    if (n == 1) {
        if (edge.size() == 1) {
            auto [w, n1, n2] = edge[0];
            return w;
        }
        if (edge.size() == 0) {
            return 0;
        }
    }

    int mst = kruskal(n, edge);
    if (mst) {                     // MST가 만들어졌다면
        return total_lenght - mst; // 남는 간선을 계산하기
    } else {
        return -1; // MST 못 만든 경우
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    int total_length = 0;
    cin >> n;
    vector<tp> edge;
    parent.assign(n + 1, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char temp;
            cin >> temp;
            int lenght = char_to_num(temp);
            if (lenght) { // 연결되어 있다면
                edge.push_back({lenght, i, j});
                total_length += lenght;
            }
        }
    }

    sort(edge.begin(), edge.end()); // 꼭 정렬 필요

    cout << solution(n, total_length, edge);
}