/*
문제 링크: https://www.acmicpc.net/problem/17087
문제 이름: [17087번] 숨바꼭질 6
카테고리: BEAKJOON
최종 업로드 날짜: 2024.05.17
버전: v1
*/

/*접근 방식: "수빈이의 위치-동생의 위치"를 전부 구한 후, 이 숫자들의 최소공약수를 구하면 그게 바로 D이다.
이때 동생들의 숫자는 100000명이라고 했으므로 하나씩 최소공약수를 구해나가는 로직으로 풀어도 된다.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    int n;

    while (b != 0) {
        n = a % b;
        a = b;
        b = n;
    }

    // 최대공약수 리턴
    return a;
}

int solution(int n, int s, vector<int> &young) {
    // 코너 케이스: 동생이 하나일 경우
    if (n == 1)
        return abs(young[0]);

    int a = young[0];
    for (int i = 1; i < young.size(); i++) {
        a = gcd(max(a, young[i]), min(a, young[i]));
    }

    return a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, s;
    cin >> n >> s;

    // 동생까지의 거리를 저장하는 백터
    vector<int> young;

    for (int i = 0; i < n; i++) {
        int dist;
        cin >> dist;
        young.push_back(abs(s - dist));
    }

    cout << solution(n, s, young);
}
