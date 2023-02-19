#include <iostream>

using namespace std;

int find(int x, int arr[])
{
    int i = x-1;

    for(;;){
        if(arr[i] < 0){
            return i+1;
        }

        i = arr[i];
    }
}

void Union(int u, int v, int arr[])
{
    int up = find(u, arr);
    int vp = find(v, arr);

    if(up == vp){
        return;
    }

    if(arr[up-1] > arr[vp-1]){
        arr[up-1] = vp-1;
    }
    else if(arr[up-1] == arr[vp-1]){
        arr[up-1] = vp-1;
        arr[vp-1] -= 1;
    }
    else{
        arr[vp-1] = up-1;
    }
}

int main()
{
    int *set;

    int n, i, j, choice;

    cin >> n;

    set = new int[n];

    for(i = 0; i < n; i++){
        set[i] = -1*1;
    }

    while(1){
        cout << "1. Find\n2. Union\n\n";
        cin >> choice;
        if(choice == 1){
            cout << "Find: ";
            cin >> j;
            cout << find(j, set) << endl;
        }
        else if(choice == 2){
            cout << "Union: ";
            cin >> i >> j;
            Union(i, j, set);
            cout << endl;
        }
    }

    return 0;
}
