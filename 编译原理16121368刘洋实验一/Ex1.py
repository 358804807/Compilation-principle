import re

# 文件按行读取后连接成为一个字符串，变成小写字母的单词
f=open("test5.txt","r")
datalines=f.readlines()
datalines_string="".join(datalines).lower()
# 将文件中所有文本符号删去
allword=re.findall(r"[\w’]+", datalines_string)

# 按行读取，将所有var和const和procedure的行存下来
data=[]
list=["const","var","procedure"]
for line in datalines:
    for i in list:
        a=re.findall(i,line,re.I|re.S) #正则表达式匹配，忽略大小写
        if a!=[]:
            data.append(line)
# print(data) #带有const或者var的行

#list内容变成一个字符串string,lower()全部变成小写字母
string="".join(data).lower()
# 将这一个字符串中所有符号删去，变成单词
e=re.findall(r"[\w’]+", string)
# print(e)
biaoshifu=[]
# 把const var procedure 数值 都去掉
for i in e:
    if re.match("const",i,re.I|re.S)==None and re.match("var",i,re.I|re.S)==None \
            and re.match("\d",i,re.I|re.S)==None and re.match("procedure",i,re.I|re.S)==None:
        biaoshifu.append(i)
print("标识符：",biaoshifu)

# 新建一个存放计数的list
count=[0]*len(biaoshifu)
# 打开输入文件并输入
f2 = open('result.txt','a')
# print(allword)
for i in range(len(biaoshifu)):
    for word in allword:
        if biaoshifu[i]==word:
            count[i]=count[i]+1
    count[i]=str(count[i]) #输入文件需变成str
    print("(",biaoshifu[i],":",count[i],")")
    f2.write("("+biaoshifu[i]+":"+count[i]+")\n")
f2.write("\n")