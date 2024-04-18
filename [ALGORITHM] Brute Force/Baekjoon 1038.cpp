/*
문제 링크: https://www.acmicpc.net/problem/1038
문제 이름: [1038번] 감소하는 수
카테고리: BEAKJOON
최종 업로드 날짜: 2024.04.05
버전: v2
*/

/*문제 풀이:  C(n, k) = n! / (k! * (n-k)!)로 조합을 사용하면 될 것이라고 생각했다(중복 없이 숫자를 뽑은 다음 감소하는 순서로 나열하면 되니까).
하지만 아니었음(숫자 자체를 구해야 하는 것이므로, 숫자의 갯수를 구하는 조합 사용 불가)
1자리 숫자에서 가장 작은 감소하는 수가 1일 때, 2자리 숫자에서는 가장 작은 감소하는 수가 10,
3자리 숫자에서는 가장 작은 감소하는 수가 10에서 뒷자리에 더 무언가를 추가할 수 없으므로 210이 되는 로직이라는 점을 고려하면 된다.
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