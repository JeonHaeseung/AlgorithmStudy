/*
문제 링크: https://www.acmicpc.net/problem/11050
문제 이름: [11050번] 이항 계수 1
카테고리: BEAKJOON
최종 업로드 날짜: 2023.03.30
버전: v1
*/

#include <iostream>
#include <string>

using namespace std;

// 2로 나눌 때의 나머지를 이용한 변환법
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int solution(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;

    cin >> n >> k;
    cout << solution(n, k);
}