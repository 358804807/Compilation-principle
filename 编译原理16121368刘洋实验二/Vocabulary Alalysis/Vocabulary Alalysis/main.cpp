#include<bits/stdc++.h>

using namespace std;

class Analyzer
{
public:
    string text;
    string clas[29]= {"plus","minus","times","slash","oddsym","eql","neq","lss","leq","gtr","geq","lparen","rparen","comma",
                      "semicolon","period","becomes","beginsym","endsym","ifsym","thensym","whilesym","writesym","readsym",
                      "dosym","callsym","constsym","varsym","procsym"
                     };
    string val[29]= {"+","-","*","/","odd","=","#","<","<=",">",">=","(",")",",",";",".",":=","begin","end","if","then",
                     "while","write","read","do","call","const","var","procedure"
                    };
    map<string,string> mp;
    int idx;
    Analyzer(string _text);
    virtual ~Analyzer();
    string getNext();
    bool isNone(char ch);
    bool isNumber(string s);
    bool isIdent(string s);
    bool find(string s);

protected:

private:
};

int main()
{
    string text="";
    char ch;
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    while(scanf("%c",&ch)!=EOF)
    {
        text+=ch;
    }

    Analyzer analyzer(text);

    vector<string> words;
    vector<string> res;
    string word=analyzer.getNext();
    while(word!="")
    {
        words.push_back(word);
        if(analyzer.find(word))
        {
            res.push_back(analyzer.mp[word]);
        }
        else if(analyzer.isIdent(word))
        {
            res.push_back("ident");
        }
        else if(analyzer.isNumber(word))
        {
            res.push_back("number");
        }
        else
        {
            res.push_back("null");
        }
        word=analyzer.getNext();
    }

    for(int i=0; i<res.size(); i++)
    {
        cout<<"("<<setw(10)<<left<<res[i]<<","<<setw(10)<<right<<words[i]<<")"<<endl;
    }



    return 0;
}


Analyzer::Analyzer(string _text)
{
    //ctor
    text = _text;
    idx=0;
    for(int i=0; i<29; i++)
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
    }
    else if(text[idx]>='0'&&text[idx]<='9')
    {
        idx++;
        while(idx<text.length()&&text[idx]>='0'&&text[idx]<='9')
        {
            tmp+=text[idx++];
        }
    }
    else if(text[idx]=='<')
    {
        idx++;
        if(idx<text.length()&&text[idx]=='=')
        {
            tmp+=text[idx++];
        }
    }
    else if(text[idx]=='>')
    {
        idx++;
        if(idx<text.length()&&text[idx]=='=')
        {
            tmp+=text[idx++];
        }
    }
    else if(text[idx]==':')
    {
        idx++;
        if(idx<text.length()&&text[idx]=='=')
        {
            tmp+=text[idx++];
        }
    }
    else
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

bool Analyzer::isIdent(string s)
{
    if(s==""||!(s[0]>='a'&&s[0]<='z')) return false;
    for(int i=1; i<s.length(); i++)
    {
        if(!(s[i]>='a'&&s[i]<='z'||s[i]>='0'&&s[i]<='9')) return false;
    }
    return true;
}

bool Analyzer::isNumber(string s)
{
    if(s=="") return false;
    for(int i=0; i<s.length(); i++)
    {
        if(!(s[i]>='0'&&s[i]<='9')) return false;
    }
    return true;
}

bool Analyzer::find(string s)
{
    return mp.find(s)!=mp.end();
}

