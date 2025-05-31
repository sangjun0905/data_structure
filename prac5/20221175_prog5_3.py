class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def precedence(op):
    if op in ('+', '-'):
        return 1
    if op in ('*', '/'):
        return 2
    return 0


def dividePoly(poly):
    items = []
    i = 0
    while i < len(poly):
        ch = poly[i]
        if ch in ' ':
            i += 1
            continue
        elif ch in '+-*/()':
            items.append(ch)
            i += 1
        elif ch.isdigit():
            num = ch
            i += 1
            while i < len(poly) and (poly[i].isdigit()):
                num += poly[i]
                i += 1
            items.append(num)
        else:
            print("올바른 정수식 입력: ")
            exit(1)
    return items


def calcPostfix(items):
    stack = []

    for item in items:
        if item.isdigit():
            stack.append(int(item))

        else:
            b = stack.pop()
            a = stack.pop()

            if item == '+':
                stack.append(a + b)
            elif item == '-':
                stack.append(a - b)
            elif item == '*':
                stack.append(a * b)
            elif item == '/':
                if b == 0:
                    print("0으로 나눌 수 없습니다.")
                    exit(1)
                stack.append(a / b)
            else:
                print(f"지원하지 않는 연산자: {item}")
                exit(1)

    return round(stack[0], 10)


def infToPostf(items):
    output = []
    stack = []

    for item in items:
        if item.isdigit():
            output.append(item)

        elif item == '(':
            stack.append(item)

        elif item == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            if not stack:
                print("괄호 짝 오류")
                exit(1)
            stack.pop()

        else:
            while stack and stack[-1] != '(' and opOrder(stack[-1]) >= opOrder(item):
                output.append(stack.pop())
            stack.append(item)

    while stack:
        if stack[-1] in '()':
            print("괄호 짝 오류")
            exit(1)
        output.append(stack.pop())

    return output

def postfixToTree(postfix):
    stack = []

    for item in postfix:
        node = TreeNode(item)
        if item.isdigit():
            stack.append(node)
        else:
            right = stack.pop()
            left = stack.pop()
            node.left = left
            node.right = right
            stack.append(node)
    return stack[0] ## root 노드

def opOrder(op):
    if op in '*/':
        return 2
    elif op in '+-':
        return 1
    return 0


def printTree(node, tab=''):
    if node is None:
        return

    print(tab + '+--- ' + str(node.value))

    printTree(node.left, tab + '|    ')
    printTree(node.right, tab + '|    ')


def preorder(node):
    if node is None:
        return []
    return [node.value] + preorder(node.left) + preorder(node.right)


def inorder(node):
    if node is None:
        return []
    return inorder(node.left) + [node.value] + inorder(node.right)


def postorder(node):
    if node is None:
        return []
    return postorder(node.left) + postorder(node.right) + [node.value]


def levelorder(node):
    if node is None:
        return []
    
    result = []
    queue = [node]
    
    while queue:
        current = queue.pop(0)
        result.append(current.value)
        
        if current.left:
            queue.append(current.left)
        if current.right:
            queue.append(current.right)
    
    return result

if __name__ == "__main__":
    expr = input("수식 입력: ")
    items = dividePoly(expr)
    postfix = infToPostf(items)

    root = postfixToTree(postfix)

    print("수식 트리 구조:")
    printTree(root)
    print("\n")

    print("전위 순회:")
    print(preorder(root))
    print("\n")

    print("중위 순회:")
    print(inorder(root))
    print("\n")

    print("후위 순회:")
    print(postorder(root))
    print("\n")

    print("레벨 순회:")
    print(levelorder(root))

    print("\n계산 결과: " + str(calcPostfix(postfix)))
