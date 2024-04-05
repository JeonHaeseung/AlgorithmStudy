/*
문제 링크: https://www.acmicpc.net/problem/1038
문제 이름: [1038번] 감소하는 수
카테고리: BEAKJOON
최종 업로드 날짜: 2023.03.30
버전: v1
*/

/*문제 풀이:  C(n, k) = n! / (k! * (n-k)!)로 순열을 사용하면 될 것이라고 생각했다.
 */
#include <iostream>
#include <vector>

using namespace std;

// 여기서 numbers는 long long 타입으로 선언해 놓고 정작 함수의 return 타입을 int로 해서 에러 발생
long long solution(int n, vector<long long> &numbers) {
    if (n > 1022)
        return -1;
    if (n == 0)
        return 0;

    for (int i = 0; i <= 9; i++) {
        numbers[i] = i;
    }

    int num = 10;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (numbers[i] % 10); j++) {
            numbers[num] = (numbers[i] * 10) + j;
            num += 1;
        }
    }

    return numbers[n];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; // 감소하는 수 번호
    cin >> n;
    // 여기서 n+1로 백터 크기 설정하면 DoubleFree 에러 발생, 이유를 모르겠음
    vector<long long> numbers(1000001, 0);
    cout << solution(n, numbers);
}