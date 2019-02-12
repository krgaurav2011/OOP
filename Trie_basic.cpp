#include <iostream>
#include <vector>
#include <string>
#define SIZE 26
using namespace std;

struct TrieNode {
	TrieNode* child[SIZE] = {};
	bool isEndofWord = false;
};

class Trie {
	TrieNode* root = new TrieNode;
	bool deleteWordHelper(TrieNode*, const string&, int);
	bool isLeafNode(TrieNode*);
	
public:
	void deleteTrie(TrieNode*);
	void insert(const string&);
	bool search(const string&) const;
	void deleteWord(const string&);
	
	Trie() {};
	//Disable copy and assignment operator
	Trie(const Trie&) =delete;   
	Trie& operator=(const Trie&) = delete;
	~Trie(){
		cout << "DESTRUCTOR called" << endl;
		if (root) deleteTrie(root);
		system("pause");
	}
};

void Trie::deleteTrie(TrieNode* node) {
	if (!node) return;
	for (int i = 0; i < SIZE; i++) {
		cout << "deleting i = " << i << endl;
		deleteTrie(node->child[i]);
	}
	delete node;
	node = nullptr;
}

void Trie::insert(const string& s) {
	TrieNode* curr = root;
	if (curr == nullptr) { cout << "null hai " << endl;
	return;
	}
	for (auto x : s) {
		if (curr->child[x - 'a'] == nullptr) {
			curr->child[x - 'a'] = new TrieNode;
		}
		curr = curr->child[x - 'a'];

	}
	curr->isEndofWord = true;
}

bool Trie::search(const string& s) const {
	TrieNode* curr = root;
	if (curr == nullptr) return false;
	for (auto x : s) {
		if (curr->child[x - 'a'] == nullptr) {
			return false;
		}
		curr = curr->child[x - 'a'];
	}
	return curr->isEndofWord;

}

bool Trie::isLeafNode(TrieNode* node) {
	for (int i = 0; i < SIZE; i++) {
		if (node->child[i]) return false;
	}
	return true;
}

bool Trie::deleteWordHelper(TrieNode* curr, const string& s, int level) {
	if (!curr) return false;
	if (s.size() == level) {
		if (!curr->isEndofWord) return false;
		curr->isEndofWord = false;
		return isLeafNode(curr);
	}
	int index = s[level] - 'a';
	bool shouldDelete = deleteWordHelper(curr->child[index], s, level + 1) ;
	if (shouldDelete) {
		delete curr->child[index];
		curr->child[index] = nullptr;
		return isLeafNode(curr) && !curr->isEndofWord;
	}
}

void Trie::deleteWord(const string& s) {
	if (!root) return;
	deleteWordHelper(root, s, 0);
}

int main() {
	vector<string> dict = { "goodmor", "hello","hell","new","news","gaurav","goodmorning","morning","mor","test","testmatch","game","end","gameend" ,"fight","bye","name","good" };
	Trie tr;
	for (auto x : dict)
		tr.insert(x);

	for (auto x : dict) {
		cout << tr.search(x) << endl;
	}
	cout << "------deleteWord(goodmor) ---search(goodmorning)--------------------\n";
	tr.deleteWord("goodmor");
	cout << tr.search("goodmorning") << endl;

	cout << "------deleteWord(mor) ---search(morning)--------------------\n";
	tr.deleteWord("mor");
	cout << tr.search("morning") << endl;



	cout << "------deleteWord(goodmor) ---search(goodmor)--------------------\n";
	tr.deleteWord("goodmor");
	cout << tr.search("goodmor") << endl;

	cout << "------deleteWord(testmatch) ---search(test)--------------------\n";
	tr.deleteWord("testmatch");
	cout << tr.search("test") << endl;

	
	/*int size;
	cin >> size;
	vector<string> inp;
	while (size--) {
		string x;
		cin >> x;
		inp.push_back(x);
	}

	cout << "size of inp" << inp.size() << endl;
	for (auto x : inp) {
		cout << "for " << x << endl;
		Trie* curr = root;
		bool flag = true;
		for (auto c : x) {
			cout << "\t now c : " << c << endl;
			if (curr->child[c - 'a'] != nullptr)
				curr = curr->child[c - 'a'];
			else if(root->child[c - 'a'] != nullptr){
					curr = root->child[c-'a'];
			}
			else {
				flag = false;
				break;
			}
		}
		if (curr->isEndofWord && flag) {
			cout << x << " can be formed" << endl;
		}
		else {
			cout << x << " cannot be formed" << endl;
		}
	}*/

	system("pause");
}