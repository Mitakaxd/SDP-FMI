using namespace std;
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

struct Node{
	char letter;
	Node* next_letter[26];
	bool final;
	Node* parent;
	Node (char let='\0', bool finish=0, Node* par=nullptr): letter(let), final(finish), parent(par){
		for(int i=0; i<26; i++){
			next_letter[i]=nullptr;
		}
	}

	string get_word() {
		Node* temp=this;
		string word="";
		while(temp->parent!=nullptr){
			word=temp->letter+word;
			temp=temp->parent;
		}
		return word;
	}
};


class dictionary {
private:
	Node* root;

public:
	dictionary(){
		root=new Node;
	}

	void add_word(string word){
		Node* temp= root;
		for(int i=0;i<word.length();i++){
			if(!temp->next_letter[word[i]-'a']){
				temp->next_letter[word[i]-'a'] = new Node(word[i], 0, temp);
			}
			temp=temp->next_letter[word[i]-'a'];
		}
		temp->final=1;
	}

	void create_dictionary (fstream& in){
		
		while(!in.eof()){
			string word;
			in>>word;
			add_word(word);
		}
	}

	bool contains (string word) const {
		Node* temp=root;
		for(int i=0; i<word.length();i++){
			if(temp->next_letter[word[i]-'a']==nullptr) return 0;
			else {
				temp=temp->next_letter[word[i]-'a'];
			}
		}
		if(temp->final==1)return 1;
		return 0;
	}

	vector<string> auto_complete (string pref){
		Node* temp=root;
		vector<string> words;
		string adding=pref;
		for(int i=0;i<pref.length();i++){
			temp=temp->next_letter[pref[i]-'a'];

		}
		search(words, temp);

        return words;

	}

	void search(vector<string>& words, Node* cur){

		if(cur->final==1)words.push_back(cur->get_word());

		for(int i=0;i<26;i++){

			if(cur->next_letter[i]!=nullptr) {search(words, cur->next_letter[i]);}
        }	
	}



};


int main(){

	dictionary file;
	fstream in("EnglishDictionary.txt");
	file.create_dictionary(in);
	string curWord("ad");
	std::vector<string> v=file.auto_complete(curWord);
	for(string word:v)
		{cout<<word<<endl;}

	return 0;
}
