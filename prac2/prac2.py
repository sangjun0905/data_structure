def split(poly): ## 수식 split
    result = []
    i = 0
    while i < len(poly): ## 수식 parsing
        char = poly[i]
        if (char == ' '):
            i += 1
            continue
        elif (char in '+-*/()'):
            if (char == '*' and i + 1 < len(poly) and poly[i + 1] == '*'):
                result.append('**')
                i += 2
            else:
                result.append(char)
                i += 1

        elif (char.isdigit() or char == '.'):
            num = char
            i += 1
            while (i < len(poly) and (poly[i].isdigit() or poly[i] == '.')):
                num += poly[i]
                i += 1
            result.append(num)

        else:
            print(f"{i+1}번째 문자 에러: {char}")
            exit()
    return result


def opOrder(op):    ## 연산자 계산 순서
    if (op == '**'): return 3
    if (op in '*/'): return 2
    if (op in '+-'): return 1
    return 0


def toPostfix(poly): ## 후위표기 변환
    output = []     ## 숫자 + 연산자 저장
    stack = []      ## 연산자 임시 저장
    for x in poly:
        if (x.replace('.', '', 1).isdigit()):
            output.append(x)
        elif (x == '('):
            stack.append(x)
        elif (x == ')'):   ## 닫는 괄호 나올 시 '(' 까지 전부 꺼내고, 연산 수행, 이후 괄호 삭제
            while (stack and stack[-1] != '('): 
                output.append(stack.pop())
            if (not stack):
                print("괄호 에러")
                exit()
            stack.pop()
        else:
            while (stack and stack[-1] != '(' and opOrder(stack[-1]) >= opOrder(x)):  ## 괄호 이후 첫 연산자는 바로 stack 에 저장
                output.append(stack.pop())
            stack.append(x)  
    while (stack):
        if (stack[-1] in '()'):
            print("괄호 에러")
            exit()
        output.append(stack.pop())
    return output


def evalPost(postPoly):
    stack = []
    for x in postPoly:
        if (x.replace('.', '', 1).isdigit()):
            stack.append(float(x))
        else:
            b = stack.pop()
            a = stack.pop()
            if (x == '+'):
                stack.append(a + b)
            elif (x == '-'):
                stack.append(a - b)
            elif (x == '*'):
                stack.append(a * b)
            elif (x == '/'):
                if (b == 0):
                    print("0으로 나눌 수 없음")
                    exit()
                stack.append(a / b)
            elif (x == '**'):
                stack.append(a ** b)
            else:
                print(f"연산자 에러: {x}")
                exit()
    return stack[0]


if __name__ == "__main__":
    while (True):
        poly = input("수식 입력: ")

        splited = split(poly)
        postPoly = toPostfix(splited)
        result = evalPost(postPoly)
        print("= ", result)
        print("후위 표기: ", postPoly)
