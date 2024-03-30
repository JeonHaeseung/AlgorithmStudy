/*
문제 링크: https://www.acmicpc.net/problem/1038
문제 이름: [1038번] 감소하는 수
카테고리: BEAKJOON
최종 업로드 날짜: 2023.03.30
버전: v1
*/

/*문제 풀이: N은 1,000,000보다 작거나 같은 자연수 또는 0이라고 했지만,

 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int solution(int n) {
    if (n >= 0 && n <= 9) { // 0~9까지라면 그대로 리턴
        return n;
    }

    int left = n - 9;
    // C(n, k) = n! / (k! * (n-k)!)
    int digit = 2;
    while (digit <= 10) { // 자릿수는 2번째 부터 시작
        int number = factorial(9) / (factorial(digit) * factorial(9 - digit));
        cout << number << " \n";
        if (number < left) {
            left -= number;
            cout << "left " << left << " \n";
        } else {
            break;
        }
        digit++;
    }

    // 감소하는 숫자의 최대값인 9876543210 이상의 범위라면 return -1
    if (digit > 10 && left > 0) {
        return -1;
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n; // 감소하는 수 번호
    cin >> n;

    cout << solution(n);
}