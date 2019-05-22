#include<list>
#include<dirent.h>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<stack>
#include<sstream>
using namespace std;


vector<string> ParseFolder(string dirName)
{
    DIR* dir;
    dirent* ent;
    vector<string> output;
    dir=opendir(dirName.c_str());
    while(true)
    {
        ent=readdir(dir);
        if(ent==nullptr)
        {
            closedir(dir);
            return output;
        }
        if(ent->d_namlen>4)
            output.push_back(ent->d_name);

    }


}
void ChangeToLowerCase(string& word){

        for(int i=0; i<word.length(); i++)
        {
            if(word[i]<='Z' && word[i]>='A')word[i]+='a'-'A';
        }


}
struct WordStruct
{
    string word;
    list<int> IdxofDocuments;


};

void InsertInVector(std::vector<WordStruct>& v, string searching,int idxofFile)
{
    auto start=v.begin();
    auto endIt=v.end();
    auto mid=start+(endIt-start)/2;

    while( start<endIt)
    {
        if((*mid).word==searching)
        {
            if((*mid).IdxofDocuments.back()!=idxofFile)
            {
                (*mid).IdxofDocuments.push_back(idxofFile);
            }
            return;
        }

        else if ((*mid).word<searching)
        {
            start=mid+1;
        }
        else
        {
            endIt=mid;
        }
        mid=(endIt-start)/2+start;
    }
//its a new word
    WordStruct newWord;
    newWord.word=searching;
    newWord.IdxofDocuments.push_back(idxofFile);
    v.insert(start,newWord);
}

list<int> SimpleQueryList(vector<WordStruct>& all_words, string searching)
{
    auto start=all_words.begin();
    auto endIt=all_words.end();
    auto mid=start+(endIt-start)/2;
    while( start<endIt)
    {
        if((*mid).word==searching)
        {
            return (*mid).IdxofDocuments;
        }

        else if ((*mid).word<searching)
        {
            start=mid+1;
        }
        else
        {
            endIt=mid;
        }
        mid=(endIt-start)/2+start;
    }
    list<int>empty;
    return empty;
}


int getWeight(char c)
{
    switch(c)
    {
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 100;
    }
}

bool isOperation(char c)
{
    return c == '+' || c == '-' || c == '*' ;
}

bool isLetter(char c)
{
    return c >= 'a' && c <= 'z';
}
list<int> orr(list<int>& first,list<int>& second)
{
    first.merge(second);
    first.unique();
    return first;
}
list<int> andd(list<int>& first,list<int>& second)
{
    for(auto it=first.begin(); it!=first.end();)
    {
        if((*it)<second.front())first.pop_front();
        else if(*it==second.front())
        {
            second.pop_front();
            it++;
        }
        else second.pop_front();
    }
    return first;
}

list<int> difference(list<int>& first,list<int>&second)
{
    for(auto it=first.begin(); it!=first.end(); it++)
    {
        second.remove((*it));
    }
    return second;
}




list<int> evaluate(const std::string& input,vector<WordStruct>& all_words)
{
    list<int> list1, list2;
    char op;
    std::stack<char> st;
    std::istringstream expr(input);
    string word;
    std::stack<list<int>> rpn;

    while(!expr.eof())
    {
        char next = expr.peek();
        if (isOperation(next))
        {
            expr >> op;
            while(!st.empty() && st.top() != '(' && getWeight(st.top()) >= getWeight(op))
            {
                char op2 = st.top();
                list2 = rpn.top();
                rpn.pop();
                list1 = rpn.top();
                rpn.pop();
                switch(op2)
                {
                case '+':
                    rpn.push( orr(list1, list2));
                    break;
                case '*':
                    rpn.push( andd(list1,list2));
                    break;
                case '-':
                    rpn.push(difference(list1,list2));
                    break;

                }
                st.pop();
            }

            st.push(op);
        }
        else if (isLetter(next))
        {
            expr >> word;
            rpn.push(SimpleQueryList(all_words,word));
        }
        else if (next == '(')
        {
            expr.ignore();
            st.push('(');
        }
        else if (next == ')')
        {
            expr.ignore();
            while(st.top() != '(')
            {
                op = st.top();
                list2 = rpn.top();
                rpn.pop();
                list1 = rpn.top();
                rpn.pop();
                switch(op)
                {
                case '+':
                    rpn.push(orr(list1, list2));
                    break;
                case '*':
                    rpn.push(andd(list1,list2));
                    break;
                case '-':
                    rpn.push(difference(list1,list2));
                    break;

                }
                st.pop();
            }

            st.pop();
        }
        else
        {
            expr.ignore();
        }
    }
    while(!st.empty())
    {
        op = st.top();
        list2 = rpn.top();
        rpn.pop();
        list1 = rpn.top();
        rpn.pop();
        switch(op)
        {
        case '+':
            rpn.push(orr(list1, list2));
            break;
        case '*':
            rpn.push(andd(list1, list2));
            break;
        case '-':
            rpn.push(difference(list1, list2));
            break;

        }
        st.pop();
    }

    return rpn.top();

}




int main()
{
    string DirPath=".\\Data";
    vector<string> FileNames=ParseFolder(DirPath);
    fstream curFile;
    vector<WordStruct> all_words;
    string curWord;
    for(int i=0; i<FileNames.size(); i++) // going through the documents
    {
        curFile.open(DirPath +"\\"+FileNames[i]);
        curFile.seekg(0);
        curFile.seekp(0);

        while(!curFile.eof())
        {
            curFile>>curWord;
            ChangeToLowerCase(curWord);
            if(all_words.empty())
            {
                WordStruct newOne;
                newOne.word=curWord;
                newOne.IdxofDocuments.push_back(i);
                all_words.push_back(newOne);
            }
            else
            {
                InsertInVector(all_words,curWord,i);
            }
        }
        curFile.close();
    }
    string input;
    while( getline(cin,input))
    { //modify querys to be lowerCase
        list<int> output=evaluate(input,all_words);
        for(auto it=output.begin(); it!=output.end(); it++)
        {
            cout<<*it<<" ";
        }
        if(output.empty())cout<<"Word/s not found";
        cout<<endl;
    }
    return 0;
}
