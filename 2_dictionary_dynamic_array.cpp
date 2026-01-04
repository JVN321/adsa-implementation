#include <bits/stdc++.h>
using namespace std;

struct Entry {
    string key;
    int value;
};

Entry *arr;
int sz = 0, cap = 1;

void show() {
    cout << "sz=" << sz << " cap=" << cap << " [";
    for (int i = 0; i < sz; i++) {
        cout << "(" << arr[i].key << ":" << arr[i].value << ")";
        if (i < sz - 1) cout << ",";
    }
    cout << "]\n";
}

void resizeArr(int newCap) {
    Entry *newArr = new Entry[newCap];
    for (int i = 0; i < sz; i++) newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

int findIndex(const string &k) {
    for (int i = 0; i < sz; i++) if (arr[i].key == k) return i;
    return -1;
}

void setKV(const string &k, int v) {
    int idx = findIndex(k);
    if (idx != -1) {
        arr[idx].value = v;
    } else {
        if (sz == cap) resizeArr(max(1, cap * 2));
        arr[sz++] = {k, v};
    }
    show();
}

void eraseKV(const string &k) {
    int idx = findIndex(k);
    if (idx == -1) {
        cout << "Key not found\n";
        return;
    }
    arr[idx] = arr[sz - 1];
    sz--;
    if (sz > 0 && sz <= cap / 4) resizeArr(max(1, cap / 2));
    show();
}

void getKV(const string &k) {
    int idx = findIndex(k);
    if (idx == -1) cout << "Key not found\n";
    else cout << arr[idx].value << "\n";
}

int main() {

    arr = new Entry[1];

    cout << "Dictionary (string->int) using dynamic array\n";
    cout << "1: set key value\n2: get key\n3: erase key\n4: show\n5: exit\n";

    while (true) {
        cout << "> ";
        int cmd;
        if (!(cin >> cmd)) break;
        if (cmd == 1) {
            string k; int v; cin >> k >> v;
            setKV(k, v);
        } else if (cmd == 2) {
            string k; cin >> k; getKV(k);
        } else if (cmd == 3) {
            string k; cin >> k; eraseKV(k);
        } else if (cmd == 4) {
            show();
        } else if (cmd == 5) {
            break;
        } else {
            cout << "Invalid command\n";
        }
    }

    delete[] arr;
    return 0;
}
