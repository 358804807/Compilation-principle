#include<bits/stdc++.h>
#include"Analyzer.h"

using namespace std;

void go(Analyzer &analyzer)
{

    analyzer.str=analyzer.getSym();

    if(analyzer.isProgram()&&analyzer.now==analyzer.res.size()&&analyzer.isLegalName())
    {
        cout<<endl<<"YES"<<endl;
    }else
    {
        cout<<endl<<"NO"<<endl;
    }
}
int main()
{
    string text="";
    char ch;
    freopen("case05.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    while(scanf("%c",&ch)!=EOF)
    {
        text+=ch;
    }

    Analyzer analyzer(text);

    vector<string> &words=analyzer.words;
    vector<string> &res=analyzer.res;
    string word=analyzer.getNext();
    while(word!="")
    {
        words.push_back(word);
        if(analyzer.find(word))
        {
            res.push_back(analyzer.mp[word]);
        }else if(analyzer.isIdent(word))
        {
            res.push_back("ident");
        }else if(analyzer.isNumber(word))
        {
            res.push_back("number");
        }else
        {
            res.push_back("null");
        }
        word=analyzer.getNext();
    }

    for(int i=0;i<res.size();i++)
    {
        cout<<"("<<setw(10)<<left<<res[i]<<","<<setw(10)<<right<<words[i]<<")"<<endl;
    }


    go(analyzer);

    return 0;
}


