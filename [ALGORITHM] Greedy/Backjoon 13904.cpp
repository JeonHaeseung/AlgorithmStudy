/*
문제 링크: https://www.acmicpc.net/problem/13904
문제 이름: [13904번] 과제
카테고리: BEAKJOON
최종 업로드 날짜: 2024.03.30
버전: v2
*/

/*문제 풀이: dp가 아니라 그리디여야 하는 이유는 작은 문제로 나눌 수 없기 때문이다.
knapsack 문제에서는 큰 문제를 작은 문제(해당 물품이 가방에 들어갔다고 가정할 때/아닐 때)로 나눌 수 있다.
그러나 이 문제는 해당 과제를 할 때/하지 않을 때로 결정하는 것이 아니다.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> hw; // pair는 미리 명시해두기

bool compair(const hw &a, const hw &b) {
    if (a.second == b.second) {
        a.first > b.first; // 첫 번째 기준 증가하는 순서
    }

    return a.second > b.second; // 두 번째 기준 감소하는 순서
}

int find_answer(int n, vector<hw> &hw_list, vector<int> &value) {
    int final_answer = 0;

    for (int i = 0; i < n; i++) {                    // 가장 높은 점수를 가지는 과제부터 하기
        for (int j = hw_list[i].first; j > 0; j--) { // 미룰 수 있을 때까지 미루기
            if (!value[j]) {                         // 해당 날짜에 아무 과제도 하지 않는다면
                value[j] = hw_list[i].second;
                final_answer += hw_list[i].second;
                break;
            }
        }
    }

    return final_answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n; // 과제의 갯수
    vector<hw> hw_list(n);

    for (int i = 0; i < n; i++) {
        cin >> hw_list[i].first >> hw_list[i].second;
    }

    sort(hw_list.begin(), hw_list.end(), compair); // 과제 일수 기준 , 과제 점수 기준 내림차순 정렬
    vector<int> value(1002);

    cout << find_answer(n, hw_list, value);
}