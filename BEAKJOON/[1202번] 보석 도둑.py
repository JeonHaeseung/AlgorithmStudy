"""
문제 링크: https://www.acmicpc.net/problem/1202
문제 이름: [1202] 보석 도둑
카테고리: BEAKJOON
최종 업로드 날짜: 2024.01.06
버전: v1
"""

"""
문제 풀이: 
"""
import sys
import heapq

# map 함수를 통해서 int 형으로 값을 받아옴
N, K = map(int, sys.stdin.readline().split())

jew = []
for _ in range(N):
    # 무게 M, 가격 V
    heapq.heappush(jew, list(map(int, sys.stdin.readline().split())))

bags = []
for _ in range(K):
    # 최대 무게 C 배열에 저장
    bags.append(int(sys.stdin.readline()))
bags.sort()

answer = 0
tmp_jew = []
for bag in bags:
    while jew and bag >= jew[0][0]:
        heapq.heappush(tmp_jew, -heapq.heappop(jew)[1])
    if tmp_jew:
        answer -= heapq.heappop(tmp_jew)
    elif not jew:
        break
print(answer)