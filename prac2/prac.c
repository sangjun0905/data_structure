def tokenize(expr):
    tokens = []
    i = 0
    while i < len(expr):
        ch = expr[i]
        if ch in ' \t':
            i += 1
            continue
        elif ch in '+-*/()':
            if ch == '*' and i+1 < len(expr) and expr[i+1] == '*':
                tokens.append('**')
                i += 2
            else:
                tokens.append(ch)
                i += 1
        elif ch.isdigit() or ch == '.':
            num = ch
            i += 1
            while i < len(expr) and (expr[i].isdigit() or expr[i] == '.'):
                num += expr[i]
                i += 1
            tokens.append(num)
        else:
            raise ValueError(f"^ {i} 위치에 오류가 있습니다. (잘못된 문자: '{ch}')")
    return tokens

def precedence(op):
    if op == '**': return 3
    if op in '*/': return 2
    if op in '+-': return 1
    return 0

def infix_to_postfix(tokens):
    output = []
    stack = []
    for token in tokens:
        if token.replace('.', '', 1).isdigit():
            output.append(token)
        elif token == '(':
            stack.append(token)
        elif token == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            if not stack or stack[-1] != '(':
                raise ValueError("^ 괄호 오류: 닫는 괄호에 대응되는 여는 괄호가 없습니다.")
            stack.pop()
        else:
            while stack and precedence(stack[-1]) >= precedence(token) and stack[-1] != '(':
                output.append(stack.pop())
            stack.append(token)
    while stack:
        if stack[-1] in '()':
            raise ValueError("^ 괄호 오류: 여는 괄호가 닫히지 않았습니다.")
        output.append(stack.pop())
    return output

def evaluate_postfix(postfix):
    stack = []
    for token in postfix:
        if token.replace('.', '', 1).isdigit():
            stack.append(float(token))
        else:
            b = stack.pop()
            a = stack.pop()
            if token == '+': stack.append(a + b)
            elif token == '-': stack.append(a - b)
            elif token == '*': stack.append(a * b)
            elif token == '/': stack.append(a / b)
            elif token == '**': stack.append(a ** b)
    result = stack[0]
    return int(result) if result == int(result) else round(result, 10)

def calculate(expr):
    try:
        expr = expr.replace(' ', '')
        tokens = tokenize(expr)
        postfix = infix_to_postfix(tokens)
        result = evaluate_postfix(postfix)
        print("= ", result)
    except ValueError as ve:
        print(str(ve))

# 테스트
while True:
    s = input("수식 입력 (종료하려면 'exit'): ")
    if s.strip() == 'exit':
        break
    calculate(s)
