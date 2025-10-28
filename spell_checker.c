#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define WORD_MAX_LEN 100

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
};

struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    newNode->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    return newNode;
}

void insertWord(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;
    for (int i = 0; word[i]; i++) {
        if (!isalpha(word[i])) continue;
        int index = tolower(word[i]) - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

int searchWord(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;
    for (int i = 0; word[i]; i++) {
        if (!isalpha(word[i])) continue;
        int index = tolower(word[i]) - 'a';
        if (!current->children[index]) return 0;
        current = current->children[index];
    }
    return current && current->isEndOfWord;
}

void loadDictionary(struct TrieNode* root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("dictionary.txt not found!\n");
        return;
    }
    char word[WORD_MAX_LEN];
    while (fscanf(file, "%s", word) != EOF)
        insertWord(root, word);
    fclose(file);
}

int main() {
    struct TrieNode* root = createNode();
    loadDictionary(root, "dictionary.txt");

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!input || !output) {
        printf("Missing input.txt or output.txt\n");
        return 1;
    }

    char word[WORD_MAX_LEN];
    if (fscanf(input, "%s", word) == 1) {
        if (searchWord(root, word))
            fprintf(output, "✅ '%s' is spelled correctly!\n", word);
        else
            fprintf(output, "❌ '%s' not found in dictionary.\n", word);
    } else {
        fprintf(output, "No input found.\n");
    }

    fclose(input);
    fclose(output);
    printf("Spell check complete.\n");
    return 0;
}
