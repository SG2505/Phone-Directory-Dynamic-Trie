#include "Trie.h"
#include <deque>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "QString"
#include "QChar"


Trie::Trie()
{
    root = new Node();
}

Trie::Node::Node() :isWord(false) {}

Trie::Node::Node(QChar c) : value(c), isWord(false) {}

Trie::Node::Node(QChar c, QString email, QString phoneNo)
{
    this->value = c;
    this->email = email;
    this->phoneNo = phoneNo;
    this->isWord = true;
}

Trie::Node* Trie::Node::getChild(QChar c)
{

    for (int i = 0; i < children.size(); i++) {
        if (children[i]->value == c) {
            return children[i];
        }
    }

    return NULL;
}

int Trie::Node::getChildIndex(Node* nodeChar)
{
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == nodeChar)
            return i;
    }


    return -1;
}

int Trie::Node::index(QChar c)
{

    for (int i = 0; i < children.size(); i++) {

        if (children[i]->value > c)
            return i;

    }
    return -1;

}

void Trie::addContact(QString const& name, QString const& email, QString const& phoneNo)
{
    Node* curr = root;
    bool exist = true;
    int j;
    int i = 0;
    for (i; i < name.length(); i++)
    {
        if (curr->getChild(name[i]) == nullptr) {
            exist = false;
            break;
        }

        curr = curr->getChild(name[i]);
    }


    for (i; i < name.length() - 1; i++)
    {
        j = curr->index(name[i]);

        if ( j != -1) {
            curr->children.insert(curr->children.begin() + j, new Node(name[i]));
            curr = curr->children[j];
        }

        else {
            curr->children.push_back(new Node(name[i]));
            curr = curr->children.back();
        }

    }

    if (!exist)

        curr->children.push_back(new Node(name[i], email, phoneNo));
    else{
        curr->phoneNo=phoneNo;
        curr->email=email;
        curr->isWord=true;
    }



}

bool Trie::search(string const& name)
{
    Node* p = find_string(name);
    if (p) return (p->isWord);
    return false;
}

Trie::Node* Trie::find_string(string const& word)
{
    Node* curr = root;

    for (int i =0;i<word.size();i++){
        if ((curr = curr->getChild(word[i])) == nullptr)
            return nullptr;
    }
    return curr;
}

bool Trie::empty() {

    return root->children.empty();
}

void Trie::erase(string const& name) {

    Node* curr = root;
    Node* ptr;
    int leaf = -1;

    if (!search(name))
        return;

    if (checkleaf(name, leaf)) {
        if (leaf == -1) {
            curr = curr->getChild(name[0]);
            root->children.erase(root->children.begin() + root->getChildIndex(root->getChild(name[0])));
            for (int i = 0; i < name.length(); i++) {

                ptr = curr->getChild(name[i + 1]);
                delete curr;
                curr = ptr;

            }


        }
        else {

            for (int i = 0; i <= leaf; i++) {
                curr = curr->getChild(name[i]);
            }

            Node* nodeptr = curr;
            curr = curr->getChild(name[leaf + 1]);
            nodeptr->children.erase(nodeptr->children.begin() + nodeptr->getChildIndex(nodeptr->getChild(name[leaf + 1])));


            for (int i = leaf + 1; i < name.length(); i++) {
                ptr = curr->getChild(name[i + 1]);
                delete curr;
                curr = ptr;

            }
        }
    }
    else { // lw el name fe ba3deh 7roof tanya fa mogard ha5ly a5r node is word =false
        for (int i = 0; i < name.length(); i++) {
            curr = curr->getChild(name[i]);
        }
        curr->isWord = false;
        curr->email="";
        curr->phoneNo="";
    }

}


bool Trie::checkleaf(string const& word, int& leaf) {
    Node* curr = root->getChild(word[0]);

    for (int i = 0; i < word.length(); i++) {

        if ((curr->isWord) && (i == word.length() - 1) && (curr->children.size() <= 1))
            return curr->children.empty();// hatreurn true ya3ny mfesh b3dha ay nodes, el klma ma3molha store lwa7dha fe branch, y3ny hadelete kol el nodes

        else if ((curr->children.size() > 1))
            leaf = i;

        else if ((curr->isWord) && !(i == word.length() - 1))
            leaf = i;

        curr = curr->getChild(word[i + 1]);
    }
    return false;
}

Trie::Node* Trie::GetDetails(QString const& name)
{

    Node* curr = root;
    for (int i = 0; i < name.length(); i++) {
        curr = curr->getChild(name[i]);
    }

    if(curr==root)
        return nullptr;
    if(curr->isWord)
        return curr;
}


vector<QString> Trie::prefix(QString const& str)
{
    Node* curr = root;
    QString str2 = "";
    vector<QString> v1;

    for (int i = 0; i < str.length(); i++)
    {
        curr = curr->getChild(str[i]);
        if(curr==NULL)
            return v1;
        if (i >= 1)
            str2 += str[i - 1];
    }

    if(curr!=0)
        prefixHelper(curr, str2,v1);
    return v1;

}

void Trie::prefixHelper(Node* start, QString acc,vector<QString> &list)
{

    acc += (start->value);

    if (start->isWord)
        list.push_back(acc);


    if (start->children.empty())
        return;

    for (int i = 0; i < (start->children.size()); i++)
        prefixHelper(start->children[i], acc,list);

}

//void Trie::display(ostream& out)
//{
//    displayhelper(root, "", out);
//}

//void Trie::displayhelper(Node* start, QString acc, ostream& out)
//{



//    acc += (start->value);

//    if (start->isWord)
//        //out << acc << endl;
//        return;

//    if (start->children.empty())
//        return;

//    for (int i = 0; i < (start->children.size()); i++)
//        displayhelper(start->children[i], acc, out);

//}

//ostream& operator <<(ostream& out, Trie& alist) {
//    alist.display(out);
//    return out;
//}

vector<QString> Trie::list()
{

    vector<QString> v1;
    getList(root, "", v1);
    return v1;


}

void Trie:: getList (Node* start, QString acc, vector<QString> &list)
{

    if(start!=root)
        acc += (start->value);


    if (start->isWord)
        list.push_back(acc);

    if (start->children.empty())
        return;

    for (int i = 0; i < (start->children.size()); i++)
        getList(start->children[i], acc, list);

} //for list in gui

Trie::Node* Trie::getRoot()
{
    return root;
}

//void Trie::display(ostream& out)
//{
//    stack<Node*> nodes;
//    stack<string> strings;
//
//    nodes.push(root);
//    strings.push("");
//
//    while (!nodes.empty()) {
//        Node* curr = nodes.pop();
//        string currstr = string.pop();
//
//        if (curr->isWord)
//            out << currstr.append(1, curr->value);
//        for (int i = 0; i < curr->children.size(); i++) {
//            nodes.push(curr->children[i]);
//            strings.push()
//        }
//    }
//
//
//
//}


//void Trie::destructor(Node* start)
//{
//
//    //if (start->isWord)
//    //    out << acc << endl;
//
//    for (int i = 0; /*(start->children[i] != NULL) &&*/ (i < (start->children.size())); i++) {
//        destructor(start->children[i]);
//        if (start->children[i]->value == -35)
//            start->children.erase(start->children.begin() + i);
//        //delete index of children in the parent node
//    }
//
//
//
//
//    if (start->children.empty()) {
//        delete start;
//        start = NULL;
//    }
//
//}

//Trie::~Trie()
//{
//    destructor(root);
//}
