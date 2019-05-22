import re

f = open("test5.txt", "r")
# 把回车和两个空格都变成一个空格
string = f.read().lower().replace("\n", " ").replace("  ", " ")
print(string)
# 单个符号
d = ["+", "-", "*", "/", ">", "<", "=", ":", "#", "(", ")", ",", ";", "."]

a = ["begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"]
a1 = ["beginsym", "callsym", "constsym", "dosym", "endsym", "ifsym", "oddsym", "proceduresym", "readsym", "thensym",
      "varsym", "whilesym", "writesy"]

b = ["+", "-", "*", "/", "=", "#", "<", "<=", ">", ">=", ":=", "(", ")", ",", ";", "."]
b1 = ["plus", "minus", "times", "slash", "eql", "neq", "lss", "leq", "gtr", "geq", "becomes", "lapern", "rparen",
      "comma", "semicolon", "period"]

allword = []
word = []

for i in range(len(string)):
    if 'a' <= string[i] <= 'z':
        word.append(string[i])
        if 'a' <= string[i + 1] <= 'z' or '0' <= string[i + 1] <= '9':
            continue
        else:
            word2 = "".join(word)
            # print(word2)
            allword.append(word2)
            word.clear()

    if '0' <= string[i] <= '9':
        word.append(string[i])
        if '0' <= string[i + 1] <= '9':
            continue
        else:
            word2 = "".join(word)
            print(word2)
            allword.append(word2)
            word.clear()

    if string[i] == ':' and string[i + 1] == '=':
        allword.append(":=")
        continue
    if string[i] == '<' and string[i + 1] == '=':
        allword.append("<=")
        continue
    if string[i] == '>' and string[i + 1] == '=':
        allword.append(">=")
        continue
    if string[i] == '=':
        if string[i - 1] != '>' and string[i - 1] != '>' and string[i - 1] != ':':
            allword.append(string[i])
    for dd in d:
        if string[i] == dd and string[i]!='=':
            allword.append(string[i])
print(allword)
f2 = open('result2.txt','a')
for i in allword:
    tag2 = 0
    for j1 in range(len(a)):
        if i == a[j1]:
            tag2 = 1
            break
        # continue
    for j2 in range(len(b)):
        if i == b[j2]:
            tag2 = 2
            break
        # continue
    if tag2 == 1:
        print("(", a1[j1], ",", i, ")")
        f2.write("("+a1[j1]+ ","+i+ ")")
    if tag2 == 2:
        print("(", b1[j2], ",", i, ")")
        f2.write("("+b1[j2]+ ","+ i+ ")")
    if re.match("\d", i, re.I | re.S) != None:
        tag2 = 3
        print("(", "number", ",", i, ")")
        f2.write("("+"number"+ ","+ i+ ")")
    if tag2 == 0:
        print("(", "ident", ",", i, ")")
        f2.write("(" + "ident" + "," + i + ")")
    f2.write("\n")
