/*
문제 링크: https://www.acmicpc.net/problem/1700
문제 이름: [1700번] 멀티탭 스케줄링
카테고리: BEAKJOON
최종 업로드 날짜: 2023.04.05
버전: v1
*/

/*문제 풀이: 첫 소감은 컴퓨터구조의 cache에서 LFU(Least Frequently Used)와 비슷하는 생각이 들었다.
그래서 앞으로 가장 적게 사용할 전자용품의 코드를 빼는 로직으로 작성해보았는데, 이 로직의 경우에는 실패였다.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int find_min(vector<int> &multi_tap, vector<int> &useage) {
    vector<pair<int, int>> multi_tap_useage(multi_tap.size());

    for (int i = 0; i < multi_tap.size(); i++) {
        multi_tap_useage.push_back(make_pair(useage[multi_tap[i]], i));
    }

    sort(multi_tap_useage.begin(), multi_tap_useage.end()); // 오름차순 정렬

    for (int i = 0; i < multi_tap_useage.size(); i++) {
        cout << multi_tap_useage[i].first << " " << multi_tap_useage[i].second << "   ";
    }
    cout << '\n';

    return multi_tap_useage[0].second; // 앞으로 가장 적게 사용할 전기용품의 인덱스 반환
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
        for (int i = 0; i < multi_tap.size(); i++) {
            cout << multi_tap[i] << " ";
        }
        cout << '\n';

        if (find_already(electronic[i], multi_tap)) { // 지금 꼽을 애가 이미 꼽혀져 있다면 pass
            continue;

        } else if (find_no_useage(multi_tap) != -1) { // 새롭게 꼽아야 하는데 멀티텝이 비어있는게 있다면 그냥 꼽기
            multi_tap[find_no_useage(multi_tap)] = electronic[i];

        } else { // 새로운 꼽아야 하는데 멀티텝이 비어있는 게 없다면, 앞으로 가장 적게 사용할 애를 빼고 answer+1
            multi_tap[find_min(multi_tap, useage)] = electronic[i];
            answer++;
            cout << "멀티텝\n";
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

    for (int i = 0; i < useage.size(); i++) {
        cout << useage[i] << " ";
    }
    cout << '\n';

    cout << solution(n, k, electronic, useage);
}