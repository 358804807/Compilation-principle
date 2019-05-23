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
ifstream infile2("in/analysis8.txt");
ofstream outfile("result.txt");

map<string,string> word;
std::map<string,string>::iterator it;

string str;//������ַ���
string sym;//���ͷ���
string sym2;//ֵ����

int count1=0,k=0,flag=0,conterr=0,lpnum=0;

string expressionAnalysis();
string termAnalysis();
string factorAnalysis();

struct quad{//������Ԫʽ
     string result;
     string arg1;
     string arg2;
     string op;
};
struct quad quad[50];

void map_init(){//��Ӧ��ϵ���г�ʼ��������ֻ�����˱��ʽ����ط���
    word["+"]="plus";
    word["-"]="minus";
    word["*"]="times";
    word["/"]="slash";
    word["="]="eql";
    word["("]="lparen";
    word[")"]="rparen";
}

void lexanalysis(){//�ʷ�����
    char ch;
    char a;
    string word1;//string����ʶ�𵥴�
    string str;//string���������ַ�ʶ��
    ostringstream buf;
    while(buf&&infile2.get(ch)) buf.put(ch);//���ļ��е��ַ�������
    str= buf.str();//���õ����ַ����浽string���ͱ�����
    int csize=str.length();
    for(int i=0;i<csize;i++){//�������ַ������б���
        while(str[i]==' '||str[i]=='\n') i++;//���ʼΪ�ո���з�����ָ���λ��������
        if(isalpha(str[i])){//�Ա�ʶ���ͻ����ֽ���ʶ��,���ÿ⺯��isalpha()
            word1=str[i++];
            while(isalpha(str[i])||isdigit(str[i])){
                word1+=str[i++];
            }
            it=word.find(word1);
            if(it!=word.end()){//�ж��ǲ��ǻ����֣���Ϊ��������������
                outfile<<"("<<word[word1]<<","<<word1<<")"<<endl;
            }
            else{//����ֱ�����
                outfile<<"(ident"<<","<<word1<<")"<<endl;
            }
            i--;
        }
        else if(isdigit(str[i])){//�ж��ǲ��ǳ��������ÿ⺯��isdigit()
            word1=str[i++];
            while(isdigit(str[i])){
                word1+=str[i++];
            }
             if(isalpha(str[i])){
                outfile<<"error"<<endl;
                break;
            }
            else{
                outfile<<"(number"<<","<<word1<<")"<<endl;
            }
            i--;
        }else{//�������Ļ��������ν����ж�
            word1=str[i];
            it=word.find(word1);
            if(it!=word.end()){
                outfile<<"("<<word[word1]<<","<<word1<<")"<<endl;
            }else{
                outfile<<"error"<<endl;
                break;
            }
        }
    }
    infile2.close();
}

int advance(){//����result�ļ��ʷ������Ľ�� ����������һ������
    int found1,found2;
    if(!getline(infile,str)){
        return 0;
    }
    found1=str.find(',',0);
    if(found1==-1){
        conterr++;
        cout<<"�﷨���� ʶ���ַ�����"<<endl;
        return -1;
    }
    found2=str.length();
    sym=str.substr(1,found1-1);
    sym2=str.substr(found1+1,found2-found1-2);
    return 1;
}

//�м��������
string newtemp(){//�����±�����t1,t2��
    char *p;
    char m[12];
    p=(char*)malloc(12);
    k++;
    itoa(k,m,10); //������kת�����ַ���m ʮ����ת��
    strcpy(p+1,m); // ��m����ָ���һ��
    p[0]='t';
    string s;
    s=p;
    return s;
}

//������Ԫʽ������ʾ������¼����
void emit(string op,string arg1,string arg2,string result){
    quad[count1].op=op;
    quad[count1].arg1=arg1;
    quad[count1].arg2=arg2;
    quad[count1].result=result;
    count1++;
    return;
}
string expressionAnalysis(){//���ʽ�ĵݹ��½���������
    string op,arg1,arg2,result;
    if(conterr){
        return NULL;
	}
	arg1=termAnalysis();//ͨ��������õ���һ��������ֵ
	if(conterr){
        return NULL;
	}
	//ÿִ��һ��advance() ȫ�ֱ���sym sym2�����޸�һ�Σ���ɶ�Ԫʽ
	while((sym=="plus")||(sym=="minus")){
        op=sym2;
		flag=advance();
		if(conterr){
            return NULL;
		}
		if(flag==0){
            cout<<"�﷨���� <�ӷ������>��ȱ��"<<endl;
            conterr++;
			return NULL;
		}
		arg2=termAnalysis();//ͨ��������õ��ڶ���������ֵ
		if(conterr){
            return NULL;
		}
		result=newtemp();//�����м���������൱�ڶԽ�����д洢
		emit(op,arg1,arg2,result);//������Ԫʽ���൱�ڽ��мӷ���������㣬�ó����
		arg1=result;//����õ��Ľ��
	}
	return arg1;//���ر��ʽ���յõ���ֵ
}

string termAnalysis(){//��ĵݹ��½���������
    string op,arg1,arg2,result;
    arg1=factorAnalysis();//ͨ�����ӷ����õ���һ��������ֵ
    if(conterr){
        return NULL;
    }
	while((sym=="times")||(sym=="slash")){
        op=sym2;
		flag=advance();
		if(conterr){
            return NULL;
		}
		if(flag==0){
			conterr++;
			cout<<"�﷨���� <�˷������>��ȱ����"<<endl;
			return NULL;
		}
		if(conterr){
            return NULL;
		}
		arg2=factorAnalysis();//ͨ�����ӷ����õ��ڶ���������ֵ
		if(conterr){
            return NULL;
		}
		result=newtemp();//�����м���������൱�ڶԽ�����д洢
		emit(op,arg1,arg2,result);//������Ԫʽ���൱�ڽ��г˷���������㣬�ó����
		arg1=result;//����õ��Ľ��
	}
	return arg1;//���������յõ���ֵ
}

string factorAnalysis(){
    string arg;
    if(sym=="ident"){//����Ǳ�ʶ�������շ��ر�ʶ���ķ���
        arg=sym2;
        flag=advance();
        if(conterr){
            return NULL;
		}
		if(lpnum==0&&sym=="rparen"){
            conterr++;
			cout<<"�﷨���� ')'��ƥ��"<<endl;
			return NULL;
        }
    }
    else if(sym=="number"){//������޷������������շ�����Ӧ������
        arg=sym2;
        flag=advance();
        if(conterr){
            return NULL;
		}
		if(lpnum==0&&sym=="rparen"){
            conterr++;
			cout<<"�﷨���� ')'��ƥ��"<<endl;
			return NULL;
        }
    }
    else if(sym=="lparen"){//����������ţ���Ҫ����������ƥ�䣬���ж��м��ǲ��Ǳ��ʽ�����ó����ʽ��ֵ���з���
        lpnum++;
        flag=advance();
        if(conterr){
            return NULL;
		}
		if(flag==0){
			conterr++;
			cout<<"�﷨���� '('��ȱ�ٱ��ʽ"<<endl;
			return NULL;
		}
        arg=expressionAnalysis();
        if(conterr){
            return NULL;
		}
        if(flag==0||sym!="rparen"){
			conterr++;
			cout<<"�﷨���� ���ʽ����ȱ��')'"<<endl;
			return " ";
		}else{
		    lpnum--;
            flag=advance();
            if(conterr){
                return NULL;
            }
            if(flag==0){
                return arg;
            }
		}
    }else{
		cout<<"�﷨���� �����ײ���Ϊ<��ʶ��>|<�޷�������>|'('"<<endl;
		conterr++;
		return " ";
	}
	return arg;
}


int main(){
    int i=0,num,result;
    //��ʼ�ʷ�����
    map_init();
    lexanalysis();

    cout<<"PL/0�������ʽ���м�������ɽ����"<<endl<<endl;
    flag=advance();

    if(flag){
        expressionAnalysis();//��ʼ���б��ʽ����
    }
    if(flag!=-1&&!conterr){//�����ʽ��ȷ��������ʽ���м�����ʾ
        for(int i=0;i<count1;i++){
            cout<<'('<<quad[i].op<<','<<quad[i].arg1<<','<<quad[i].arg2<<','<<quad[i].result<<')'<<endl;;
        }
    }
    infile.close();
    return 0;
}
