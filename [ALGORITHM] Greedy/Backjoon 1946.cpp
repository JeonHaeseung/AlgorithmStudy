/*
문제 링크: https://www.acmicpc.net/problem/1946
문제 이름: [1946번] 신입 사원
카테고리: BEAKJOON
최종 업로드 날짜: 2023.04.07
버전: v4
*/

/*문제 풀이: 어떤 A 지원자의 성적이 다른 B 지원자보다 적어도 하나는 높아야 한다.
N(1 ≤ N ≤ 100,000) 명의 지원자들을 단순하게 정말 직접 비교하는 nC2의 worst 케이스를 생각해보면
가능한 경우의 수는 4,999,950,000 -> 브루트 포스로 절대 못 품.
 */
/* v3 변경 내용: 기존에는 아래와 같이 temp라는 명확하지 않은 변수를 사용했고,
가장 작은 값 min 자체를 저장하는게 아니라 min을 만드는 index를 temp에 저장함
-> 인덱스를 저장하는 것은 직관적이지 않을 뿐더러 디버깅도 복잡하게 만듬, min 자체를 저장하는 것으로 변경

    int answer = 1; // 서류 1등은 반드시 선발
    int temp = 0;

    for (int i = 1; i < apply.size(); i++) {
        // 서류 2등부터는 면접 순위가 1등보다는 높아야 함
        if (apply[temp].second > apply[i].second) {
            temp = i; // 높았다면 업데이트(왜냐하면 서류 순위가 낮은 다음 지원자가 얘보다는 면접 순위가 높아야 함)
            answer++;
        }
    }
*/
/* v4 변경 내용: min이 1일 때는 for문을 break(왜냐하면 앞으로 더 높은 면접 순위가 등장할 수 없음)
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int solution(vector<pair<int, int>> &apply) {
    // 서류심사 성적과 면접시험 성적 중 적어도 하나가 다른 지원자보다 떨어지지 않는 자만 선발
    // == 서류 심사가 낮은 사람은 자신보다 서류 심사가 높은 모든 사람들 중에서 가장 면접 심사가 높아야 함
    // 면접 심사의 최소값(즉, 가장 높은 사람) 보다만 높으면 됨

    // 초기값
    int min = apply.front().second;
    int answer = 1; // 서류 1등은 반드시 선발

    for (int i = 1; i < apply.size(); i++) {
        if (min == 1) {
            break;
        }
        // 최소값 업데이트가 일어나는 경우에만 선발(서류 심사가 낮은 사람이지만, 면접 심사는 높다는 뜻이므로)
        if (min > apply[i].second) {
            min = apply[i].second;
            answer++;
        }
    }

    return answer;
}

// 시간 복잡도: 입력 O(n) + sort O(nlogn) + 선발 O(n) = O(2n + nlogn) = O(nlogn)
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

        sort(apply.begin(), apply.end(), less<>()); // 서류, 순위로 오름차순 정렬(순위가 낮을 수록 잘 본 것)

        cout << solution(apply) << "\n";
        t--;
    }
}