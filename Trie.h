#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <vector>
#include "QString"
#include "QChar"
using namespace std;




class Trie
{
private:


    class Node
    {
    public:
        Node();
        Node(QChar c);
        Node* getChild(QChar c);
        int getChildIndex(Node* nodeChar);
        int index(QChar c);
        deque<Node*> children;
        QChar value;
        bool isWord;
        QString email;
        QString phoneNo;
        Node(QChar c, QString email, QString phoneNo);

    };


    Node* root;
    Node* find_string(string const& word);
    void displayhelper(Node* start, QString acc, ostream& out);
    void prefixHelper(Node* start, QString acc,vector<QString> &list);
    bool checkleaf(string const& word, int& leaf);
    void getList(Node* start, QString acc, vector<QString> &list);

public:
    Trie();

    void addContact(QString const& name, QString const& email, QString const& phoneNo);
    bool search(string const& name);
    bool empty();
    void erase(string const& name);
    void display(ostream& out);
    vector<QString> prefix(QString const& str);
    Node* getRoot();
    Node* GetDetails(QString const& name);
    vector<QString> list();

};
ostream& operator<< (ostream& out, Trie& aList);
