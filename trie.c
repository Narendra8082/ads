#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Function to create a new trie node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = 0;
    return node;
}

// Function to insert a word into the trie
void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (!current->children[index]) {
            current->children[index] = createNode();
        }

        current = current->children[index];
    }

    current->isEndOfWord = 1;
}

// Function to search for a word in the trie
int search(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (!current->children[index]) {
            return 0; // Word not found
        }

        current = current->children[index];
    }

    return (current != NULL && current->isEndOfWord);
}

// Driver program
int main() {
    struct TrieNode* root = createNode();

    // Insert words into the trie
    insert(root, "apple");
    insert(root, "app");
    insert(root, "apricot");
    insert(root, "banana");

    // Search for words in the trie
    printf("Search for 'apple': %s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("Search for 'ap': %s\n", search(root, "ap") ? "Found" : "Not Found");
    printf("Search for 'apricot': %s\n", search(root, "apricot") ? "Found" : "Not Found");
    printf("Search for 'orange': %s\n", search(root, "orange") ? "Found" : "Not Found");

    return 0;
}
