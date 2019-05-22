#include<bits/stdc++.h>
using namespace std;

class Analyzer
{
    public:
        string text;//PL0文本
        //系统名称及对应的符号串
        string clas[29]={"plus","minus","times","slash","oddsym","eql","neq","lss","leq","gtr","geq","lparen","rparen","comma",
                        "semicolon","period","becomes","beginsym","endsym","ifsym","thensym","whilesym","writesym","readsym",
                        "dosym","callsym","constsym","varsym","procsym"};
        string val[29]={"+","-","*","/","odd","=","#","<","<=",">",">=","(",")",",",";",".",":=","begin","end","if","then",
                        "while","write","read","do","call","const","var","procedure"};
        map<string,string> mp; //clas 与 val 的映射关系
        int idx; //用于标记text的读取位置
        vector<string> words; //text中的所有单词
        vector<string> res; //words 所对应的系统名字
        string str=""; //语法分析的最小单元
        int now=0; //用于标记语法分析中所处res的位置
        int errorflag=0;
        Analyzer(string _text); //初始化text及mp
        virtual ~Analyzer();
        string getNext(); //得到text的下一个单词
        string getSym();  //得到res中的下一个单词
        //qb
        bool isLegalName(); //判断res中的命名是否有number+ident非法组合
        bool isNone(char ch); //判断是否为'/t',' ','\n',EOF此类空字符
        bool isNumber(string s); //判断是否为整数
        bool isIdent(string s); //判断是否为标识符
        bool isExpression(); //判断是否为表达式
        bool isTerm(); //判断是否为项
        bool isFactor(); //判断是否为因子
        //cj
        bool isCondition(); //判断是否为条件表达式
        bool isSentence();//判断是否为语句
        bool isComplexSentence();//复合语句
        bool isJudgement();//判断是否为条件语句
        bool isLoop();//判断是否为循环语句
        bool isAssignment(); //赋值语句
        //ly
        bool isProgram(); //程序
        bool isBlock();//分程序
        bool isProcedureDescription();//过程说明
        bool isProcedureCall();//过程调用语句
        bool isProcedureHead();//过程首部
        //lj
        bool isConstDeclaration();//常量说明
        bool isVarDeclaration();//变量说明
        bool isConstDefinition();//常量定义
        bool isWrite();//读语句
        bool isRead();//写语句

        bool find(string s); //在map中查找s

    protected:

    private:
};

Analyzer::Analyzer(string _text)
{
    //ctor
    text = _text;
    idx=0;
    //将所有字符变为小写
    for(int i=0;i<text.length();i++)
    {
        if(text[i]>='A'&&text[i]<='Z')
        {
            text[i]+='a'-'A';
        }
    }
    for(int i=0;i<29;i++)
    {
        mp[val[i]]=clas[i];
    }
}

Analyzer::~Analyzer()
{
    //dtor
}

string Analyzer::getNext()
{
    string tmp="";
    while(idx<text.length()&&isNone(text[idx]))
    {
        idx++;
    }
    if(idx>=text.length()) return "";

    tmp+=text[idx];
    if(text[idx]>='a'&&text[idx]<'z')
    {
        idx++;
        while((idx<text.length())&&(text[idx]>='a'&&text[idx]<='z'||text[idx]>='0'&&text[idx]<='9'))
        {
            tmp+=text[idx++];
        }
    }else if(text[idx]>='0'&&text[idx]<='9')
    {
        idx++;
        while(idx<text.length()&&text[idx]>='0'&&text[idx]<='9')
        {
            tmp+=text[idx++];
        }
    }else if(text[idx]=='<')
    {
        idx++;
        if(idx<text.length()&&text[idx]=='=')
        {
            tmp+=text[idx++];
        }
    }else if(text[idx]=='>')
    {
        idx++;
        if(idx<text.length()&&text[idx]=='=')
        {
            tmp+=text[idx++];
        }
    }else if(text[idx]==':')
    {
        idx++;
        if(idx<text.length()&&text[idx]=='=')
        {
            tmp+=text[idx++];
        }
    }else
    {
        idx++;
    }
    return  tmp;
}

bool Analyzer::isNone(char ch)
{
    if(ch==' '||ch==10||ch==13||ch=='\t') return true;
    return false;
}
//标识符
bool Analyzer::isIdent(string s)
{
    if(s==""||!(s[0]>='a'&&s[0]<='z')){
        return false;
    }
    for(int i=1;i<s.length();i++)
    {
        if(!(s[i]>='a'&&s[i]<='z'||s[i]>='0'&&s[i]<='9')){
            if (errorflag==0){
                cout<<"标识符不合法"<<endl;
                errorflag=1;
            }
            return false;
        }
    }
    return true;
}

bool Analyzer::isNumber(string s)
{
    if(s=="") return false;
    for(int i=0;i<s.length();i++)
    {
        if(!(s[i]>='0'&&s[i]<='9'))
        {
            //cout<<"数字不合法"<<endl;
            return false;
        }
    }
    return true;
}

string Analyzer::getSym()
{
    return now<res.size()?res[now++]:"";
}

bool Analyzer::isLegalName()
{
    for(int i=0;i+1<res.size();i++)
    {
        if(res[i]=="number"&&res[i+1]=="ident")
        {
            if (errorflag==0){
                if (errorflag==0){
                    cout<<"有number+ident非法组合"<<endl;
                    errorflag=1;
                }
                errorflag=1;
            }
            return false;
        }
    }
    return true;
}
//因子
bool Analyzer::isFactor()
{
    bool flag=true;

    if(str=="ident")
    {
        str=getSym();
    }else if(str=="number")
    {
        str=getSym();
    }else if(str=="lparen")
    {
        str=getSym();
        flag&=isExpression();
        if(str=="rparen")
        {
            str=getSym();
        }else{
            if (errorflag==0){
                cout<<"因子中表达式缺少右括号"<<endl;
                errorflag=1;
            }flag=false;
        }
    }else
    {
        if (errorflag==0){
            cout<<"因子中表达式缺少左括号"<<endl;
            errorflag=1;
        }flag=false;
    }
    return flag;
}
//项
bool Analyzer::isTerm()
{
    bool flag=true;
    flag&=isFactor();

    while(str=="times"||str=="slash")
    {
        str=getSym();
        flag&=isFactor();
    }

    return flag;
}
//表达式
bool Analyzer::isExpression()
{
    bool flag=true;
    if(str=="plus"||str=="minus")
    {
        str=getSym();
    }
    flag&=isTerm();
    while(str=="plus"||str=="minus")
    {
        str=getSym();
        flag&=isTerm();
    }

    return flag;
}
//判断是否为条件表达式
bool Analyzer::isCondition()
{
    bool flag=true;
    if(str=="odd")
    {
        str=getSym();
        flag&=isExpression();
    }
    else
    {
        flag&=isExpression();
        if(str=="eql"||str=="neq"||str=="lss"||str=="leq"||str=="gtr"||str=="geq"){
            str=getSym();
            flag&=isExpression();
        }
        else
        {
            flag=false;
            if (errorflag==0){
                cout<<"条件表达式中关系运算符有错"<<endl;
                errorflag=1;
            }//str=getSym();
        }
    }

    return flag;
}
//语句
bool Analyzer::isSentence()
{
    bool flag=true;

    if(str=="ident")
    {
        flag&=isAssignment();
    }
    else if(str=="ifsym")
    {
        flag&=isJudgement();
    }
    else if(str=="whilesym")
    {
        flag&=isLoop();
    }
    else if(str=="callsym")
    {
        flag&=isProcedureCall();
    }
    else if(str=="beginsym")
    {
        flag&=isComplexSentence();
    }
    else if(str=="readsym")
    {
        flag&=isRead();
    }
    else if(str=="writesym")
    {
        flag&=isWrite();
    }
    return flag;
}
//复合语句
bool Analyzer::isComplexSentence()
{
    bool flag=true;
    if(str=="beginsym")
    {
        str=getSym();
        flag&=isSentence();
    }else
    {
        flag=false;
        if (errorflag==0){
            cout<<"复合语句缺少begin"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    while(str=="semicolon")
    {
        str=getSym();
        flag&=isSentence();
    }

    if(str!="endsym")
    {
        flag=false;
        if (errorflag==0){
            errorflag=1;
            cout<<"复合语句缺少end"<<endl;
        }
    }
    str=getSym();
    return flag;
}
//条件语句
bool Analyzer::isJudgement()
{
    bool flag=true;
    if(str=="ifsym")
    {
        str=getSym();
        flag&=isCondition();
        if(str=="thensym")
        {
            str=getSym();
            flag&=isSentence();
        }
        else
        {
            flag=false;
            if (errorflag==0){
                cout<<"条件语句缺少then"<<endl;
                errorflag=1;
            }//str=getSym();
        }
    }
    else{
        flag=false;
        if (errorflag==0){
            cout<<"条件语句缺少if"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//当循环结构
bool Analyzer::isLoop()
{
    bool flag=true;

    if(str=="whilesym")
    {

        str=getSym();
        flag&=isCondition();
        if(str=="dosym")
        {
            str=getSym();
            flag&=isSentence();
        }
        else
        {
            flag=false;
            if (errorflag==0){
                cout<<"当循环语句缺少do"<<endl;
                errorflag=1;
            }
            //str=getSym();
        }
    }
    else{
        flag=false;
        if (errorflag==0){
            cout<<"当循环语句缺少while"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//赋值语句
bool Analyzer::isAssignment()
{
    bool flag=true;
    if(str=="ident")
    {

        str=getSym();
        if(str=="becomes")
        {
            str=getSym();
            flag&=isExpression();
        }
        else
        {
            flag=false;
            if (errorflag==0){
                cout<<"赋值语句缺少:="<<endl;
                errorflag=1;
            }
            //str=getSym();
        }
    }
    else
    {
        flag=false;
        if (errorflag==0){
            cout<<"赋值语句缺少标识符"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//读语句
bool Analyzer::isRead()
{
    bool flag=true;
    if (str=="readsym")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少read"<<endl;
            errorflag=1;
        }
    }
    if (str=="lparen")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少左括号"<<endl;
            errorflag=1;
        }
    }
    if(str!="ident")
    {
        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少标识符"<<endl;
            errorflag=1;
        }

    }
    str=getSym();
    while(str=="comma"){
        str=getSym();
        if(str!="ident")
        {
            flag=false;
            if (errorflag==0){
                cout<<"读语句缺少标识符"<<endl;
                errorflag=1;
            }

        }
        str=getSym();
    }
    if (str=="rparen")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少右括号"<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//写语句
bool Analyzer::isWrite()
{
    bool flag=true;
    if (str=="writesym")
    {
        str=getSym();
    }else{

        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少write"<<endl;
            errorflag=1;
        }
    }
    if (str=="lparen")
    {
        str=getSym();
    }else{

        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少左括号"<<endl;
            errorflag=1;
        }
    }
    flag&=isExpression();
    while(str=="comma"){
        str=getSym();
        flag&=isExpression();
    }
    if (str=="rparen")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0){
            cout<<"读语句缺少右括号"<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//程序
bool Analyzer::isProgram()
{
    bool flag=isBlock();
    if(str!="period")
    {
        flag=false;
        if (errorflag==0){
            cout<<"程序缺少结束符号."<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//分程序
bool Analyzer::isBlock()
{
    bool flag=true;


    if(str=="constsym")
    {
        flag&=isConstDeclaration();
    }

    if(str=="varsym")
    {
        flag&=isVarDeclaration();
    }

    if(str=="procsym")
    {
        flag&=isProcedureDescription();
    }

    flag&=isSentence();

    return flag;
}
//常量说明
bool Analyzer::isConstDeclaration()
{
    bool flag=true;

    if(str!="constsym")
    {
        flag=false;
        if (errorflag==0){
            cout<<"常量说明缺少const"<<endl;
            errorflag=1;
        }

    }
    str=getSym();
    flag&=isConstDefinition();
    while(str=="comma")
    {
        str=getSym();
        flag&=isConstDefinition();
    }
    if(str!="semicolon")
    {
        flag=false;
        if (errorflag==0){
            cout<<"常量说明缺少分号;"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}
//常量定义
bool Analyzer::isConstDefinition()
{
    bool flag=true;
    if(str=="ident")
    {
        str=getSym();
        if(str=="eql")
        {
            str=getSym();
            if(str=="number")
            {
                str=getSym();
            }
            else
            {
                flag=false;
                if (errorflag==0)
                {
                    cout<<"常量定义缺少数字"<<endl;
                    errorflag=1;
                }
                //str=getSym();
            }
        }
        else
        {
            flag=false;
            if (errorflag==0)
            {
                cout<<"常量定义缺少="<<endl;
                errorflag=1;
            }
            //str=getSym();
        }
    }
    else
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"常量定义缺少标识符"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//变量说明
bool Analyzer::isVarDeclaration()
{
    bool flag=true;

    if(str!="varsym")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"常量说明缺少var"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    if(str=="ident")
    {
        str=getSym();
    }
    else
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"常量说明缺少标识符"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    while(str=="comma")
    {
        str=getSym();
        if(str!="ident")
        {

            flag=false;
            if (errorflag==0)
            {
                cout<<"常量说明缺少标识符"<<endl;
                errorflag=1;
            }
        }
        str=getSym();
    }
    if(str!="semicolon")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"常量说明缺少;"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}

//过程说明
bool Analyzer::isProcedureDescription()
{
    bool flag=true;

    flag&=isProcedureHead();
    flag&=isBlock();
    /*while(str=="semicolon")
    {
        str=getSym();
        flag&=isProcedureDescription();
    }*/
    if(str!="semicolon")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"过程说明缺少;"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}
//过程首部
bool Analyzer::isProcedureHead()
{
    bool flag=true;
    if(str=="procsym")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0)
        {
            cout<<"过程首部缺少procedure"<<endl;
            errorflag=1;
        }
    }
    if (str!="ident")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"过程首部缺少标识符"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    if (str=="semicolon")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0)
        {
            cout<<"过程首部缺少;"<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//过程调用语句
bool Analyzer::isProcedureCall()
{
    bool flag=true;
    if (str=="callsym")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0)
        {
            cout<<"过程调用缺少call"<<endl;
            errorflag=1;
        }
    }
    if(str!="ident")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"过程调用缺少标识符"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}

bool Analyzer::find(string s)
{
    return mp.find(s)!=mp.end();
}
