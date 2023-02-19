#include <bits/stdc++.h>
#define NULL_VALUE -999999

using namespace std;

class Queue
{
    stack <int> s1, s2;

public:
    Queue()
    {

    }
    int get_size(){return s1.size() + s2.size();}
    int top()
    {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }

        return s2.top();

    }
    void push(int x)
    {
        s1.push(x);
    }
    void pop()
    {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }

        s2.pop();

    }
    bool is_empty()
    {
        return s1.empty() and s2.empty();
    }
    ~Queue()
    {

    }
};

int main()
{

    Queue q;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    cout << q.get_size() << endl << endl;

    while(!q.is_empty()){
        cout << q.top() << ' ';
        q.pop();
    }cout << endl << endl << q.get_size() << endl;
}

