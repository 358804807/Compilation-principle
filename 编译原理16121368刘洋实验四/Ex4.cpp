/*
<���ʽ> -> [+|-]<��>{<�ӷ������> <��>}
<��> -><����>{<�˷������> <����>}
<����> -> <��ʶ��>|<�޷�������>|(<���ʽ>)
<�ӷ������> -> +|-
<�˷������> -> *|/

��Ϊ�ع��ķ���
<���ʽ>-><��> | <���ʽ>+<��> | <���ʽ>-<��>
<��>-><����> | <��>*<����> | <��>/<����>
<����>->(<���ʽ>) | <��ʶ��> | <��ʶ��>


*/



#include<bits/stdc++.h>
using namespace std;
//result �ʷ�������� analysis ԭ���ʽ
ifstream infile("result.txt");
ifstream infile2("in/analysis0.txt");
ofstream outfile("result.txt");

map<string,string> word;
std::map<string,string>::iterator it;

string str;//������ַ���
string sym;//���ͷ���
string sym2;//ֵ����

int count1=0,k=0,flag=0,conterr=0,lpnum=0;

int expressionAnalysis2();//���ʽ����
int termAnalysis2();//�����
int factorAnalysis2();//���ӷ���


void map_init() //��Ӧ��ϵ���г�ʼ��������ֻ�����˱��ʽ����ط���
{
    word["+"]="plus";
    word["-"]="minus";
    word["*"]="times";
    word["/"]="slash";
    word["="]="eql";
    word["("]="lparen";
    word[")"]="rparen";
}

void lexanalysis() //�ʷ�����-��������result ��Ԫʽ����
{
    char ch;
    char a;
    string word1;//string����ʶ�𵥴�
    string str;//string���������ַ�ʶ��
    ostringstream buf;
    while(buf&&infile2.get(ch)) buf.put(ch);//���ļ��е��ַ�������
    str= buf.str();//���õ����ַ����浽string���ͱ�����
    int csize=str.length();
    for(int i=0; i<csize; i++) //�������ַ������б���
    {
        while(str[i]==' '||str[i]=='\n') i++;//���ʼΪ�ո���з�����ָ���λ��������
        if(isalpha(str[i])) //�Ա�ʶ���ͻ����ֽ���ʶ��,���ÿ⺯��isalpha()
        {
            word1=str[i++];
            while(isalpha(str[i])||isdigit(str[i]))
            {
                word1+=str[i++];
            }
            it=word.find(word1);
            if(it!=word.end()) //�ж��ǲ��ǻ����֣���Ϊ��������������
            {
                outfile<<"("<<word[word1]<<","<<word1<<")"<<endl;
            }
            else //����ֱ�����
            {
                outfile<<"(ident"<<","<<word1<<")"<<endl;
            }
            i--;
        }
        else if(isdigit(str[i])) //�ж��ǲ��ǳ��������ÿ⺯��isdigit()
        {
            word1=str[i++];
            while(isdigit(str[i]))
            {
                word1+=str[i++];
            }
            if(isalpha(str[i]))
            {
                outfile<<"error"<<endl;
                break;
            }
            else
            {
                outfile<<"(number"<<","<<word1<<")"<<endl;
            }
            i--;
        }
        else  //�������Ļ��������ν����ж�
        {
            word1=str[i];
            it=word.find(word1);
            if(it!=word.end())
            {
                outfile<<"("<<word[word1]<<","<<word1<<")"<<endl;
            }
            else
            {
                outfile<<"error"<<endl;
                break;
            }
        }
    }
    infile2.close();
}

int advance() //����������һ������
{
    int found1,found2;
    if(!getline(infile,str))
    {
        return 0;
    }
    found1=str.find(',',0);
    if(found1==-1)
    {
        conterr++;
        cout<<"�﷨���� ʶ���ַ�����"<<endl;
        return -1;
    }
    found2=str.length();
    sym=str.substr(1,found1-1);
    sym2=str.substr(found1+1,found2-found1-2);
    return 1;
}

//���ʽ���������
int expressionAnalysis2() //���ʽ
{
    string op;
    int arg1,arg2,result;
    if(conterr)
    {
        return 0;
    }
    arg1=termAnalysis2();//ͨ��������õ���һ��������ֵ
    if(conterr)
    {
        return 0;
    }
    while((sym=="plus")||(sym=="minus"))
    {
        op=sym2;
        flag=advance();
        if(conterr)
        {
            return 0;
        }
        if(flag==0)
        {
            cout<<"�﷨���� <�ӷ������>��ȱ��"<<endl;
            conterr++;
            return 0;
        }
        arg2=termAnalysis2();//ͨ��������õ��ڶ���������ֵ
        if(conterr)
        {
            return 0;
        }
        if(op=="+") //���Ǽӷ���������мӷ����㣬���Եõ��Ľ�����б���
        {
            result=arg1+arg2;
            arg1=result;
        }
        else //���Ǽ�����������мӷ����㣬���Եõ��Ľ�����б���,��Ϊ��������
        {
            result=arg1-arg2;
            arg1=result;
        }
    }
    return arg1;//���ظñ��ʽ�������ֵ
}
int termAnalysis2() //��
{
    string op;
    int arg1,arg2,result;
    arg1=factorAnalysis2();//ͨ�����ӷ����õ���һ��������ֵ
    if(conterr)
    {
        return 0;
    }
    while((sym=="times")||(sym=="slash"))
    {
        op=sym2;
        flag=advance();
        if(conterr)
        {
            return 0;
        }
        if(flag==0)
        {
            conterr++;
            cout<<"�﷨���� <�˷������>��ȱ����"<<endl;
            return 0;
        }
        if(conterr)
        {
            return 0;
        }
        arg2=factorAnalysis2();//ͨ�����ӷ����õ��ڶ���������ֵ
        if(conterr)
        {
            return 0;
        }
        if(op=="*") //���ǳ˷���������мӷ����㣬���Եõ��Ľ�����б���
        {
            result=arg1*arg2;
            arg1=result;
        }
        else //���ǳ�����������мӷ����㣬���Եõ��Ľ�����б���
        {
            if(arg2==0)
            {
                conterr++;
                cout<<"��������Ϊ0"<<endl;
                return 0;
            }
            result=arg1/arg2;
            arg1=result;
        }
    }
    return arg1;//���ظ����������ֵ
}
int factorAnalysis2()
{
    int arg;
    if(sym=="ident") //�������ʽ�в�������ĸ�������޷���������
    {
        cout<<"�������ʽ�к�����ĸ"<<endl;
        conterr++;
        return 0;
    }
    else if(sym=="number")  //���������֣��򷵻���Ӧ��ֵ
    {
        arg=atoi(sym2.c_str());
        flag=advance();
        if(conterr)
        {
            return 0;
        }
        if(lpnum==0&&sym=="rparen")
        {
            conterr++;
            cout<<"�﷨���� ')'��ƥ��"<<endl;
            return 0;
        }
    }
    else if(sym=="lparen") //����������ţ���Ҫ����������ƥ�䣬���ж��м��ǲ��Ǳ��ʽ�����ó����ʽ��ֵ���з���
    {
        lpnum++;
        flag=advance();
        if(conterr)
        {
            return 0;
        }
        if(flag==0)
        {
            conterr++;
            cout<<"�﷨���� '('��ȱ�ٱ��ʽ"<<endl;
            return 0;
        }
        arg=expressionAnalysis2();//���ر��ʽ��ֵ
        if(conterr)
        {
            return 0;
        }
        if(flag==0||sym!="rparen")
        {
            conterr++;
            cout<<"�﷨���� ���ʽ����ȱ��')'"<<endl;
            return 0;
        }
        else
        {
            lpnum--;
            flag=advance();
            if(conterr)
            {
                return 0;
            }
            if(flag==0)
            {
                return arg;
            }
        }
    }
    else
    {
        cout<<"�﷨���� �����ײ���Ϊ<��ʶ��>|<�޷�������>|'('"<<endl;
        conterr++;
        return 0;
    }
    return arg;//���ظ������������ֵ
}
int main()
{
    int i=0,num,result;
    //��ʼ�ʷ�����
    map_init();
    lexanalysis();

    cout<<"PL/0�������ʽ�������������"<<endl<<endl;
    flag=advance();
    if(flag)
    {
        result=expressionAnalysis2();//��ʼ���б��ʽ����
        if(flag!=-1&&!conterr) //�����ʽ��ȷ��������ʽ��ֵ
        {
            cout<<result<<endl;
        }
    }
    else
    {
        cout<<"error!"<<endl;
        return 0;
    }
    infile.close();
    return 0;
}
