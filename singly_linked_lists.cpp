#include <iostream>
#define NULL_VALUE -999999

using namespace std;

template <class T>
class node
{
public:

    T data;
    node *next;

    node()
    {
        next = NULL;
    }
    ~node()
    {
        delete next;
    }
};

template <class T>
class linked_list
{
    node<T> *head, *tail, *newnode;
    int si_ze;

public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
        si_ze = 0;
    }

    T get_at(int index);
    int get_size();
    int f_ind(T x);
    bool ins_ert(T x, int index);
    void append(T x);
    bool rem_ove(int index);

    ~linked_list()
    {
        delete head;
        delete tail;
    }

};

template <class T>
T linked_list<T>::get_at(int index)
{
    if(index < 0 || index >= si_ze) return NULL_VALUE;

    newnode = head;

    while(index){
        newnode = newnode->next;
        index--;
    }

    return newnode->data;
}

template <class T>
int  linked_list<T>::get_size()
{
    return si_ze;
}

template <class T>
int linked_list<T>::f_ind(T x)
{
    newnode = head;
    int i = 0;

    while(newnode != NULL){
        if(newnode->data == x){
            return i;
        }
        i++;
        newnode = newnode->next;
    }

    return NULL_VALUE;
}

template <class T>
bool  linked_list<T>::ins_ert(T x, int index)
{
    if(index < 0 || index >= si_ze) return false;

    newnode = new node<T>;
    newnode->data = x;

    if(index == 0){
        newnode->next = head;
        head = newnode;
        si_ze++;
        return true;
    }

    int i = 1;
    node<T> *temp = head;

    for(; i < index; i++){
        temp = temp->next;
    }

    newnode->next = temp->next;
    temp->next = newnode;

    si_ze++;
    return true;
}


template <class T>
void  linked_list<T>::append(T x)
{
    newnode = new node <T>;
    newnode->data = x;

    if(si_ze == 0){
        head = newnode;
        tail = newnode;
    }
    else{
        tail->next = newnode;
        tail = newnode;
    }

    si_ze++;
}

template <class T>
bool  linked_list<T>::rem_ove(int index)
{
    if(index < 0 || index >= si_ze) return false;

    int i = 1;
    node <T> *temp = head;

    if(index == 0){
        head = head->next;
        delete temp;
        si_ze--;
        return true;
    }

    for(; i < index; i++){
        temp = temp->next;
    }

    newnode = temp->next;
    temp->next = temp->next->next;
    delete newnode;

    si_ze--;
    return true;
}

int main()
{
    linked_list<int> li;

    cout << li.get_size() << endl;
    li.append(1);
    li.append(2);
    li.append(3);
    li.append(4);
    li.append(5);

    li.ins_ert(100, 0);
    li.ins_ert(200, 3);
    li.ins_ert(300, 5);

    cout << li.get_size() << endl;

    cout << li.f_ind(200) << ' ' << li.f_ind(400) << endl;

    li.rem_ove(li.get_size()-1);
    li.rem_ove(0);

    for(int i = 0; i < li.get_size(); i++){
        cout << li.get_at(i) << ' ';
    }cout << endl;

    return 0;

}

