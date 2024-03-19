/*
문제 링크: https://www.acmicpc.net/problem/1112
문제 이름: [1112번] 진법 변환
카테고리: BEAKJOON
최종 업로드 날짜: 2023.11.27
버전: v1
*/

/*문제 풀이: 양의 진법인 경우와, 음의 진법인 경우를 따로 계산해주어야 한다.
양의 진법인 경우에는 기존의 숫자에 절대값을 취해준 다음 기존의 진법 계산 방식대로 계산한다.
음의 진법인 경우에는 나머지를 무조건 + 로 만들어주어야 한다. 나머지가 +가 되도록 몫을 변경한다.
*/
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

string translate_minus(int x, int b){
    int quotient = 1;
    int remainder = 1;
    int present_num = x;
    string answer = "";
    
     while(quotient!=0){
        quotient = present_num/b;
        remainder = present_num%b;
        
        if(remainder<0){
            if(quotient<0){
                quotient = (present_num/b)-1;
            } else{
                quotient = (present_num/b)+1;
            }
            remainder = present_num - quotient*b;
        }

        // 몫 업데이트
        present_num = quotient;
        
        answer = to_string(remainder) + answer;
    }
    
    return answer;
}

string translate_plus(int x, int b){
    int quotient = 1;
    int remainder = 1;
    int present_num = x;
    string answer = "";
    
     while(quotient!=0){
        quotient = present_num/b;
        remainder = present_num%b;

        // 몫 업데이트
        present_num = quotient;
        
        answer = to_string(remainder) + answer;
    }
    
    return answer;
}

string change_num(int x, int b){
    //초기화
    string answer = "";
    
    if(b<0){ //음의 진법 변환인 경우
        answer = translate_minus(x, b);
    }else{ //양의 진법 변환인 경우
        answer = translate_plus(abs(x), b);
        if(x<0){
            answer = "-" + answer;
        }
    }
    return answer;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int x; //최소~최대가 -10억~10억이므로 int 형으로도 충분분
    int b;
    
    cin >> x >> b;
    
    cout << change_num(x, b);
    
}
