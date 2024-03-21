/*
문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/17687
문제 이름: [3차] n진수 게임
카테고리: 2018 KAKAO BLIND RECRUITMENT
최종 업로드 날짜: 2023.11.26
버전: v1
*/

/*
문제 풀이: translated를 통해서 튜브뿐만 아니라 모든 사람의 정답을 구해놓고,
translated 배열 안에서 다시 for 문을 돌면서 튜브의 정답을 찾는 방법을 선택했다.
그 이유는 하나의 숫자 안에서도 튜브가 선택해야 하는 정답이 여러 개 있을 수 있기 때문이다.
예시) "4"라는 숫자는 이진수로 "100"이므로, 맴버가 2명이고 튜브가 첫번째 순서라면 숫자 2개 선택
또한, 진수 변환하는 로직을 translate_number를 통해서 함수화하였다.
*/
#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string translate_number(int n, int present_num) {
    // 몫과 나머지 초기화
    int quotient = 100;
    int remainder = 100;
    string translated = "";

    while (quotient > 0) {
        quotient = present_num / n;
        remainder = present_num % n;
        string str_num = "";

        if (remainder >= 10 && remainder <= 15) {
            // 숫자->대문자 변환은 'A' 더하기
            char char_num = 'A' + (remainder - 10);
            str_num += char_num;
        } else {
            str_num = to_string(remainder);
        }

        translated = str_num + translated;
        // 다음 자리 수 구하기
        present_num = quotient;
    }
    return translated;
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    string translated = "";

    // 진법 n, 미리 구할 숫자의 갯수 t, 게임에 참가하는 인원 m, 튜브의 순서 p
    // 구해야 하는 총 숫자 수(모든 맴버)=(t-1)*m+p
    int total_num = (t - 1) * m + p;
    int present_num = 0;
    while (1) {
        if (translated.length() >= total_num) {
            break;
        } else {
            translated += translate_number(n, present_num);
            present_num++;
        }
    }
    for (int i = p - 1; i <= total_num - 1; i += m) {
        // cout << i << " " << total_num << " " << translated[i] << "\n";
        answer += translated[i];
    }
    return answer;
}