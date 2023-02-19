#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define nln cout << '\n'
#define ll long long int
#define MAX 100000 //maximum number of edges
///11 11 6 8 19 4 10 5 17 43 49 31

using namespace std;

class node
{
public:
    int data;
    node* left;
    node* right;

    node()
    {
        data= 0;
        left = NULL;
        right = NULL;
    }
    node(int x)
    {
        data= x;
        left = NULL;
        right = NULL;
//        left = new node;
//        right = new node;
    }
    bool compare(int x)
    {
         return x < data;
    }
    ~node()
    {
        delete left;
        delete right;
    }
};

void insert_ele(node* &root, int data)
{
    if(root == NULL){
        root = new node(data);
    }
    else if(root->compare(data)){
        insert_ele(root->left, data);
    }
    else{
        insert_ele(root->right, data);
    }
}

void delete_ele(node* &root, int data)
{
    ///find
    node* temp = root;
    node* pretemp = NULL;

    while(temp->data != data and temp != NULL){
        if(data < temp->data){
            pretemp = temp;
            temp = temp->left;
        }
        else if(data > temp->data){
            pretemp = temp;
            temp = temp->right;
        }
    }

    if(temp == NULL) return;

    int x;

    if(temp->left == NULL and temp->right == NULL){
        ///leaf
        pretemp = NULL;
        delete temp;
    }
    else if(temp->left == NULL){
        ///x = inorder successor

        while(temp->left == NULL){
            pretemp = temp;
            temp = temp->right;
        }
        while(temp->left != NULL){
            pretemp = temp;
            temp = temp->left;
        }


    }
}


void preorder(node* &root)
{
    if(root == NULL){
        return;
    }

    cout << root->data << ' ';

    preorder(root->left);
    preorder(root->right);

}

void postorder(node* &root)
{
    if(root == NULL){
        return;
    }

    postorder(root->left);
    postorder(root->right);

    cout << root->data << ' ';

}

void inorder(node* &root)
{
    if(root == NULL){
        return;
    }

    inorder(root->left);

    cout << root->data << ' ';

    inorder(root->right);

}

int main()
{
    node* root;

    root = NULL;

    int n, a, i;
    cin >> n;
    for(i = 0 ; i < n; i++)
    {
        cin >> a;
        insert_ele(root, a);
    }

    cout << "Inorder: "; inorder(root); cout << endl << endl;
    cout << "Preorder: "; preorder(root); cout << endl << endl;
    cout << "Postorder: "; postorder(root); cout << endl << endl;

}

