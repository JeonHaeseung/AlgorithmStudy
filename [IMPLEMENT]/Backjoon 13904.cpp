/*
문제 링크: https://www.acmicpc.net/problem/1094
문제 이름: [1094번] 막대기
카테고리: BEAKJOON
최종 업로드 날짜: 2024.03.30
버전: v1
*/

/*문제 풀이: 이진수 변환과 같은 문제라고 보면 된다.
64cm의 막대에서 나올 수 있는 작은 막대는 32, 16, 8, 4, 2, 1로, 전부 2의 배수이다.
 */

#include <iostream>
#include <string>

using namespace std;

// 2로 나눌 때의 나머지를 이용한 변환법
int divide_by_two(int num) {
    int result = 0;
    int remain;
    int i = 1;

    while (num > 0) {
        remain = num % 2;
        result += remain * i;
        num /= 2;
        i *= 10;
    }

    return result;
}

int solution(int x) {
    int final_answer = 0;
    string two_string;

    two_string = to_string(divide_by_two(x));
    for (int i = 0; i < two_string.size(); i++) {
        if (two_string[i] == '1') {
            final_answer++;
        }
    }

    return final_answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x;

    cin >> x;
    cout << solution(x);
}