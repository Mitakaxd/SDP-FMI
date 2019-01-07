#include<iomanip>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
struct Node
{
    int WordCount;
    Node* letters[26];
    Node(int WordCount_=0): WordCount(WordCount_)
    {
        for(int i=0; i<26; i++)letters[i]=nullptr;
    }
};




class Trie
{

private:
    void findAllwordsFromNode(Node* mynode, vector<string>& v, string curWord)
    {

        if (mynode->WordCount > 0)  v.push_back(curWord);
        for (int i = 0; i < 26; i++)
        {


            if (mynode->letters[i]!=nullptr)findAllwordsFromNode(mynode->letters[i], v, curWord + (char)(i + 'a'));
        }
    }

    Node* root;
    void copyAutomate(Node*& rootone, Node* roottwo)
    {

        rootone=new Node(roottwo->WordCount);
        for(int i=0; i<26; i++)
        {
            if(roottwo->letters[i])
            {
                copyAutomate(rootone->letters[i], roottwo->letters[i]);
            }
        }

    }
    void delAutomate(Node*& root)
    {
        for(int i=0; i<26; i++)
        {
            if(root->letters[i])delAutomate(root->letters[i]);
        }
        delete root;
        root=nullptr;
    }



public:

    Trie()
    {
        root = new Node(0);

    }
    Trie(Trie const& other)
    {
        copyAutomate(root,other.root);
    }
    Trie& operator=(Trie const& other)
    {
        if(this!=&other)
        {
            delAutomate(root);
            copyAutomate(this->root,other.root);
        }
        return *this;
    }
    ~Trie()
    {
        delAutomate(root);
    }

    void addWord(const string& word)
    {
        string curWord = word;
        Node* curNode = root;
        for (int i = 0; i < curWord.length(); i++)
        {

            int idxofSymbol = curWord[i] - 'a';

            if (curNode->letters[idxofSymbol]==nullptr) curNode->letters[idxofSymbol] = new Node(0);



            curNode = curNode->letters[idxofSymbol];

            if (i == curWord.length() - 1)
            {
                curNode->WordCount++;
            }
        }


    }


    std::vector<string> getSuggestions(const string& beginning)
    {
        vector<string> output;
        Node* curNode = root;
        for (int i = 0; i < beginning.length(); i++)
        {
            curNode = curNode->letters[beginning[i] - 'a'];
            if(!curNode)return output;//no words with that prefix
        }

        findAllwordsFromNode(curNode, output, beginning); //using a recursive function to fill vector with words

        //sortby Getvalue
        for(int i=0; i<output.size(); i++)
        {
            for(int j=i; j<output.size(); j++)
            {
                if(getValue(output[i])<getValue(output[j]))
                {
                    string temp=output[i];
                    output[i]=output[j];
                    output[j]=temp;
                }
            }
        }
        return output;

    };
    bool find(const std::string& word)
    {
        Node* curNode = root;
        for (int i = 0; i < word.length(); i++)
        {
            int idxofSymbol = word[i] - 'a';
            if (!curNode)return false;
            curNode = curNode->letters[idxofSymbol];
        }
        return curNode->WordCount != 0;
    }

    bool remove(const string & word)
    {
        if (find(word))//check if word is in tree
        {

            Node* curNode = root;
            int idxofSymbol;

            for (int i = 0; i < word.length(); i++)
            {
                idxofSymbol = word[i] - 'a'; //finding which route we should take
                curNode = curNode->letters[idxofSymbol]; //iterating
            }
            curNode->WordCount=0; //the removal itself
            //not removing nodes cause they could be used for other words
            // checking if they are in use will slow us a lot
            return true;
        }
        return false;
    }
    int getValue(const string& word) const
    {
        Node* curNode = root;
        for (int i = 0; i < word.length(); i++)
        {
            int idxofSymbol = word[i] - 'a';
            if(!curNode->letters[idxofSymbol])return 0;
            curNode = curNode->letters[idxofSymbol];
        }
        return curNode->WordCount;
    }
    void initializewithFile(fstream& file)
    {


        string word;
        while(!file.eof())
        {
            file>>word;

            addWord(word);
        }
    }
};





int main()
{
    Trie Text;
    //fstream file("Test.txt");
    string word;
    cout<<"Type text, only lower case letters, 0 to stop"<<endl;
    cin>>word;
    while(word!="0")
    {
        Text.addWord(word);
        cin>>word;
    }
    //  Text.initializewithFile(file);
    vector<string>Words=Text.getSuggestions("");
    auto endofTop10=Words.end();
    if(Words.size()>10)endofTop10=Words.begin()+10;
    cout<<setw(20)<<"TOP 10 MOST USED WORDS"<<endl;
    for(auto it=Words.begin(); it!=endofTop10; it++)
    {
        cout<<"word : "<<*it<<"    times:  "<<Text.getValue(*it)<<endl;
    }


    return 0;
}

