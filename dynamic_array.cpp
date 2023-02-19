#include <iostream>
#define NULL_VALUE -999999

using namespace std;

template <class T>
class dynamic_array
{
    T *ara;
    int maxsize;
    int si_ze;
    void resize_array();
public:
    dynamic_array();
    T get_at(int index);
    int get_size();
    int f_ind(T x);
    bool ins_ert(T x, int index);
    void append(T x);
    bool rem_ove(int index);
    ~dynamic_array();


};

template <class T>
dynamic_array<T>::dynamic_array()
{
    maxsize = 10;
    ara = new T[maxsize];
    si_ze = 0;
}

template <class T>
void dynamic_array<T>::append(T x)
{
    if(si_ze == maxsize){
        maxsize -= 10;
        resize_array();
    }

    ara[si_ze] = x;
    si_ze++;
}

template <class T>
bool dynamic_array<T>::ins_ert(T x, int index)
{
    if(index < 0 || index >= si_ze) return false; ///insertion unsuccessful

    if(si_ze == maxsize){
        maxsize += 10;
        resize_array();
    }


    int n = si_ze;

    for(; n > index; n--){
        ara[n] = ara[n-1];
    }

    ara[n] = x;
    si_ze++;

    return true;
}

template <class T>
bool dynamic_array<T>::rem_ove(int index)
{
    if(index < 0 || index >= si_ze) return false; ///insertion unsuccessful


    int n = si_ze;

    for(; n-1 > index; index++){
        ara[index] = ara[index+1];
    }

    si_ze--;
    if(si_ze == maxsize-10)
    {
        maxsize -= 10;
        resize_array();
    }


    return true;
}

template <class T>
T dynamic_array<T>::get_at(int index)
{
    if(index < 0 || index >= si_ze) return NULL_VALUE;

    return ara[index];
}

template <class T>
int dynamic_array<T>::get_size()
{
    return si_ze;
}

template <class T>
int dynamic_array<T>::f_ind(T x)
{
    int i = 0;
    for(; i<si_ze; i++){
        if(ara[i] == x) return i;
    }
    return NULL_VALUE;
}

template <class T>
void dynamic_array<T>::resize_array()
{
    T  *new_arr = new T[maxsize];

    int i = 0;

    for(; i < si_ze; i++){
        new_arr[i] = ara[i];
    }
    delete ara;

    ara = new_arr;
}

template <class T>
dynamic_array<T>::~dynamic_array()
{
    delete ara;
}



int main()
{
    dynamic_array <int> a;

    a.append(0);
    a.append(1);
    a.append(2);
    a.append(3);
    a.append(4);

    cout << a.ins_ert(100, 100) << endl;
    a.ins_ert(100, 2);

    cout << a.rem_ove(0) << endl;

    cout << a.f_ind(10) << ' ' << a.f_ind(100) << endl;

    for(int i = 0; i < a.get_size(); i++){
        cout << a.get_at(i) << ' ';
    }
    cout << endl;
}

