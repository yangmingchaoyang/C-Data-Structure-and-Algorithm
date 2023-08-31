/*
介绍前缀树
何为前缀树? 如何生成前缀树?
例子: 一个字符串类型的数组arr1，另一个字符串类型的数组arr2。arr2中有哪些字符，是arr1中
出现的？请打印。arr2中有哪些字符，是作为arr1中某个字符串前缀出现的？请打印。arr2
中有哪些字符，是作为arr1中某个字符串前缀出现的？请打印 arr2中出现次数最大的前缀。
*/
#include <iostream>

const int MAX_SIZE = 26; // 字母表大小

class TrieNode {
public:
    int pass;
    int end;
    TrieNode* nexts[MAX_SIZE];

    TrieNode() {
        pass = 0;
        end = 0;
        for (int i = 0; i < MAX_SIZE; i++) {
            nexts[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        destroyTrie(root);
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        node->pass++;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->nexts[index] == nullptr) {
                node->nexts[index] = new TrieNode();
            }
            node = node->nexts[index];
            node->pass++;
        }
        node->end++;
    }

    int search(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->end;
    }

    int prefixNumber(const std::string& pre) {
        TrieNode* node = root;
        for (char ch : pre) {
            int index = ch - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->pass;
    }

    void deleteWord(const std::string& word) {
        if (search(word) != 0) {
            TrieNode* node = root;
            node->pass--;
            for (char ch : word) {
                int path = ch - 'a';
                if (--(node->nexts[path]->pass) == 0) {
                    deleteNode(node->nexts[path]);
                    node->nexts[path] = nullptr;
                    return;
                }
                node = node->nexts[path];
            }
            node->end--;
        }
    }

private:
    void deleteNode(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < MAX_SIZE; i++) {
            if (node->nexts[i] != nullptr) {
                deleteNode(node->nexts[i]);
            }
        }
        delete node;
        node=nullptr;
    }

    void destroyTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < MAX_SIZE; i++) {
            if (node->nexts[i] != nullptr) {
                destroyTrie(node->nexts[i]);
            }
        }
        delete node;
        node=nullptr;
    }
};

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("banana");
    trie.insert("application");

    std::cout << "Search 'apple': " << trie.search("apple") << std::endl;  // 1
    std::cout << "Search 'banana': " << trie.search("banana") << std::endl;  // 1
    std::cout << "Search 'application': " << trie.search("application") << std::endl;  // 1
    std::cout << "Search 'app': " << trie.search("app") << std::endl;  // 0
    std::cout << "Prefix number 'app': " << trie.prefixNumber("app") << std::endl;  // 2

    trie.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << trie.search("apple") << std::endl;  // 0

    return 0;
}
