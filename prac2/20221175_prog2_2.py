def dividePoly(poly):
    items = []
    i = 0
    while i < len(poly):
        ch = poly[i]
        if ch in ' ':
            i += 1
            continue
        elif ch in '+-*/()':
            if ch == '*' and i + 1 < len(poly) and poly[i + 1] == '*':
                items.append('**')
                i += 2
            else:
                items.append(ch)
                i += 1
        elif ch.isdigit() or ch == '.':
            num = ch
            i += 1
            while i < len(poly) and (poly[i].isdigit() or poly[i] == '.'):
                num += poly[i]
                i += 1
            items.append(num)
        else:
            print("에러{i}에 잘못된 문자 입력되었습니다")
            exit(1)
    return items


def opOrder(op):
    if op == '**': return 3
    elif op in '*/': return 2
    elif op in '+-': return 1
    return 0


def infToPostf(items):
    output = []
    stack = []

    for item in items:
        if item.replace('.', '', 1).isdigit():  # 숫자인 경우
            output.append(item)

        elif item == '(':
            stack.append(item)

        elif item == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            if not stack:
                print("괄호 짝이 맞지 않습니다.")
                exit(1)
            stack.pop()  # '(' 제거

        else:  # 연산자
            while stack and stack[-1] != '(' and opOrder(stack[-1]) >= opOrder(item):
                output.append(stack.pop())
            stack.append(item)

    while stack:
        if stack[-1] in '()':
            print("괄호 짝이 맞지 않습니다.")
            exit(1)
        output.append(stack.pop())

    return output
