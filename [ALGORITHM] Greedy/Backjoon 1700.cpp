/*
문제 링크: https://www.acmicpc.net/problem/1700
문제 이름: [1700번] 멀티탭 스케줄링
카테고리: BEAKJOON
최종 업로드 날짜: 2024.04.05
버전: v2
*/

/*문제 풀이: 첫 소감은 컴퓨터구조의 cache에서 LFU(Least Frequently Used)와 비슷하는 생각이 들었다.
처음으로 짠 로직은 앞으로 가장 적게 사용할 전자용품을 빼는 것이었는데, 이 로직은 성공적이지 못했다.
(그 이유는 앞으로 가장 적게 사용할 전자용품이라고 해도 바로 다음에 사용하는 애라면 빼서는 안되기 때문)
두 번째로 짠 로직은 앞으로 가장 나중에 사용할 전자용품을 빼는 것이었고, 이 로직은 성공적이었다. 즉 LFU가 아니라 LRU(의 반대 개념)로 푸는 문제였다.
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int find_far(int index, vector<int> &multi_tap, vector<int> &electronic) {

    int last_need = -1;  // 가장 늦게 다가올 차례
    int last_index = -1; // 뺄 멀티탭 자리

    for (int i = 0; i < multi_tap.size(); i++) {
        int tmp = 0;
        for (int j = index; j < electronic.size(); j++) {
            if (electronic[j] == multi_tap[i]) {
                break;
            }
            tmp++;
        }
        if (tmp > last_need) {
            last_need = tmp;
            last_index = i;
        }
    }

    return last_index; // 앞으로 가장 늦게 다시 사용하게 될 전기용품의 인덱스 반환
}

int find_no_useage(vector<int> &multi_tap) {
    for (int i = 0; i < multi_tap.size(); i++) {
        if (multi_tap[i] == 0) {
            return i; // 인덱스 반환
        }
    }
    return -1;
}

bool find_already(int device, vector<int> &multi_tap) {
    for (int i = 0; i < multi_tap.size(); i++) {
        if (multi_tap[i] == device) {
            return true;
        }
    }
    return false;
}

int solution(int n, int k, vector<int> &electronic, vector<int> &useage) {
    int answer = 0;
    vector<int> multi_tap(n, 0);

    for (int i = 0; i < k; i++) {
        if (find_already(electronic[i], multi_tap)) { // 지금 꼽을 애가 이미 꼽혀져 있다면 pass
            continue;

        } else if (find_no_useage(multi_tap) != -1) { // 새롭게 꼽아야 하는데 멀티텝이 비어있는게 있다면 그냥 꼽기
            multi_tap[find_no_useage(multi_tap)] = electronic[i];

        } else { // 새로운 애를 꼽아야 하는데 멀티텝이 비어있는 게 없다면, 가장 늦게 다시 사용해야 하는 애를 빼고 answer+1
            multi_tap[find_far(i, multi_tap, electronic)] = electronic[i];
            answer++;
        }

        useage[electronic[i]]--;
    }

    return answer;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> electronic(k, -1);
    vector<int> useage(k + 1, 0); // K (1 ≤ K ≤ 100)이므로 0번째 인덱스 필요없음

    for (int i = 0; i < k; i++) {
        cin >> electronic[i];
        useage[electronic[i]]++;
    }

    cout << solution(n, k, electronic, useage);
}