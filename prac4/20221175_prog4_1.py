import time
from typing import List
from copy import deepcopy

class WordEntry:
    def __init__(self, word, mean):
        self.word = word
        self.mean = mean

    def __repr__(self):
        return f"{self.word}\t{self.mean}"

def compareLoweredWord(a, b):
    return (a.lower() > b.lower()) - (a.lower() < b.lower())

def readFile(filename):
    wordArrayByInsert = []
    with open(filename, encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if ' : ' not in line:
                continue
            word, mean = line.split(' : ', 1)
            entry = WordEntry(word.strip(), mean.strip())
            wordArrayByInsert.append(entry)
    return wordArrayByInsert, len(wordArrayByInsert)

def insertSort(wordArr):
    for i in range(1, len(wordArr)):
        key = wordArr[i]
        j = i - 1
        while j >= 0 and compareLoweredWord(wordArr[j].word, key.word) > 0:
            wordArr[j + 1] = wordArr[j]
            j -= 1
        wordArr[j + 1] = key

def qsortNotRecursive(wordArr):
    stack = [(0, len(wordArr) - 1)]
    while stack:
        left, right = stack.pop()
        if left >= right:
            continue
        pivot = wordArr[right]
        i = left - 1
        for j in range(left, right):
            if compareLoweredWord(wordArr[j].word, pivot.word) <= 0:
                i += 1
                wordArr[i], wordArr[j] = wordArr[j], wordArr[i]
        wordArr[i + 1], wordArr[right] = wordArr[right], wordArr[i + 1]
        p = i + 1
        stack.extend([(left, p - 1), (p + 1, right)])

def makeHeap(wordArr, n, i):
    root = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < n and compareLoweredWord(wordArr[left].word, wordArr[root].word) > 0:
        root = left
    if right < n and compareLoweredWord(wordArr[right].word, wordArr[root].word) > 0:
        root = right
    if root != i:
        wordArr[i], wordArr[root] = wordArr[root], wordArr[i]
        makeHeap(wordArr, n, root)

def heapSort(wordArr):
    n = len(wordArr)
    for i in range(n // 2 - 1, -1, -1):
        makeHeap(wordArr, n, i)
    for i in range(n - 1, 0, -1):
        wordArr[0], wordArr[i] = wordArr[i], wordArr[0]
        makeHeap(wordArr, i, 0)

def middleOfThree(wordArr, left, mid, right):
    a, b, c = wordArr[left].word.lower(), wordArr[mid].word.lower(), wordArr[right].word.lower()
    if a < b:
        if b < c:
            return mid
        elif a < c:
            return right
        else:
            return left
    else:
        if a < c:
            return left
        elif b < c:
            return right
        else:
            return mid

def betterQsortNotRecursive(wordArr):
    stack = [(0, len(wordArr) - 1)]
    while stack:
        left, right = stack.pop()
        if left >= right:
            continue
        mid = (left + right) // 2
        pivotIdx = middleOfThree(wordArr, left, mid, right) ## 3개의 값 중 중간값을 피봇으로 활용
        wordArr[pivotIdx], wordArr[right] = wordArr[right], wordArr[pivotIdx]
        pivot = wordArr[right]
        i = left - 1
        for j in range(left, right):
            if compareLoweredWord(wordArr[j].word, pivot.word) <= 0:
                i += 1
                wordArr[i], wordArr[j] = wordArr[j], wordArr[i]
        wordArr[i + 1], wordArr[right] = wordArr[right], wordArr[i + 1]
        p = i + 1
        stack.extend([(left, p - 1), (p + 1, right)])

def binarySearch(target, wordArr):
    left, right = 0, len(wordArr) - 1
    comparedCnt = 0
    while left <= right:
        mid = (left + right) // 2
        comparedCnt += 1
        cmp = compareLoweredWord(target, wordArr[mid].word)
        if cmp == 0:
            return mid, comparedCnt
        elif cmp < 0:
            right = mid - 1
        else:
            left = mid + 1
    return -1, comparedCnt

def main():
    wordArrayByInsert, wordCount = readFile("randdict_utf8.TXT")
    wordArrayByQuick = deepcopy(wordArrayByInsert)
    wordArrayByHeap = deepcopy(wordArrayByInsert)
    wordArrayBysort = deepcopy(wordArrayByInsert)
    wordArrayByBetterQsort = deepcopy(wordArrayByInsert)

    t1 = time.time()
    insertSort(wordArrayByInsert)
    t2 = time.time()
    print("삽입 정렬: %f초" % (t2 - t1))

    t1 = time.time()
    qsortNotRecursive(wordArrayByQuick)
    t2 = time.time()
    print("퀵 정렬: %f초" % (t2 - t1))

    t1 = time.time()
    heapSort(wordArrayByHeap)
    t2 = time.time()
    print("힙 정렬: %f초" % (t2 - t1))

    t1 = time.time()
    wordArrayBysort.sort(key=lambda x: x.word.lower())
    t2 = time.time()
    print("내장 sort 정렬: %f초" % (t2 - t1))

    t1 = time.time()
    betterQsortNotRecursive(wordArrayByBetterQsort)
    t2 = time.time()
    print("중간값을 피봇으로 한 퀵 정렬 시간: %f초" % (t2 - t1))

    while True:
        query = input("단어 입력 : ").strip()
        idx, comparedCnt = binarySearch(query, wordArrayByQuick)
        if idx != -1:
            entry = wordArrayByQuick[idx]
            print(f"({idx + 1}:{comparedCnt}) {entry.word}\t{entry.mean}")
        else:
            print("단어를 찾을 수 없습니다.")

if __name__ == "__main__":
    main()
