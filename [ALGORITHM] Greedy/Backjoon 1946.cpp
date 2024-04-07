/*
문제 링크: https://www.acmicpc.net/problem/1946
문제 이름: [1946번] 신입 사원
카테고리: BEAKJOON
최종 업로드 날짜: 2023.04.07
버전: v2
*/

/*문제 풀이: 어떤 A 지원자의 성적이 다른 B 지원자보다 적어도 하나는 높아야 한다.
N(1 ≤ N ≤ 100,000) 명의 지원자들을 단순하게 정말 직접 비교하는 nC2의 worst 케이스를 생각해보면
가능한 경우의 수는 4,999,950,000 -> 브루트 포스로 절대 못 품.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int solution(vector<pair<int, int>> &apply) {
    // 서류 1등은 무조건 합격(적어도 서류는 그 어떤 지원자보다 높으므로)
    int answer = 1;
    int temp = 0;

    for (int i = 1; i < apply.size(); i++) {
        // 서류 2등부터는 면접 순위가 1등보다는 높아야 함
        if (apply[temp].second > apply[i].second) {
            temp = i; // 높았다면 업데이트(왜냐하면 서류 순위가 낮은 다음 지원자가 얘보다는 면접 순위가 높아야 함)
            answer++;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t) {
        int n;
        cin >> n;
        vector<pair<int, int>> apply;
        for (int i = 0; i < n; i++) {
            int test, interview;
            cin >> test >> interview;
            apply.push_back(make_pair(test, interview));
        }

        sort(apply.begin(), apply.end()); // 서류, 순위로 오름차순 정렬(순위가 낮을 수록 잘 본 것)

        cout << solution(apply) << "\n";
        t--;
    }
}