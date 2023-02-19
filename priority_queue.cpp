#include <iostream>

using namespace std;

class PriorityQueue{
    int maxsize;
    int *heap;
public:
    PriorityQueue();
    void Insert(int num);
    int FindMax();
    int ExtractMax();
    bool isEmpty()
    {
        if(heap[0]){
            return false;
        }
        else
            return true;
    }
    void IncreaseKey(int indx, int newKey);
    void DecreaseKey(int indx, int newKey);
    void Print();
    ~PriorityQueue();
};

PriorityQueue::PriorityQueue()
{
    maxsize = 10;
    heap = new int[maxsize+1];
    heap[0] = 0;
}

void PriorityQueue::Insert(int num)
{
    heap[0]++;

    if(heap[0] >= maxsize){
        cout << "increase size" << endl;
        maxsize += 10;
        int *temp = new int[maxsize+1];

        for(int i = 0; i <= maxsize-10; i++){
            temp[i] = heap[i];
        }
        delete[] heap;

        heap = temp;

    }

    heap[heap[0]] = num;

    int i = heap[0];

    for(; i > 1;i /= 2){
        if(heap[i] > heap[i/2]){
            //swap
            heap[i] += heap[i/2];
            heap[i/2] = heap[i] - heap[i/2];
            heap[i] = heap[i] - heap[i/2];
        }
        else return;
    }
}

void PriorityQueue::Print()
{
    if(heap[0]){
        for(int i = 1; i <= heap[0]; i++){
            cout << heap[i] << ' ';
        }
        cout << endl;
    }
    else
        cout << "heap is empty\n";
}

int PriorityQueue::FindMax()
{
    if(heap[0]){
        return heap[1];
    }
    else
        cout << "heap is empty\n";
        return -999999;
}

int PriorityQueue::ExtractMax()
{
    int max = -999999;

    if(heap[0]){
        max = heap[1];
        heap[1] = heap[heap[0]];
        ///decrement of heap size
        heap[0]--;

        ///go_down
        int i;

        for(i = 1; i < heap[0];){
            ///no child
            if(i*2 > heap[0]){
                break;
            }
            ///one child
            else if(i*2 == heap[0]){

                if(heap[i] < heap[i*2]){
                    ///swap

                    heap[i] += heap[i*2];
                    heap[i*2] = heap[i] - heap[i*2];
                    heap[i] = heap[i] - heap[i*2];
                    i = i*2;
                }
                else break;
            }
            ///both children
            else if(heap[i*2] > heap[i*2+1]){

                if(heap[i] < heap[i*2]){
                    ///swap
                    heap[i] += heap[i*2];
                    heap[i*2] = heap[i] - heap[i*2];
                    heap[i] = heap[i] - heap[i*2];
                    i = i*2;
                }
                else break;
            }
            else{
                if(heap[i] < heap[i*2+1]){
                    ///swap
                    heap[i] += heap[i*2+1];
                    heap[i*2+1] = heap[i] - heap[i*2+1];
                    heap[i] = heap[i] - heap[i*2+1];
                    i = i*2 +1;
                }
                else break;
            }
        }

        if(heap[0] == maxsize-10){
            maxsize -= 10;
            int *temp = new int[maxsize+1];
            for(int i = 0; i <= maxsize; i++){
                temp[i] = heap[i];
            }
            delete[] heap;

            heap = temp;

        }
    }
    else
        cout << "heap is empty\n";

    return max;
}

void PriorityQueue::IncreaseKey(int indx, int newKey)
{
    if(heap[indx] >= newKey || indx > heap[0] ) return; //do nothing

    heap[indx] = newKey;
    int i = indx;

    for(; i > 1;i /= 2){
        if(heap[i] > heap[i/2]){
            //swap
            heap[i] += heap[i/2];
            heap[i/2] = heap[i] - heap[i/2];
            heap[i] = heap[i] - heap[i/2];
        }
        else return;
    }
}

void PriorityQueue::DecreaseKey(int indx, int newKey)
{
    if(heap[indx] <= newKey || indx > heap[0] ) return; //do nothing

    heap[indx] = newKey;
    int i;

    for(i = indx; i < heap[0];){
        ///no child
        if(i*2 > heap[0]){
            return;
        }
        ///one child
        else if(i*2 == heap[0]){

            if(heap[i] < heap[i*2]){
                ///swap

                heap[i] += heap[i*2];
                heap[i*2] = heap[i] - heap[i*2];
                heap[i] = heap[i] - heap[i*2];
                i = i*2;
            }
            else return;
        }
        ///both children
        else if(heap[i*2] > heap[i*2+1]){

            if(heap[i] < heap[i*2]){
                ///swap
                heap[i] += heap[i*2];
                heap[i*2] = heap[i] - heap[i*2];
                heap[i] = heap[i] - heap[i*2];
                i = i*2;
            }
            else return;
        }
        else{
            if(heap[i] < heap[i*2+1]){
                ///swap
                heap[i] += heap[i*2+1];
                heap[i*2+1] = heap[i] - heap[i*2+1];
                heap[i] = heap[i] - heap[i*2+1];
                i = i*2 +1;
            }
            else return;
        }
    }
}

PriorityQueue::~PriorityQueue()
{
    maxsize = 0;
    delete [] heap;
}

int main()
{
    PriorityQueue pq;

    int choice;


    while(true){
        cout << "1 Insert\n2 Find Max\n3 Extract Max\n4 IncreaseKey\n5 DecreaseKey\n6 Print\n7 Quit\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            ///Insert
            int num;
            cin >> num;
            pq.Insert(num);
            break;
        case 2:
            ///Find Max
            cout << "Max element: " << pq.FindMax() << endl;
            break;
        case 3:
            ///Extract Max
            cout << "Max element: " << pq.ExtractMax() << endl;
            break;
        case 4:
        ///IncreaseKey
        {
            int indx, newKey;

            cout << "Increase at index: ";
            cin>> indx;
            cout << "New key: ";
            cin >> newKey;

            pq.IncreaseKey(indx, newKey);

            break;

        }

        case 5:
            ///DecreaseKey
        {
            int indx, newKey;

            cout << "Decrease at index: ";
            cin>> indx;
            cout << "New key: ";
            cin >> newKey;

            pq.DecreaseKey(indx, newKey);

            break;
        }

        case 6:
            ///Print
            pq.Print();
            break;
        case 7:
            return 0;

        }
    }


    return 0;
}
