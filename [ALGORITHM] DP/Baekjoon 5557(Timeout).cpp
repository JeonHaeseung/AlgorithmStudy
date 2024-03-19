/*
문제 링크: https://www.acmicpc.net/problem/5557
문제 이름: [5557번] 1학년
카테고리: BEAKJOON
최종 업로드 날짜: 2023.03.19
버전: v1
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

long long final_answer = 0;

/* 0이상 20 이하인지 확인*/
bool check_arrage(int curr_num)
{
    return (curr_num >= 0 && curr_num <= 20);
}

/* 정답이 맞는지 확인 */
bool check_answer(int result, int answer)
{
    return (result == answer);
}

bool check_possible(int curr_idx, int curr_num, int answer, vector<long> &number_sums)
{
    return (answer >= curr_num - number_sums[curr_idx + 1] && answer <= curr_num + number_sums[curr_idx + 1]);
}

/* 재귀적인 방식으로 답을 통과
curr_num은 여태까지 계산한 결과
bool 값 반환에서 리펙토링*/
void count_answer(int n, int curr_idx, int curr_num, vector<long> &numbers, vector<long> &number_sums)
{

    // 백트래킹
    // 범위가 안 맞는 경우에는 리턴
    if (!check_arrage(curr_num))
    {
        return;
    }

    // 어떻게 해도 결과값을 만드는 게 불가능 한 경우 리턴
    if (!check_possible(curr_idx, curr_num, numbers[n - 1], number_sums))
    {
        return;
    }

    // 마지막을 검사하고 있고, 답이 맞는 경우에는 answer 늘린 후 리턴
    if (curr_idx == n - 2)
    {
        if (check_answer(curr_num, numbers[n - 1]))
        {
            final_answer++;
            return;
        }
        else
            return;
    }

    // +- 모두 고려하기
    count_answer(n, curr_idx + 1, curr_num + numbers[curr_idx + 1], numbers, number_sums);
    count_answer(n, curr_idx + 1, curr_num - numbers[curr_idx + 1], numbers, number_sums);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<long> numbers(n);
    vector<long> number_sums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
        number_sums[i] = numbers[i];
    }

    for (int i = n - 2; i >= 0; i--)
    {
        number_sums[i] = number_sums[i] + number_sums[i + 1];
    }

    count_answer(n, 0, numbers[0], numbers, number_sums);
    cout << final_answer;
}