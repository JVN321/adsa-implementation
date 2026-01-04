#include <bits/stdc++.h>
using namespace std;

int *arr;
int sz = 0, cap = 1;

void show() {
    cout << "sz=" << sz << " cap=" << cap << " [";
    for (int i = 0; i < sz; i++) {
        cout << arr[i];
        if (i < sz - 1) cout << ",";
    }
    cout << "]\n";
}

void resize(int newCap) {
    int *newArr = new int[newCap];
    for (int i = 0; i < sz; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

void push(int x) {
    if (sz == cap) resize(cap * 2);
    arr[sz++] = x;
    show();
}

void pop() {
    if (sz == 0) {
        cout << "Array is empty!\n";
        return;
    }
    sz--;
    if (sz > 0 && sz <= cap / 4) resize(cap / 2);
    show();
}

int main() {
    arr = new int[1];
    
    cout << "Dynamic Array Operations:\n";
    cout << "1. Push value\n";
    cout << "2. Pop value\n";
    cout << "3. Show array\n";
    cout << "4. Exit\n\n";
    
    while (true) {
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            cout << "Enter value: ";
            int x;
            cin >> x;
            push(x);
        } else if (choice == 2) {
            pop();
        } else if (choice == 3) {
            show();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}
