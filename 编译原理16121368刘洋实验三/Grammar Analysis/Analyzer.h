#include<bits/stdc++.h>
using namespace std;

class Analyzer
{
    public:
        string text;//PL0�ı�
        //ϵͳ���Ƽ���Ӧ�ķ��Ŵ�
        string clas[29]={"plus","minus","times","slash","oddsym","eql","neq","lss","leq","gtr","geq","lparen","rparen","comma",
                        "semicolon","period","becomes","beginsym","endsym","ifsym","thensym","whilesym","writesym","readsym",
                        "dosym","callsym","constsym","varsym","procsym"};
        string val[29]={"+","-","*","/","odd","=","#","<","<=",">",">=","(",")",",",";",".",":=","begin","end","if","then",
                        "while","write","read","do","call","const","var","procedure"};
        map<string,string> mp; //clas �� val ��ӳ���ϵ
        int idx; //���ڱ��text�Ķ�ȡλ��
        vector<string> words; //text�е����е���
        vector<string> res; //words ����Ӧ��ϵͳ����
        string str=""; //�﷨��������С��Ԫ
        int now=0; //���ڱ���﷨����������res��λ��
        int errorflag=0;
        Analyzer(string _text); //��ʼ��text��mp
        virtual ~Analyzer();
        string getNext(); //�õ�text����һ������
        string getSym();  //�õ�res�е���һ������
        //qb
        bool isLegalName(); //�ж�res�е������Ƿ���number+ident�Ƿ����
        bool isNone(char ch); //�ж��Ƿ�Ϊ'/t',' ','\n',EOF������ַ�
        bool isNumber(string s); //�ж��Ƿ�Ϊ����
        bool isIdent(string s); //�ж��Ƿ�Ϊ��ʶ��
        bool isExpression(); //�ж��Ƿ�Ϊ���ʽ
        bool isTerm(); //�ж��Ƿ�Ϊ��
        bool isFactor(); //�ж��Ƿ�Ϊ����
        //cj
        bool isCondition(); //�ж��Ƿ�Ϊ�������ʽ
        bool isSentence();//�ж��Ƿ�Ϊ���
        bool isComplexSentence();//�������
        bool isJudgement();//�ж��Ƿ�Ϊ�������
        bool isLoop();//�ж��Ƿ�Ϊѭ�����
        bool isAssignment(); //��ֵ���
        //ly
        bool isProgram(); //����
        bool isBlock();//�ֳ���
        bool isProcedureDescription();//����˵��
        bool isProcedureCall();//���̵������
        bool isProcedureHead();//�����ײ�
        //lj
        bool isConstDeclaration();//����˵��
        bool isVarDeclaration();//����˵��
        bool isConstDefinition();//��������
        bool isWrite();//�����
        bool isRead();//д���

        bool find(string s); //��map�в���s

    protected:

    private:
};

Analyzer::Analyzer(string _text)
{
    //ctor
    text = _text;
    idx=0;
    //�������ַ���ΪСд
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
//��ʶ��
bool Analyzer::isIdent(string s)
{
    if(s==""||!(s[0]>='a'&&s[0]<='z')){
        return false;
    }
    for(int i=1;i<s.length();i++)
    {
        if(!(s[i]>='a'&&s[i]<='z'||s[i]>='0'&&s[i]<='9')){
            if (errorflag==0){
                cout<<"��ʶ�����Ϸ�"<<endl;
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
            //cout<<"���ֲ��Ϸ�"<<endl;
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
                    cout<<"��number+ident�Ƿ����"<<endl;
                    errorflag=1;
                }
                errorflag=1;
            }
            return false;
        }
    }
    return true;
}
//����
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
                cout<<"�����б��ʽȱ��������"<<endl;
                errorflag=1;
            }flag=false;
        }
    }else
    {
        if (errorflag==0){
            cout<<"�����б��ʽȱ��������"<<endl;
            errorflag=1;
        }flag=false;
    }
    return flag;
}
//��
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
//���ʽ
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
//�ж��Ƿ�Ϊ�������ʽ
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
                cout<<"�������ʽ�й�ϵ������д�"<<endl;
                errorflag=1;
            }//str=getSym();
        }
    }

    return flag;
}
//���
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
//�������
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
            cout<<"�������ȱ��begin"<<endl;
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
            cout<<"�������ȱ��end"<<endl;
        }
    }
    str=getSym();
    return flag;
}
//�������
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
                cout<<"�������ȱ��then"<<endl;
                errorflag=1;
            }//str=getSym();
        }
    }
    else{
        flag=false;
        if (errorflag==0){
            cout<<"�������ȱ��if"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//��ѭ���ṹ
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
                cout<<"��ѭ�����ȱ��do"<<endl;
                errorflag=1;
            }
            //str=getSym();
        }
    }
    else{
        flag=false;
        if (errorflag==0){
            cout<<"��ѭ�����ȱ��while"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//��ֵ���
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
                cout<<"��ֵ���ȱ��:="<<endl;
                errorflag=1;
            }
            //str=getSym();
        }
    }
    else
    {
        flag=false;
        if (errorflag==0){
            cout<<"��ֵ���ȱ�ٱ�ʶ��"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//�����
bool Analyzer::isRead()
{
    bool flag=true;
    if (str=="readsym")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0){
            cout<<"�����ȱ��read"<<endl;
            errorflag=1;
        }
    }
    if (str=="lparen")
    {
        str=getSym();
    }else{
        flag=false;
        if (errorflag==0){
            cout<<"�����ȱ��������"<<endl;
            errorflag=1;
        }
    }
    if(str!="ident")
    {
        flag=false;
        if (errorflag==0){
            cout<<"�����ȱ�ٱ�ʶ��"<<endl;
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
                cout<<"�����ȱ�ٱ�ʶ��"<<endl;
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
            cout<<"�����ȱ��������"<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//д���
bool Analyzer::isWrite()
{
    bool flag=true;
    if (str=="writesym")
    {
        str=getSym();
    }else{

        flag=false;
        if (errorflag==0){
            cout<<"�����ȱ��write"<<endl;
            errorflag=1;
        }
    }
    if (str=="lparen")
    {
        str=getSym();
    }else{

        flag=false;
        if (errorflag==0){
            cout<<"�����ȱ��������"<<endl;
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
            cout<<"�����ȱ��������"<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//����
bool Analyzer::isProgram()
{
    bool flag=isBlock();
    if(str!="period")
    {
        flag=false;
        if (errorflag==0){
            cout<<"����ȱ�ٽ�������."<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//�ֳ���
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
//����˵��
bool Analyzer::isConstDeclaration()
{
    bool flag=true;

    if(str!="constsym")
    {
        flag=false;
        if (errorflag==0){
            cout<<"����˵��ȱ��const"<<endl;
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
            cout<<"����˵��ȱ�ٷֺ�;"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}
//��������
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
                    cout<<"��������ȱ������"<<endl;
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
                cout<<"��������ȱ��="<<endl;
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
            cout<<"��������ȱ�ٱ�ʶ��"<<endl;
            errorflag=1;
        }
        //str=getSym();
    }
    return flag;
}
//����˵��
bool Analyzer::isVarDeclaration()
{
    bool flag=true;

    if(str!="varsym")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"����˵��ȱ��var"<<endl;
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
            cout<<"����˵��ȱ�ٱ�ʶ��"<<endl;
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
                cout<<"����˵��ȱ�ٱ�ʶ��"<<endl;
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
            cout<<"����˵��ȱ��;"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}

//����˵��
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
            cout<<"����˵��ȱ��;"<<endl;
            errorflag=1;
        }
    }
    str=getSym();
    return flag;
}
//�����ײ�
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
            cout<<"�����ײ�ȱ��procedure"<<endl;
            errorflag=1;
        }
    }
    if (str!="ident")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"�����ײ�ȱ�ٱ�ʶ��"<<endl;
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
            cout<<"�����ײ�ȱ��;"<<endl;
            errorflag=1;
        }
    }
    return flag;
}
//���̵������
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
            cout<<"���̵���ȱ��call"<<endl;
            errorflag=1;
        }
    }
    if(str!="ident")
    {
        flag=false;
        if (errorflag==0)
        {
            cout<<"���̵���ȱ�ٱ�ʶ��"<<endl;
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
