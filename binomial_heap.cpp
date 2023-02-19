#include <bits/stdc++.h>
#define nullval INT_MIN
//#define fin cin
//#define fout cout

using namespace std;

fstream fin, fout;

/// Binomial Tree Class
class bin_tree
{
    int val;
    int height;
    bin_tree* parent;
    vector <bin_tree*> children;

public:
    bin_tree();
    bin_tree(int new_val);
    void set_val(int new_val);
    int get_val(){return val;};
    int get_height(){return height;};
    bin_tree* tree_union(bin_tree* tree2);
    void print();
    bool empty(){return (height == -1);};
    vector <bin_tree*> remove_root();
    ~bin_tree(){};
};

bin_tree::bin_tree()
{
    val = nullval;
    height = -1;
    parent = NULL;
}

bin_tree::bin_tree(int new_val)
{
    val = new_val;
    height = 0;
    parent = NULL;
}

void bin_tree::set_val(int new_val)
{
    val = new_val;
    height = 0;
    parent = NULL;
}


bin_tree* bin_tree::tree_union(bin_tree* tree2)
{
    if(empty()) return tree2;
    if(tree2->empty()) return this;

    if(this->val < tree2->val){
        tree2->parent = this;
        this->children.push_back(tree2);
        this->height++;

        return this;
    }

    this->parent = tree2;
    tree2->children.push_back(this);
    tree2->height++;

    return tree2;
}

vector <bin_tree*> bin_tree::remove_root()
{
    return this->children;
}

void bin_tree::print()
{
    fout << "Binomial Tree, B" << height << endl;

    queue < bin_tree* > q;
    int level = 0;
    fout << "Level " << level << " :";
    q.push(this);
    q.push(NULL);

    while(!q.empty()){
        if(!q.front()){
            /// new level
            q.pop();
            if(q.empty())break;
            level++;
            fout << "\nLevel " << level << " :";

            q.push(NULL);
            continue;
        }

        fout << ' ' << q.front()->val;

        for(int i = q.front()->children.size() -1; i >= 0; i--){
            q.push(q.front()->children[i]);
        }
        q.pop();
    }

    fout << endl;
}


/// Binomial Heap Class

class bin_heap
{
    vector <bin_tree*> trees;

public:
    bin_heap(){};
    void print();
    void Insert(int new_val);
    void heap_union(bin_heap* heap2);
    bin_tree* find_min();
    int extract_min();
    ~bin_heap(){};
};

bin_tree* bin_heap::find_min()
{
    if(trees.empty())return NULL;

    bin_tree* m = trees[0];
    for(auto tree: trees){
        if(m->get_val() > tree->get_val()){
            m = tree;
        }
    }

    return m;
}

void bin_heap::heap_union(bin_heap* heap2)
{
    int mask1, mask2;
    mask1 = mask2 = 0;

    vector <bin_tree*> h1 = trees;
    vector <bin_tree*> h2 = heap2->trees;

    for(int i = 0; i < h1.size(); i++){
        mask1 |= (1<<(h1[i]->get_height()));
    }
    for(int i = 0; i < h2.size(); i++){
        mask2 |= (1<<(h2[i]->get_height()));
    }

    bin_tree* carry;
    carry = NULL;

    vector <bin_tree*> *temp;

    temp = new vector <bin_tree*>;
    int i, j;
    i = j = 0;

    int mask = 1;

    int max_loop = ceil(log2(mask1+mask2))+1;

    while(max_loop--){
        if(!(mask1&mask) && !(mask2&mask)){
            /// both 0
            if(carry){
                /// not 0
                /// insert carry, set carry NULL

                temp->push_back(carry);
                carry = NULL;
            }
        }
        else if(!(mask1&mask) && (mask2&mask)){
            /// 0 1
            if(carry){
                /// add h2 to carry, clear h2

                carry = carry->tree_union(h2[j]);
                h2[j] = NULL;

                j++; /// move h2 forward
            }
            else {
                /// no carry
                /// insert h2, clear h2

                temp->push_back(h2[j]);
                h2[j] = NULL;

                j++; /// move h2 forward
            }
        }
        else if((mask1&mask) && !(mask2&mask)){
            /// 1 0
            if(carry){
                /// add h1 to carry, remove h1

                carry = carry->tree_union(h1[i]);
                h1[i] = NULL;

                i++; /// move h1 forward
            }
            else{
                /// insert h1
                temp->push_back(h1[i]);
                h1[i] = NULL;
                i++; /// move h1 forward
            }
        }
        else if((mask1&mask) && (mask2&mask)){
            /// both 1

            if(carry){
                /// add h2 to carry, insert h1
                carry = carry->tree_union(h2[j]);
                h2[j] = NULL;

                temp->push_back(h1[i]);
                h1[i] = NULL;

                i++; /// move h1 forward
                j++; /// move h2 forward
            }
            else{
                /// add h1 and h2 and keep in carry
                /// clear h1 and h2
                /// remove h1

                carry = h1[i]->tree_union(h2[j]);

                h1[i] = NULL;
                h2[j] = NULL;

                i++;
                j++;
            }
        }

        mask <<= 1;
    }

    this->trees = *temp;

}

void bin_heap::Insert(int new_val)
{
    if(trees.empty()){
        bin_tree* new_tree;
        new_tree = new bin_tree(new_val);
        trees.push_back(new_tree);

        return;
    }

    bin_heap new_heap;
    new_heap.Insert(new_val);

    this->heap_union(&new_heap);
}

int bin_heap::extract_min()
{
    if(trees.empty()) return nullval;

    bin_tree* mini = find_min();

    int i;
    for(i = 0; i < trees.size(); i++){
        if(trees[i] == mini)break;
    }

    for(i++ ; i < trees.size(); i++){
        trees[i-1] = trees[i];
    }
    trees[i-1] = NULL;
    trees.pop_back();

    bin_heap new_heap;
    new_heap.trees = mini->remove_root();

    this->heap_union(&new_heap);

    return mini->get_val();
}

void bin_heap::print()
{
    fout << "Printing Binomial Heap..." << endl;

    for(int i = 0; i < trees.size(); i++){
        trees[i]->print();
    }
}

vector <int> convert(string s)
{
    istringstream istr(s);
    istream_iterator<string> it(istr), end;

    vector <string> ss(it, end);

    vector <int> vals;
    for(string val: ss){
        vals.push_back(stoi(val));
    }

    return vals;
}

int main()
{
    fin.open("input.txt");
    fout.open("output.txt", ios::out);

    bin_heap heap;
    char ch;

    while(fin >> ch){
        switch(ch)
        {
        case 'I':
            {
                int new_val;
                fin >> new_val;
                heap.Insert(new_val);
                break;
            }
        case 'P':
            {
                heap.print();
                break;
            }
        case 'F':
            {
                fout << "Find-Min returned " << heap.find_min()->get_val() << endl;
                break;
            }
        case 'E':
            {
                fout << "Extract-Min returned " << heap.extract_min() << endl;
                break;
            }
        case 'U':
            {
                bin_heap new_heap;

                string s;
                getline(fin, s);
                vector <int> vals = convert(s);

                for(auto val: vals){
                    new_heap.Insert(val);
                }

                heap.heap_union(&new_heap);
                break;
            }
        }
    }

}


