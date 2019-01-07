#include<iomanip>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
struct Node {
	Node* parent;
	int WordCount;
	Node* letters[26];
	Node(int WordCount_,Node* parent_=nullptr): WordCount(WordCount_),parent(parent_) {}
};




class Trie {

	private: 
		void findAllwordsFromNode(Node* mynode, vector<string>& v, string curWord) {

if (mynode->WordCount > 0)  v.push_back(curWord);
				
		for (int i = 0; i < 26; i++) {
			if (mynode->letters[i])findAllwordsFromNode(mynode->letters[i], v, curWord + (char)(i + 'a'));

		}
		


	}
	Node* root;
	//fix parent stuff
void copyAutomate(Node*& rootone, Node* roottwo,Node* parent=nullptr){

rootone=new Node(roottwo->WordCount,parent);
for(int i=0;i<26;i++){if(roottwo->letters[i]) {copyAutomate(rootone->letters[i], roottwo->letters[i],rootone);}}

}
void delAutomate(Node*& root){
for(int i=0;i<26;i++){if(root->letters[i])delAutomate(root->letters[i]); delete root;root=nullptr;}
}


public:

	Trie() {root = new Node(0);}
	Trie(Trie const& other){copyAutomate(root,other.root);}
	Trie& operator=(Trie const& other){if(this!=&other){delAutomate(root);copyAutomate(this->root,other.root);}return *this;}
	~Trie(){delAutomate(root);}
//fix parent stuff
	void addWord(const string& word) {
		string curWord = word;
		Node* curNode = root;
		for (int i = 0; i < curWord.length(); i++)
		{	int idxofSymbol = curWord[i] - 'a';
		if (!curNode->letters[idxofSymbol]){curNode->letters[idxofSymbol] = new Node(0,curNode);}
		
			 curNode = curNode->letters[idxofSymbol];
			if (i == curWord.length() - 1){curNode->WordCount++;}
		}


	}


	std::vector<string> getSuggestions(const string& beginning) {
		vector<string> output;
		Node* curNode = root;
		for (int i = 0; i < beginning.length(); i++) {curNode = curNode->letters[beginning[i] - 'a'];}
		findAllwordsFromNode(curNode, output, beginning);
	//sortby Getvalue
	for(int i=0;i<output.size();i++){
		for(int j=i;j<output.size();j++){if(getValue(output[i])<getValue(output[j])) {string temp=output[i];
output[i]=output[j];
output[j]=temp;
		} }
		return output;
	}
	};
	bool find(const std::string& word) {
		Node* curNode = root;
		for (int i = 0; i < word.length(); i++) {
			int idxofSymbol = word[i] - 'a';
			if (!curNode)return false;
			curNode = curNode->letters[idxofSymbol];
		} return curNode->WordCount != 0;
	}

	bool remove(const string & word) {
		if (find(word)) {
			string CurWord = word; Node* curNode = root;
			int idxofSymbol;

			for (int i = 0; i < word.length(); i++) {
				 idxofSymbol = word[i] - 'a'; curNode = curNode->letters[idxofSymbol];
			} curNode->WordCount=0;
			
		return true;} return false;
	}
	int getValue(const string& word) const {
		Node* curNode = root;
		for (int i = 0; i < word.length(); i++) {
			int idxofSymbol = word[i] - 'a';
			curNode = curNode->letters[idxofSymbol];
		} return curNode->WordCount;
	}
	void initializewithFile(fstream& file){


		string word;
		while(!file.eof()){
			file>>word;
		    addWord(word); }
	}
};





int main()
{
Trie Text;
string word;
///while(word!="0"){
//cin>>word;
//Text.addWord(word);}
fstream file("EnglishDictionary.txt");

Text.initializewithFile(file);
vector<string>Words=Text.getSuggestions("a");
//Words.sort(Words.begin(),Words.end(),Trie::getValue);
for(auto it=Words.begin();it!=Words.end();it++){
cout<<*it<<Text.getValue(*it)<<endl;
}


return 0;
}

