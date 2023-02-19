#include <bits/stdc++.h>
#define NULL_VALUE -999999

using namespace std;

class Queue
{
    int *ara;
    int p1, p2, maxize;
    re_size()
    {
        int * temp;
        temp = new int[maxize];
        for(int i = p1; i < p2;i++){
            temp[i-p1] = ara[i];
        }
        delete ara;
        ara = temp;
        p2 -= p1;
        p1 = 0;
    }
public:
    Queue()
    {
        maxize = 10;
        ara = new int[maxize];
        p1 = p2 = 0;
    }
    int get_size(){return p2-p1;}
    int top(){if(is_empty())return NULL_VALUE;return ara[p1];}
    void push(int x)
    {
        if(p2 == maxize){
            maxize +=10;
            re_size();
        }

        ara[p2] = x;
        p2++;
    }
    void pop()
    {
        if(is_empty())return;
        p1++;

        if(p1 == 10){
            maxize -=10;
            re_size();
        }
    }
    bool is_empty()
    {
        return p2-p1 == 0;
    }
    ~Queue()
    {
        delete ara;
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

