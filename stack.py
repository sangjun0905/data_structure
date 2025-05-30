#----------------------------------------------------------------------
class Stack :
    def __init__( self ):   
        self.top = []       

    def isEmpty( self ): return len(self.top) == 0
    def size( self ): return len(self.top)
    def clear( self ): self.top = []	

    def push( self, item ):
        self.top.append(item)

    def pop( self ):
        if not self.isEmpty():
            return self.top.pop(-1)

    def peek( self ):
        if not self.isEmpty():
            return self.top[-1]

    def __str__(self ):
        return str(self.top[::-1])

odd = Stack()				        
even = Stack()				        
for i in range(10):		    	    
    if i%2 == 0 : even.push(i) 		
    else : odd.push(i)			    
print(' 스택 even push 5회: ', even)
print(' 스택 odd  push 5회: ', odd)	
print(' 스택 even     peek: ', even.peek())
print(' 스택 odd      peek: ', odd.peek())	
for _ in range(2) : even.pop()		
for _ in range(3) : odd.pop()		
print(' 스택 even  pop 2회: ', even)
print(' 스택 odd   pop 3회: ', odd)	



#======================================================================
# Postfix 계산하기
#======================================================================	
def evalPostfix( expr ):
    s = Stack()			       
    for token in expr :			
        if token in "+-*/" :	
            val2 = s.pop()		
            val1 = s.pop()		
            if (token == '+'): s.push(val1 + val2)	
            elif (token == '-'): s.push(val1 - val2)
            elif (token == '*'): s.push(val1 * val2)
            elif (token == '/'): s.push(val1 / val2)
        else :				        
            s.push( float(token) )	

    return s.pop()		        	


expr1 = [ '8', '2', '/', '3', '-', '3', '2', '*', '+']
expr2 = [ '1', '2', '/', '4', '*', '1', '4', '/', '*']
print(expr1, ' --> ', evalPostfix(expr1))
print(expr2, ' --> ', evalPostfix(expr2))


#======================================================================
# infix to Postfix
#======================================================================

# 우선순위를 돌려주는 함수
def precedence (op):
    if   op=='(' or op==')' : return 0	
    elif op=='+' or op=='-' : return 1	
    elif op=='*' or op=='/' : return 2	
    else : return -1


def Infix2Postfix( expr ):		
    s = Stack()
    output = []			        
    for term in expr :
        if term in '(' :		
            s.push('(')			
        elif term in ')' :		
            while not s.isEmpty() :
                op = s.pop()
                if op=='(' : break;	
                else :			    
                    output.append(op)
        elif term in "+-*/" :		
            while not s.isEmpty() :	
                op = s.peek()		
                if( precedence(term) <= precedence(op)):
                    output.append(op)
                    s.pop()
                else: break
            s.push(term)		
        else :				    
            output.append(term)	

    while not s.isEmpty() :		
        output.append(s.pop())	

    return output	


infix1 = [ '8', '/', '2', '-', '3', '+', '(', '3', '*', '2', ')']
infix2 = [ '1', '/', '2', '*', '4', '*', '(', '1', '/', '4', ')']
postfix1 = Infix2Postfix(infix1)
postfix2 = Infix2Postfix(infix2)
result1 = evalPostfix(postfix1)
result2 = evalPostfix(postfix2)
print('  중위표기: ', infix1)
print('  후위표기: ', postfix1)
print('  계산결과: ', result1, end='\n\n')
print('  중위표기: ', infix2)
print('  후위표기: ', postfix2)
print('  계산결과: ', result2)
