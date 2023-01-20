#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
//struktura wezla
struct Node{
    Node *left;
    Node *right;
    char character;
    int value;
    Node(char c, int v, Node* l=nullptr, Node* r=nullptr){
        left = l;
        right = r;
        character = c;
        value = v;
    }
    ~Node(){
        delete right;
        delete left;
    }
    bool isLeaf(){ //sprawdza, czy liść zawieraja jakiś znak
        return character != '\0';
    }
};

//zliczanie
Node* createHuffmanTree(unordered_map<char, int>& value) {

    vector<Node *> nodes;

    for (auto &[character, f]: value) {
        nodes.push_back(new Node(character, f));
    }

    while (nodes.size() > 1) {
        int min1 = 0, min2 = 1; //szukamy 2 najmniejszych elementow
        if (nodes[min1]->value > nodes[min2]->value) {
            swap(min1, min2);
        }
        for (int i = 2; i < nodes.size(); i++) {
            if (nodes[i]->value < nodes[min1]->value) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->value < nodes[min2]->value) {
                min2 = i;
            }
        }

        //łączymy je w jeden
        Node *node = new Node('\0', nodes[min1]->value + nodes[min2]->value);
        node->left = nodes[min1];
        node->right = nodes[min2];
        nodes[min1] = node;
        nodes.erase(nodes.begin() + min2);
    }

    return nodes[0];
}

void generateHuffmanCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (root->character != '\0') {
        codes[root->character] = code;
    }
    generateHuffmanCodes(root->left, code + '0', codes);
    generateHuffmanCodes(root->right, code + '1', codes);
}

string decode(Node* root, string code) {
    string decoded = "";
    Node *currentNode = root; //zaczynamy na korzeniu
    for (char c: code) {
        if (c == '0') {
            if (currentNode->left->isLeaf()) {
                decoded += currentNode->left->character; //jesli lisc -> zapisujemy i wracamy
                currentNode = root;
            } else {
                currentNode = currentNode->left; //jesli kontener -> ustawiamy na niego wskaznik
            }
        } else {
            if (currentNode->right->isLeaf()) {
                decoded += currentNode->right->character; //jesli lisc -> zapisujemy i wracamy
                currentNode = root;
            } else {
                currentNode = currentNode->right; //jesli kontener -> ustawiamy na niego wskaznik
            }

        }
    }
    return decoded;
}


int main() {
    ifstream input("input.txt");
    if (!input) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    //tworzymy mape wartosci liczb
    unordered_map<char, int> value;
    char character;
    while (input.get(character)) {
        ++value[character];
    }

    //budowa drzewa
    Node* root = createHuffmanTree(value);

    //tworzenie mapy przechowujacej wartosci kazdej z liter
    unordered_map<char, string> codes;
    string code;
    generateHuffmanCodes(root, code, codes);
    ofstream output("output.bin");
    if (!output) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }


    //powrot do poczatku pliku input
    input.clear();
    input.seekg(0, ios::beg);
    string encoded;
    //tworzenie kodu huffmana
    while (input.get(character)) {
        encoded += codes[character];
    }
    output << encoded; //zapis do pliku output
    ofstream decoded("decoded.txt");
    decoded << decode(root, encoded); //zapis zdekodowanego wyniku
    decoded.close();

    input.close();
    output.close();
    return 0;
}

