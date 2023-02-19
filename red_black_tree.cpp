#include <bits/stdc++.h>
#define red 0
#define blk 1
#define NILL INT_MIN
//#define fin cin
//#define fout cout
using namespace std;

fstream fin, fout;

struct Node{
    int val;
    Node* parent;
    Node* left;
    Node* right;
    bool colour;
};

class RedBlckTree{
    Node* root;

    void Insert_fixup(Node* fix);
    void Delete_fixup(Node* fix);
    Node* left_rotate(Node* node);
    Node* right_rotate(Node* node);
    void sub_delete(Node* node); // deletes the entire subtree except node and replaces node->val to NILL
    Node* successor(Node* node);
    Node* predecessor(Node* node);
public:

    RedBlckTree()
    {
        root = new Node;
        root->val = NILL;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->colour = blk;
    }

    void print(Node* node = NULL);
    Node* Find(int x);
    void Insert(int x);
    void Delete(int x);
    ~RedBlckTree();

};

Node* RedBlckTree::Find(int x)
{
    Node* node;

    node = root;

    while(node->val != x){
        if(node->val == NILL)
            return NULL;
        if(x <= node->val){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }

    return node;
}

Node* RedBlckTree::left_rotate(Node* node)
{
    Node* temp_r = node->right;
    Node* temp_p = node->parent;

    node->right = temp_r->left;
    temp_r->left->parent = node;

    temp_r->left = node;
    node->parent = temp_r;

    temp_r->parent = temp_p;
    if(temp_p){
        if(temp_p->val < node->val){
            temp_p->right = temp_r;
        }
        else{
            temp_p->left = temp_r;
        }
    }
    else{
        root = temp_r;
    }

    return temp_r;
}

Node* RedBlckTree::right_rotate(Node* node)
{
    Node* temp_l = node->left;
    Node* temp_p = node->parent;

    node->left = temp_l->right;
    temp_l->right->parent = node;

    temp_l->right = node;
    node->parent = temp_l;

    temp_l->parent = temp_p;
    if(temp_p){
        if(temp_p->val < node->val){
            temp_p->right = temp_l;
        }
        else{
            temp_p->left = temp_l;
        }
    }
    else{
        root = temp_l;
    }

    return temp_l;
}

void RedBlckTree::Insert_fixup(Node* fix)
{
    Node* Uncle;

    if(fix->parent->val > fix->parent->parent->val){
        Uncle = fix->parent->parent->left;
    }
    else{
        Uncle = fix->parent->parent->right;
    }

    /// case4 : uncle black
    if(Uncle->colour == blk){

        if(fix->parent->val <= fix->parent->parent->val){
            if(fix->val > fix->parent->val){
                fix = left_rotate(fix->parent)->left;
            }

            fix = right_rotate(fix->parent->parent);

            fix->colour = blk;
            fix->right->colour = red;
            return;

        }

        if(fix->val <= fix->parent->val){
            fix = right_rotate(fix->parent)->right;
        }

        fix = left_rotate(fix->parent->parent);

        fix->colour = blk;
        fix->left->colour = red;
        return;
    }

    /// case5 : uncle red
    // recolor
    fix->parent->colour = blk;
    Uncle->colour = blk;

    /// case6 : uncle red and grandparent root
    if(!(Uncle->parent->parent)){
        return;
    }

    /// case7 : uncle red and grandparent not root
    // recolor
    Uncle->parent->colour = red;
    // recheck
    if(Uncle->parent->parent->colour == blk ){
        return;
    }

    /// case8 : fix up again
    Insert_fixup(Uncle->parent);

}

void RedBlckTree::Insert(int x)
{
    Node *node;

    node = root;

    while(node->val != NILL){
        if(x <= node->val){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }

    node->val = x;

    node->left = new Node;
    node->left->val = NILL;
    node->left->parent = node;
    node->left->left = NULL;
    node->left->right = NULL;
    node->left->colour = blk;

    node->right = new Node;
    node->right->val = NILL;
    node->right->parent = node;
    node->right->left = NULL;
    node->right->right = NULL;
    node->right->colour = blk;

    /// case1 : empty tree
    if(!(node->parent)){
        return;
    }
    /// case2 : not empty parent black
    node->colour = red;
    if(node->parent->colour == blk ){
        return;
    }

    /// case3 : parent red
    Insert_fixup(node);

}

void RedBlckTree::print(Node* node)
{
    if(!node){
        node = root;
    }
    if(node->val == NILL){
        return;
    }


    if(node->left->val == NILL and node->right->val == NILL){
        fout << node->val << ':' << ((node->colour == blk)?'b':'r');
        return;
    }

    fout << node->val << ':' << ((node->colour == blk)?'b':'r') << '(';
    print(node->left);
    fout << ")(";
    print(node->right);
    fout << ')';
}

void RedBlckTree::sub_delete(Node* node)
{
    if(node->val != NILL){
        sub_delete(node->left);
        node->left->parent = NULL;
        delete node->left;
        node->left = NULL;

        sub_delete(node->right);
        node->right->parent = NULL;
        delete node->right;
        node->right = NULL;

        node->val = NILL;
        node->colour = blk;
    }
}

Node* RedBlckTree::successor(Node* node)
{
    Node* temp = node->right;

    if(temp->val == NILL)
    {
        return NULL;
    }

    while(temp->left->val != NILL)
    {
        temp = temp->left;
    }

    return temp;
}

Node* RedBlckTree::predecessor(Node* node)
{
    Node* temp = node->left;

    if(temp->val == NILL)
    {
        return NULL;
    }

    while(temp->right->val != NILL)
    {
        temp = temp->right;
    }

    return temp;
}

void RedBlckTree::Delete(int x)
{
    Node* node = Find(x);
    Node* succ;
    Node* pred;

    if(!node)return;
    succ = successor(node);
    pred = predecessor(node);
    while(succ || pred){
        if(succ){
            node->val = succ->val;  // replace
            node = succ;
        }
        else{
            node->val = pred->val;
            node = pred;
        }
        succ = successor(node);
        pred = predecessor(node);
    }

    /// now delete node

    /// case1 : delete root
    if(node == root){
        sub_delete(root);
        return;
    }

    /// case2 : node color red
    if(node->colour == red){
        sub_delete(node);
        return;
    }

    /// double black
    sub_delete(node);   // node is now a double black
    Delete_fixup(node);
}

void RedBlckTree::Delete_fixup(Node* node)
{

    /// case1 : DB is root
    if(node == root){
        return;
    }
    bool is_left = 1;

    if(node == node->parent->right)is_left = 0;

    Node* sibling;
    if(is_left){
        sibling = node->parent->right;
    }
    else{
        sibling = node->parent->left;
    }
    if(sibling->colour == blk){
        /// case2 : sibling black, sibling's children are also black
        if(sibling->left->colour == blk and sibling->right->colour == blk){

            sibling->colour = red;

            if(node->parent->colour == red){
                node->parent->colour = blk;
                return;
            }
            else{
                node = node->parent;
                Delete_fixup(node);
                return;
            }
        }
        if(is_left){

                /// case4 : sibling black, sibling's far child black
            if(sibling->right->colour == blk){
                swap(sibling->colour, sibling->left->colour);
                right_rotate(sibling);
                Delete_fixup(node);
                return;

            }   ///case5 : sibling's far child red
            else{
                swap(node->parent->colour, sibling->colour);
                left_rotate(node->parent);
                sibling->right->colour = blk;
                return;
            }
        }
        else{

                /// case4 : sibling black, sibling's far child black
            if(sibling->left->colour == blk){
                swap(sibling->colour, sibling->right->colour);
                left_rotate(sibling);
                Delete_fixup(node);
                return;

            }   ///case5 : sibling's far child red
            else{
                swap(node->parent->colour, sibling->colour);
                right_rotate(node->parent);
                sibling->left->colour = blk;
                return;
            }
        }
    }
    /// case3 : sibling red
    if(sibling->colour == red)
    {
        swap(sibling->colour, node->parent->colour);
        if(is_left){
            left_rotate(node->parent);
        }
        else{
            right_rotate(node->parent);
        }
        Delete_fixup(node);
        return;
    }
}

RedBlckTree::~RedBlckTree()
{
    sub_delete(root);
    delete root;
}


int main()
{
    fin.open("input.txt");
    fout.open("output.txt");

    RedBlckTree rbt;

    char ch;
    int x;

    while(fin >> ch >> x){
        switch(ch)
        {
        case 'F':
            {
                fout << ((rbt.Find(x))?"True":"False") << endl;
                break;
            }
        case 'I':
            {
                rbt.Insert(x);
                rbt.print();
                fout << endl;
                break;
            }
        case 'D':
            {
                rbt.Delete(x);
                rbt.print();
                fout << endl;
            }
        }
    }
}

