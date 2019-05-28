#   python3 program which takes brainfuck code as input an emits stacky code as output
#   simple run $python3 converter.py < "input_file_name" > "output_file_name"

from sys import stdin

valid = ['>', '<', '+', '-', '.', ',', '[', ']']
code = []
for line in stdin:
    for c in line:
        if (c in valid):
            code.append(c)


def handleSequence(add, sub, final):
    global code
    total = 0
    while len(code) > 0:
        c = code[0]
        if (c == add):
            total += 1
        elif (c == sub):
            total -= 1
        else:
            break
        code.pop(0)
    if (total != 0):
        final(total)
    return


def printMove(delta):
    op = ''
    for _ in range(abs(delta)):
        op += '>'
    print('b' if delta > 0 else 'a', op, 'a' if delta > 0 else 'b')
    return


def printChange(delta):
    print('a > add', abs(delta), '> add' if (delta > 0)
          else '> inv > add 1 > add', '> and 255 > and > a')
    return


def printInput():
    print('a > bin io > a')
    return


def printOutput():
    print('a + io')
    return


def printBracketOpen():
    print('a [')
    return


def printBracketClose():
    print('a ]')
    return


def handleOther():
    global code
    code.pop()
    return


while (len(code) > 0):
    c = code[0]
    if (c == '>' or c == '<'):
        handleSequence('>', '<', printMove)
    elif (c == '+' or c == '-'):
        handleSequence('+', '-', printChange)
    elif (c == '.'):
        printOutput()
        code.pop(0)
    elif (c == ','):
        printInput()
        code.pop(0)
    elif (c == '['):
        printBracketOpen()
        code.pop(0)
    elif (c == ']'):
        printBracketClose()
        code.pop(0)
    else:
        handleOther()
        code.pop(0)
