/*
문제 링크: https://www.acmicpc.net/problem/9944
문제 이름: [9944번] NxM 보드 완주하기
카테고리: BEAKJOON
최종 업로드 날짜: 2024.04.05
버전: v2
*/

/*문제 풀이: DFS로 풀어야 하는 문제라는 건 감이 왔었는데, direction을 보존하는 방법을 몰랐다.
case를 나눠서 direction이 보존되는 경우/아닌 경우로 재귀호출을 하면 된다.
 */

#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int n; // 세로
int m; // 가로
int case_num = 1;
int empty_points_num; // 빈 공간이자 시작점이 될 수 있는 값
int final_answer = INT_MAX;

// 미로의 범위 내이고, 장애물이 아닌데 이전에 방문했던적이 없는 경우
bool check_possible(int next_x, int next_y, vector<vector<int>> &board, vector<vector<int>> &visited) {
    if (next_x < m && next_x >= 0 && next_y < n && next_y >= 0 && board[next_x][next_y] == 1 && visited[next_x][next_y] == 0) {
        return true;
    } else
        return false;
}

void direction(int x, int y, int d, int visited_point_num, int turn_count, vector<vector<int>> &board, vector<vector<int>> &visited) {
    // 모든 길을 방문했다면 return
    if (visited_point_num >= empty_points_num) {
        if (final_answer > turn_count) {
            final_answer = turn_count;
        }
        return;
    }

    // 방문하지 않았다면 다음 길을 선택하기
    int next_x = x + dx[d];
    int next_y = y + dy[d];

    // 원래 가던 direction(d) 그대로 갈 수 있다면
    if (check_possible(next_x, next_y, board, visited)) {
        visited[next_x][next_y] = 1;
        direction(next_x, next_y, d, visited_point_num + 1, turn_count, board, visited);
        visited[next_x][next_y] = 0;

    } else { // direction(d)을 바꿔야 하는 상황이라면
        for (int i = 0; i < 4; i++) {
            if (i == d)
                continue;
            int next_x = x + dx[i];
            int next_y = y + dy[i];

            if (check_possible(next_x, next_y, board, visited)) {
                visited[next_x][next_y] = 1;
                // 여기 i로 두어야 하는 걸 d로 두어서 에러 났었음, direction 바꿔야 하니 i로 두어야 함
                direction(next_x, next_y, i, visited_point_num + 1, turn_count + 1, board, visited);
                visited[next_x][next_y] = 0;
            }
        }
    }
}

void find_anwser(vector<vector<int>> &board, vector<vector<int>> &visited, vector<pair<int, int>> &empty_points) {
    // 모든 가능한 시작 지점(empty_points)에 대해서 탐색하기
    if (empty_points_num == 1) {
        final_answer = 0;
        return;
    }

    for (int i = 0; i < empty_points_num; i++) {
        int start_x = empty_points[i].first;
        int start_y = empty_points[i].second;

        for (int d = 0; d < 4; d++) {
            visited[start_x][start_y] = 1;
            direction(start_x, start_y, d, 1, 1, board, visited);
            visited[start_x][start_y] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 정해지지 않은 test case
    while (cin >> n >> m) {
        // n, m에 딱 맞추어 board 및 visited 생성하면 런타임 에러 (OutOfBounds) 발생
        vector<vector<int>> board(31, vector<int>(31, 0));
        vector<vector<int>> visited(31, vector<int>(31, 0));
        vector<pair<int, int>> empty_points;

        for (int i = 0; i < n; i++) {
            string temp;
            cin >> temp; // 한 줄 읽기
            for (int j = 0; j < m; j++) {
                if (temp[j] == '.') { // 빈 공간
                    board[i][j] = 1;
                    empty_points.push_back(make_pair(i, j)); // 시작점으로 가능한 공간
                }
                if (temp[j] == '*') { // 장애물
                    board[i][j] = 0;
                }
            }
        }

        empty_points_num = empty_points.size();

        find_anwser(board, visited, empty_points);

        // 모든 길을 방문하는 게 불가능한 경우
        if (final_answer == INT_MAX) {
            final_answer = -1;
        }

        cout << "Case " << case_num << ": " << final_answer << "\n";
        final_answer = INT_MAX; // 리셋하기

        case_num += 1; // 다음 테스트 케이스
    }

    return 0;
}