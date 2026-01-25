#include <iostream>
#include <vector>
#include <tuple>
#include <map>
using namespace std;


class Tree {
public:
    char content = 0;
    int count = 0;
    string code = "";
    Tree* children[3] = { nullptr, nullptr, nullptr };

    Tree(char con, int c) : content(con), count(c) {}
    Tree(Tree* f, Tree* s) {
        children[0] = f;
        children[1] = s;
        count = f->count + s->count;
    }
    Tree(Tree* f, Tree* s, Tree *t) {
        children[0] = f;
        children[1] = s;
        children[2] = t;
        count = f->count + s->count + t->count;
    }

    void Codify(map<char, string>& codes) {
        if (content != 0)
            codes[content] = code;
        if (children[0] != nullptr) {
            children[0]->code = code + "0";
            children[0]->Codify(codes);
        }
        if (children[1] != nullptr) {
            children[1]->code = code + "1";
            children[1]->Codify(codes);
        }
        if (children[2] != nullptr) {
            children[2]->code = code + "2";
            children[2]->Codify(codes);
        }
    }
    map<char, string> Codify() {
        map<char, string> codes;
        Codify(codes);
        return codes;
    }


};

tuple<Tree, string> Huffman2(string s) {
    map<char, int> counts;
    for (char c : s)
        counts[c]++;


    vector<Tree*> branches;
    for (auto [f, s] : counts)
        branches.push_back(new Tree(f, s));

    while (branches.size() > 1) {
        int lowest1 = 0, lowest2 = 1;
        if (branches[lowest2]->count > branches[lowest1]->count)
            swap(lowest2, lowest1);
        for (int n = 2; n < branches.size(); n++) {
            if (branches[lowest1]->count > branches[n]->count)
                lowest1 = n;
            if (branches[lowest2]->count > branches[lowest1]->count)
                swap(lowest2, lowest1);
        }
        if (lowest1 < lowest2) swap(lowest1, lowest2);
        Tree* next = new Tree(branches[lowest1], branches[lowest2]);
        branches.erase(branches.begin() + lowest1);
        branches.erase(branches.begin() + lowest2);
        branches.push_back(next);
    }

    map<char, string> codes;
    branches[0]->Codify(codes);

    string out = "";

    for (char c : s)
        out += codes[c];

    return make_tuple(*branches[0], out);
}

tuple<Tree, string> Huffman3(string s) {
    map<char, int> counts;
    for (char c : s)
        counts[c]++;

    vector<Tree*> branches;
    for (auto [f, s] : counts)
        branches.push_back(new Tree(f, s));

    if(branches.size() % 2 == 0) {
        int lowest1 = 0, lowest2 = 1;
        if (branches[lowest2]->count > branches[lowest1]->count)
            swap(lowest2, lowest1);
        for (int n = 2; n < branches.size(); n++) {
            if (branches[lowest1]->count > branches[n]->count)
                lowest1 = n;
            if (branches[lowest2]->count > branches[lowest1]->count)
                swap(lowest2, lowest1);
        }
        if (lowest1 < lowest2) swap(lowest1, lowest2);
        Tree* next = new Tree(branches[lowest1], branches[lowest2]);
        branches.erase(branches.begin() + lowest1);
        branches.erase(branches.begin() + lowest2);
        branches.push_back(next);
    }

    while (branches.size() > 2) {
        int lowest1 = 0, lowest2 = 1, lowest3 = 2;
        if (branches[lowest2]->count > branches[lowest1]->count)
            swap(lowest2, lowest1);
        if (branches[lowest3]->count > branches[lowest2]->count)
            swap(lowest3, lowest2);
        if (branches[lowest2]->count > branches[lowest1]->count)
            swap(lowest2, lowest1);

        for (int n = 3; n < branches.size(); n++) {
            if (branches[lowest1]->count > branches[n]->count)
                lowest1 = n;
            if (branches[lowest2]->count > branches[lowest1]->count) {
                swap(lowest2, lowest1);
                if (branches[lowest3]->count > branches[lowest2]->count)
                    swap(lowest3, lowest2);
            }
        }
        if (lowest1 < lowest2) swap(lowest1, lowest2);
        if (lowest2 < lowest3) swap(lowest2, lowest3);
        if (lowest1 < lowest2) swap(lowest1, lowest2);
        Tree* next = new Tree(branches[lowest1], branches[lowest2], branches[lowest3]);
        branches.erase(branches.begin() + lowest1);
        branches.erase(branches.begin() + lowest2);
        branches.erase(branches.begin() + lowest3);
        branches.push_back(next);
    }

    auto codes = branches[0]->Codify();

    string out = "";

    for (char c : s)
        out += codes[c];

    return make_tuple(*branches[0], out);
}

int main() {
    string s = "aaaaaaaaaaaaaaaabbbbccdddddddfffeee";
    auto [tree2, str2] = Huffman2(s);
    auto [tree3, str3] = Huffman3(s);

    for (auto [key, val] : tree2.Codify())
        cout << key << ":" << val << endl;
    cout << str2 << endl << endl;

    for (auto [key, val] : tree3.Codify())
        cout << key << ":" << val << endl;
    cout << str3;


    return 0;
}