#include <bits/stdc++.h>
#define nullval LONG_MIN

using namespace std;

long long collisions;
long long probes;
long long no_place;

/// hash table size is m


/// ===================================>>>      hash functions starts    <<<================================

long long Hash1(string str, long long m)
{
    long long hash_val = 0;
    const int p = 31;

    reverse(str.begin(), str.end());

    for(auto ch: str){
        hash_val *= p;
        hash_val %= m;
        hash_val += ((long long)ch) % m;
        hash_val %= m;
    }

    return hash_val;
}

long long Hash2(string str, long long m)
{
    unsigned long long hash_val = 0;

    for(auto ch: str){
        hash_val += ch;
        hash_val += (hash_val << 10);
        hash_val ^= (hash_val >> 6);
    }
    hash_val += (hash_val << 3);
    hash_val ^= (hash_val >> 11);
    hash_val += (hash_val << 15);

    hash_val %= m;

    return hash_val;
}

long long auxHash__(string str, long long m)
{
    long long hash_val = 0;

    for(auto ch: str){
        hash_val ^= (long long)ch;
    }

    hash_val *= 10;
    hash_val++;
    hash_val %= m;

    return hash_val;
}

/// ===================================>>>      hash functions ends    <<<================================


/// ===================================>>>      Chaining Method starts    <<<================================

class Chaining_Method_hashTable
{
    struct List
    {
        pair <string , long long> val;
        List* prev;
        List* next;
    };

    List** table;
    long long table_size;
    const long long default_table_size = 10000;
    long long (*Hash)(string, long long );

public:
    Chaining_Method_hashTable();
    Chaining_Method_hashTable(long long m);
    Chaining_Method_hashTable(long long m, long long (*func)(string , long long));
    void set_size(long long m);
    void Insert(pair < string , long long > input);
    long long Search(string input);
    void Delete(string input);
    ~Chaining_Method_hashTable();
};

Chaining_Method_hashTable::Chaining_Method_hashTable()
{
    table = new List*[default_table_size];
    table_size = default_table_size;

    for(long long pos = 0; pos < table_size; pos++) table[pos] = NULL;
    Hash = &Hash1;
};

Chaining_Method_hashTable::Chaining_Method_hashTable(long long m)
{
    table_size = m;

    table = new List*[table_size];
    for(long long pos = 0; pos < table_size; pos++) table[pos] = NULL;
    Hash = &Hash1;
};

Chaining_Method_hashTable::Chaining_Method_hashTable(long long m, long long (*func)(string , long long))
{
    table_size = m;

    table = new List*[table_size];
    for(long long pos = 0; pos < table_size; pos++) table[pos] = NULL;
    Hash = func;
};

void Chaining_Method_hashTable::set_size(long long m)
{
    for(long long pos = 0; pos < table_size; pos++)
        delete table[pos];

    delete table;
    table_size = m;

    table = new List*[table_size];
    for(long long pos = 0; pos < table_size; pos++) table[pos] = NULL;
}

void Chaining_Method_hashTable::Insert(pair <string, long long > input)
{
    if(Search(input.first) != nullval) return;    // already present

    long long hash_val  = Hash(input.first, table_size);

    if(table[hash_val]){
        /// collision
        collisions++;
        List* temp = table[hash_val];

        while(temp->next){
            temp = temp->next;
        }

        temp->next = new List;

        temp->next->val = input;
        temp->next->prev = temp;
        temp->next->next = NULL;
    }
    else{
        /// empty list
        table[hash_val] = new List;

        table[hash_val]->val = input;
        table[hash_val]->prev = NULL;
        table[hash_val]->next = NULL;
    }
}

long long Chaining_Method_hashTable::Search(string input)
{
    long long hash_val  = Hash(input, table_size);

    if(table[hash_val]){
        List* temp = table[hash_val];

        while(temp){
            probes++;
            if(temp->val.first == input){
                return temp->val.second;
            }
            temp = temp->next;
        }
    }

    return nullval;
}


void Chaining_Method_hashTable::Delete(string input)
{
    long long hash_val  = Hash(input, table_size);

    if(table[hash_val]){
        List* temp = table[hash_val];

        while(temp){
            if(temp->val.first == input){
                /// delete

                if(table[hash_val] == temp){
                    /// root of list

                    table[hash_val] = temp->next;
                    if(table[hash_val])   table[hash_val]->prev = NULL;

                    temp->next = NULL;
                    delete temp;
                }
                else{
                    if(temp->prev)    temp->prev->next = temp->next;
                    if(temp->next)    temp->next->prev = temp->prev;

                    temp->prev = temp->next = NULL;
                    delete temp;
                }

                return;
            }
            temp = temp->next;
        }
    }
}

Chaining_Method_hashTable::~Chaining_Method_hashTable()
{
    for(long long pos = 0; pos < table_size; pos++)
        delete table[pos];

    delete table;
}

/// ===================================>>>      Chaining Method ends    <<<================================


/// ===================================>>>      Double Hashing starts    <<<================================

class Double_Hashing_hashTable
{
    pair <string, long long>* table;
    long long table_size;
    const long long default_table_size = 10000;
    long long (*Hash)(string, long long );
    long long (*auxHash)(string, long long );

public:
    Double_Hashing_hashTable();
    Double_Hashing_hashTable(long long m);
    Double_Hashing_hashTable(long long m, long long (*func)(string , long long), long long (*auxfunc)(string , long long));
    void set_size(long long m);
    void Insert(pair < string , long long > input);
    long long Search(string input);
    void Delete(string input);
    ~Double_Hashing_hashTable();
};

Double_Hashing_hashTable::Double_Hashing_hashTable()
{
    table_size = default_table_size;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
    Hash = &Hash1;
    auxHash = &auxHash__;
}

Double_Hashing_hashTable::Double_Hashing_hashTable(long long m)
{
    table_size = m;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
    Hash = &Hash1;
    auxHash = &auxHash__;
}

Double_Hashing_hashTable::Double_Hashing_hashTable(long long m, long long (*func)(string , long long), long long (*auxfunc)(string , long long) = auxHash__)
{
    table_size = m;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
    Hash = func;
    auxHash = auxfunc;
}

void Double_Hashing_hashTable::set_size(long long m)
{
    delete[] table;

    table_size = m;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
}

void Double_Hashing_hashTable::Insert(pair <string, long long> input)
{
    if(Search(input.first) != nullval) return; // already exists

    long long doubleHash;
    long long i = 0;

    while(true)
    {
        collisions++;
        doubleHash = (Hash(input.first, table_size) + (i*auxHash(input.first, table_size)) % table_size) % table_size;

        if(table[doubleHash].second == nullval){
            table[doubleHash] = input;

            return;
        }
        i++;
        if(i == table_size){
            no_place++;
            return;
        }
    }
}

long long Double_Hashing_hashTable::Search(string input)
{
    long long doubleHash;
    long long i = 0;

    while(true)
    {
        doubleHash = (Hash(input, table_size) + (i*auxHash(input, table_size)) % table_size) % table_size;

        if(table[doubleHash].first == input){
            return table[doubleHash].second;
        }
        probes++;


        if(table[doubleHash].second == nullval){
            // doesn't exist
            return nullval;
        }
        i++;
        if(i == table_size)return nullval;
    }
}


void Double_Hashing_hashTable::Delete(string input)
{
    long long doubleHash;
    long long i = 0;

    while(true)
    {
        doubleHash = (Hash(input, table_size) + (i*auxHash(input, table_size)) % table_size) % table_size;

        if(table[doubleHash].first == input){
            table[doubleHash] = {"", nullval};
            return;
        }

        if(table[doubleHash].second == nullval){
            // doesn't exist
            return;
        }
        i++;
        if(i == table_size)return;
    }
}


Double_Hashing_hashTable::~Double_Hashing_hashTable()
{
    delete[] table;
}


/// ===================================>>>      Double Hashing ends    <<<================================


/// ===================================>>>      Custom Probing starts    <<<================================

class Custom_Probing_hashTable
{
    pair <string, long long>* table;
    long long table_size;
    const long long c1 = 3;
    const long long c2 = 10;
    const long long default_table_size = 10000;
    long long (*Hash)(string, long long );
    long long (*auxHash)(string, long long );

public:
    Custom_Probing_hashTable();
    Custom_Probing_hashTable(long long m);
    Custom_Probing_hashTable(long long m, long long (*func)(string , long long), long long (*auxfunc)(string , long long));
    void set_size(long long m);
    void Insert(pair < string , long long > input);
    long long Search(string input);
    void Delete(string input);
    ~Custom_Probing_hashTable();
};

Custom_Probing_hashTable::Custom_Probing_hashTable()
{
    table_size = default_table_size;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
    Hash = &Hash1;
    auxHash = &auxHash__;
}

Custom_Probing_hashTable::Custom_Probing_hashTable(long long m)
{
    table_size = m;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
    Hash = &Hash1;
    auxHash = &auxHash__;
}

Custom_Probing_hashTable::Custom_Probing_hashTable(long long m, long long (*func)(string , long long), long long (*auxfunc)(string , long long) = auxHash__)
{
    table_size = m;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
    Hash = func;
    auxHash = auxfunc;
}

void Custom_Probing_hashTable::set_size(long long m)
{
    delete[] table;

    table_size = m;
    table = new pair<string, long long>[table_size];

    for(long long i = 0; i < table_size; i++){
        table[i].second = nullval;
    }
}

void Custom_Probing_hashTable::Insert(pair <string, long long> input)
{
    if(Search(input.first) != nullval) return; // already exists

    long long customHash;
    long long i = 0;

    while(true)
    {
        collisions++;
        customHash = (Hash(input.first, table_size) + (c1*i*auxHash(input.first, table_size)) % table_size + (c2*i*i) % table_size) % table_size;

        if(table[customHash].second == nullval){
            table[customHash] = input;

            return;
        }
        i++;
        if(i == table_size){
            no_place++;
            return;
        }
    }
}

long long Custom_Probing_hashTable::Search(string input)
{
    long long customHash;
    long long i = 0;

    while(true)
    {
        customHash = (Hash(input, table_size) + (c1*i*auxHash(input, table_size)) % table_size + (c2*i*i) % table_size) % table_size;

        if(table[customHash].first == input){
            return table[customHash].second;
        }
        probes++;


        if(table[customHash].second == nullval){
            // doesn't exist
            return nullval;
        }
        i++;
        if(i == table_size)return nullval;
    }
}


void Custom_Probing_hashTable::Delete(string input)
{
    long long customHash;
    long long i = 0;

    while(true)
    {
        customHash = (Hash(input, table_size) + (c1*i*auxHash(input, table_size)) % table_size + (c2*i*i) % table_size) % table_size;

        if(table[customHash].first == input){
            table[customHash] = {"", nullval};
            return;
        }

        if(table[customHash].second == nullval){
            // doesn't exist
            return;
        }
        i++;
        if(i == table_size)return;
    }
}


Custom_Probing_hashTable::~Custom_Probing_hashTable()
{
    delete[] table;
}

/// ===================================>>>      Custom Probing ends    <<<================================


vector <string> word_gen(long long n)
{
    vector <string> v;
    set <string> chk;
    string s = "0000000";

    srand(0);

    for(;n--;){
        for(char &ch: s){
            ch = rand()%26 + 'a';
        }

        if(chk.count(s)){
            n++;
            continue;
        }
        v.push_back(s);
    }

    return v;
}

vector <long long> rand_select(long long n, long long m)
{
    vector <long long> v;
    set <long long> chk;
    srand(0);

    for(;n--;){
        long long i = rand()%m;

        if(chk.count(i)){
            n++;
            continue;
        }
        v.push_back(i);
    }

    return v;

}

int main()
{
    long long table_length, search_length;

    cin >> table_length >> search_length;

    vector <string> words = word_gen(table_length);
    vector <long long> indx = rand_select(search_length, table_length);

/// Chaining Method

    Chaining_Method_hashTable cm_ht1(table_length, Hash1), cm_ht2(table_length, Hash2);

    /// hash1
    cout << "Hash1: \n";

    collisions = 0;
    long long i = 1;
    for(string word: words){
        cm_ht1.Insert({word, i});
        i++;
    }

    cout << "No. of Collisions in Chaining Method " << collisions << endl;

    probes = 0;

    for(long long i: indx){
        cm_ht1.Search(words[i]);
    }

    cout << "Avg. Probes in Chaining Method " << probes/(search_length*1.0) << endl;

    cout << endl;

    /// hash2
    cout << "Hash2: \n";
    collisions = 0;

    i = 1;
    for(string word: words){
        cm_ht2.Insert({word, i});
        i++;
    }

    cout << "No. of Collisions in Chaining Method " << collisions << endl;

    probes = 0;

    for(long long i: indx){
        cm_ht2.Search(words[i]);
    }

    cout << "Avg. Probes in Chaining Method " << probes/(search_length*1.0) << endl;


    cout << endl << endl;
/// Double Hashing

    Double_Hashing_hashTable d_ht1(table_length, Hash1), d_ht2(table_length, Hash2);

    /// hash1

    cout << "Hash1: \n";
    collisions = no_place = 0;

    i = 1;
    for(string word: words){
        d_ht1.Insert({word, i});
        i++;
    }

//    cout << "no place " << no_place << endl;
    cout << "No. of Collisions in Double Hashing " << collisions << endl;

    probes = 0;

    for(long long i: indx){
        d_ht1.Search(words[i]);
    }

    cout << "Avg. Probes in Double Hashing " << probes/(search_length*1.0) << endl;

    cout << endl;
    /// hash2

    cout << "Hash2: \n";
    collisions = no_place = 0;

    i = 1;
    for(string word: words){
        d_ht2.Insert({word, i});
        i++;
    }

//    cout << "no place " << no_place << endl;
    cout << "No. of Collisions in Double Hashing " << collisions << endl;

    probes = 0;

    for(long long i: indx){
        d_ht2.Search(words[i]);
    }

    cout << "Avg. Probes in Double Hashing " << probes/(search_length*1.0) << endl;

    cout << endl << endl;

/// Custom Probing

    Custom_Probing_hashTable cp_ht1(table_length, Hash1), cp_ht2(table_length, Hash2);

    /// hash1

    cout << "Hash1: \n";
    collisions = no_place = 0;

    i = 1;
    for(string word: words){
        cp_ht1.Insert({word, i});
        i++;
    }

//    cout << "no place " << no_place << endl;
    cout << "No. of Collisions in Custom Probing " << collisions << endl;

    probes = 0;

    for(long long i: indx){
        cp_ht1.Search(words[i]);
    }

    cout << "Avg. Probes in Custom Probing " << probes/(search_length*1.0) << endl;

    cout << endl;
    /// hash2

    cout << "Hash2: \n";
    collisions = no_place = 0;

    i = 1;
    for(string word: words){
        cp_ht2.Insert({word, i});
        i++;
    }

//    cout << "no place " << no_place << endl;
    cout << "No. of Collisions in Custom Probing " << collisions << endl;

    probes = 0;

    for(long long i: indx){
        cp_ht2.Search(words[i]);
    }

    cout << "Avg. Probes in Custom Probing " << probes/(search_length*1.0) << endl;


    return 0;
}
