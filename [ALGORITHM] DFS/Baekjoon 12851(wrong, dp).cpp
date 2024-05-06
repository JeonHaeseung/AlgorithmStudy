/*
문제 링크: https://www.acmicpc.net/problem/12851
문제 이름: [12851번] 숨바꼭질 2
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.06
버전: v1
*/

/*접근 방식:
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool checkRange(int n) {
    if (n >= 0 && n <= 100000) {
        return true;
    } else {
        return false;
    }
}

void setState(int n, vector<int> &current_dp, vector<int> &current_state, vector<int> &visited) {
    if (checkRange(n)) {
        current_dp[n] += 1;
        if (!visited[n]) {
            current_state.push_back(n);
            visited[n] = 1;
        }
    }
}

pair<int, int> solution(int n, int k) {
    // 코너 케이스(n>k)
    if (n >= k) {
        return make_pair(n - k, 1);
    }

    // 초기화
    int col = 100001;
    vector<int> dp(col, 0); // 0으로 초기화 1행*100001열 만들기
    int time = 0;
    int count = dp[k];

    // 다음 state를 구하기 위해 사용(10만 개 열 모두 for 문 도는 것을 방지)
    vector<int> last_state;
    last_state.push_back(n);
    vector<int> visited(col, 0);

    // 답이 구해질 때까지 계속하기
    while (count == 0) {
        // 다음 시간대에 한 행 추가
        time += 1;
        vector<int> current_dp(col, 0);
        vector<int> current_state;

        // 기존 state에서 +1, -1, x2하기
        for (int i = 0; i < last_state.size(); i++) {
            setState(last_state[i] + 1, current_dp, current_state, visited);
            setState(last_state[i] - 1, current_dp, current_state, visited);
            setState(last_state[i] * 2, current_dp, current_state, visited);
        }

        // 기존 행 삭제하기
        dp = current_dp;
        last_state = current_state;

        // 답변에 도달했는지 확인하기
        count = dp[k];
    }

    if (n == 1) {
        return make_pair(time, count * 2);
    }

    return make_pair(time, count);
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