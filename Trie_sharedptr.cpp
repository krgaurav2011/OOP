#include <iostream>
#include <string>
#include <vector>
#include <memory>
#define SIZE 26

using namespace std;
class TrieNode {
public:
	shared_ptr<TrieNode> child[SIZE];
	bool isEndOfWord = false;
	TrieNode() = default;
}; 

class Trie
{
public:
	Trie() = default;
	~Trie() {}
	void insert(const string& s) {
		shared_ptr<TrieNode> curr = root;
		for (const auto& x : s) {
			auto& next = curr->child[x - 'a'];
			if (next == nullptr) {
				next = make_shared<TrieNode>();
			}
			curr = next;
		}
		curr->isEndOfWord = true;
	}
	bool search(const string& s) {
		shared_ptr<TrieNode> curr = root;
		for (const auto& x : s) {
			auto& next = curr->child[x - 'a'];
			if (next == nullptr) {
				return false;
			}
			curr = next;
		}
		return  curr && curr->isEndOfWord;
	}

private:
	shared_ptr<TrieNode> root = make_shared<TrieNode>();
};



int main() {
	Trie tr;
	vector<string> dict = { "hello","hell","new","news","gaurav","good","goodmorning","morning","mor","test","testmatch","game","end","gameend" };
	for (auto x : dict) {
		tr.insert(x);
	}


	for (auto x : dict) {
		cout << (tr.search(x) ? "Found" : "Notfound") << endl;
	}

	int t;
	cin>>t;
	while (t--) {
		cout << "-----------------------------------" << endl;
		string word;
		cin >> word;
		cout << (tr.search(word) ? "Found" : "Notfound") << endl;

	}

	system("pause");

}