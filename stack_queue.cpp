#include <bits/stdc++.h>
#define NULL_VALUE -999999

using namespace std;

class Stack
{
    queue <int> q1, q2;

public:
    Stack()
    {

    }
    int get_size(){return q1.size() + q2.size();}
    int top()
    {
        if(q1.empty()){
            while(q2.size() > 1){
                q1.push(q2.front());
                q2.pop();
            }

            int temp = q2.front();
            q1.push(q2.front());
            q2.pop();

            return temp;
        }
        else{
            while(q1.size() > 1){
                q2.push(q1.front());
                q1.pop();
            }

            return q1.front();
        }

    }
    void push(int x)
    {
        q1.push(x);
    }
    void pop()
    {
        if(q1.empty()){
            while(q2.size() > 1){
                q1.push(q2.front());
                q2.pop();
            }

            q2.pop();
        }
        else{
            while(q1.size() > 1){
                q2.push(q1.front());
                q1.pop();
            }

            q1.pop();
        }

    }
    bool is_empty()
    {
        return q1.empty() and q2.empty();
    }
    ~Stack()
    {

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

