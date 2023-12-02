"""
문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/17686
문제 이름: [3차] 파일명 정렬
카테고리: 2018 KAKAO BLIND RECRUITMENT
최종 업로드 날짜: 2023.12.02
버전: v1
"""

"""
문제 풀이: state를 잘 분리해야 한다.
state 0은 head를 검사할 때, state 1은 number를 검사할 때, state 2는 tail을 검사할 때로 구분하였다.
또한, tail이 없이 number에서 끝나는 경우도 고려하였다.
"""
def split_file(files):
    split_arr = []
    for file_index, filename in enumerate(files):
        flag=0
        num_index=0
        head=""
        number=0
        tail=""
        for char_index, char in enumerate(filename):
            if char.isdigit()==True and flag==0: #처음으로 숫자를 마주친 경우
                head=filename[:char_index].lower()
                flag=1
                num_index=char_index
            if char_index==len(filename)-1 and flag==1: # 문자열의 마지막을 맞이한 경우
                number=int(filename[num_index:])
                tail=""
                break
            if char.isdigit()==False and flag==1: #숫자 다음으로 문자를 마주친 경우
                number=int(filename[num_index:char_index])
                tail=filename[char_index:]
                break
        split_tuple=(file_index, head, number, tail)
        print(split_tuple)
        split_arr.append(split_tuple)
        
    return split_arr

def custom_sort(item):
    return (item[1], item[2])

def answer_file(sorted_files, files):
    answer=[]
    for item in sorted_files:
        answer.append(files[item[0]]) # 원래 인덱스 값을 가져와서 순서대로 넣어주기
    return answer
            
def solution(files):
    split_arr = split_file(files)
    sorted_files = sorted(split_arr, key=custom_sort)
    answer = answer_file(sorted_files, files)
    return answer