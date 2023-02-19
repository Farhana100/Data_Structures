#include <bits/stdc++.h>
#define NULL_VALUE -999999
///A+B/C*(D+E)-F
using namespace std;

map <char , int> mp;

int main()
{
    mp['('] = 0;
    mp['+'] = 1;
    mp['-'] = 1;
    mp['*'] = 2;
    mp['/'] = 2;

    string infix;
    char *postfix;
    stack <char> st;

    cout << "Infix: ";
    cin >> infix;
    int j, i, n = infix.length();
    postfix = new char[n];

    for(i = j = 0; i < n; ){
        if(infix[i] >= 'A' and infix[i] <= 'Z'){
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else if(infix[i] == '+' or infix[i] == '-' or infix[i] == '*' or infix[i] == '/'){
            if(st.empty()){
                st.push(infix[i]);
                i++;
            }
            else if(mp[st.top()] < mp[infix[i]]){
                st.push(infix[i]);
                i++;
            }
            else {
                postfix[j] = st.top();
                j++;
                st.pop();
            }
        }
        else if(infix[i] == '('){
            st.push(infix[i]);
            i++;
        }
        else{
            while(st.top() != '('){
                postfix[j] = st.top();
                j++;
                st.pop();
            }
            st.pop();
            i++;
        }
    }

    while(!st.empty()){
        postfix[j] = st.top();
        j++;
        st.pop();
    }

    postfix[j] = 0;

    cout << "Postfix: " << postfix << endl;

}

