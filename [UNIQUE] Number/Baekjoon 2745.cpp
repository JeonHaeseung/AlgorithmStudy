/*
문제 링크: https://www.acmicpc.net/problem/2745
문제 이름: [2745번] 진법 변환
카테고리: BEAKJOON
최종 업로드 날짜: 2024.04.09
버전: v1
*/

/*문제 풀이: B진법 수 N을 10진법으로 바꾸면, 항상 10억보다 작거나 같으므로 int 형으로도 충분하다.
B진법을 10진법으로 바꾸는 방법: abc라는 숫자가 있다고 치면, a*B^2 + a*B^1 + a*B^0 이 10진법 공식이다.
10진법을 B진법으로 바꾸는 방법은 이 반대로, 10진법 수를 B로 나누어준 몫이다.
 */
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

vector<int> change_to_int(vector<char> char_num) {
    vector<int> int_num;
    for (int i = 0; i < char_num.size(); i++) {
        if (char_num[i] >= 'A' && char_num[i] <= 'Z') {
            int_num.push_back(char_num[i] - 55);
        } else {
            int_num.push_back(char_num[i] - '0');
        }
    }

    return int_num;
}

long long solution(vector<int> int_num, int b) {
    long long answer = 0;
    for (int digit = 0; digit <= int_num.size(); digit++) {
        answer += int_num[int_num.size() - 1 - digit] * pow(b, digit);
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string n;
    int b;

    cin >> n >> b;

    vector<char> number;

    for (int i = 0; i < n.length(); i++) {
        number.push_back(n[i]);
    }

    vector<int> int_num = change_to_int(number);

    cout << solution(int_num, b);
}
