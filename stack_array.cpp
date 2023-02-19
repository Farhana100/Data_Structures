#include <bits/stdc++.h>
#define NULL_VALUE -999999

using namespace std;

class Stack
{
    int *ara;
    int si_ze, maxize;
    re_size()
    {
        int * temp;
        temp = new int[maxize];
        for(int i = 0; i < si_ze;i++){
            temp[i] = ara[i];
        }
        delete ara;
        ara = temp;
    }
public:
    Stack()
    {
        maxize = 10;
        ara = new int[maxize];
        si_ze = 0;
    }
    int get_size(){return si_ze;}
    int top(){if(is_empty())return NULL_VALUE;return ara[si_ze-1];}
    void push(int x)
    {
        if(si_ze == maxize){
            maxize +=10;
            re_size();
        }

        ara[si_ze] = x;
        si_ze++;
    }
    void pop()
    {
        if(is_empty())return;
        si_ze--;

        if(si_ze == maxize-10){
            maxize -=10;
            re_size();
        }
    }
    bool is_empty()
    {
        return si_ze == 0;
    }
    ~Stack()
    {
        delete ara;
    }
};

int main()
{

    Stack s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    cout << s.get_size() << endl << endl;

    while(!s.is_empty()){
        cout << s.top() << ' ';
        s.pop();
    }cout << endl << endl << s.get_size() << endl;
}

