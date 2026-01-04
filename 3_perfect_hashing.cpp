#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll P = 2147483647LL;

int primarySize;
int a1, b1;
vector<vector<int>> buckets;

struct Sec
{
    vector<int> t;
    int a = 0, b = 0;
    ll p = 0;
};

vector<Sec> second;

int h(ll x, int a, int b, ll p) { return (int)(((((ll)a * x + b) % p))); }

void rnd(int &a, int &b)
{
    a = 1 + rand() % (int)(P - 1);
    b = rand() % (int)P;
}

bool collision_free(const vector<int> &keys, int a, int b, ll p, int m)
{
    vector<char> seen(m);
    for (int k : keys)
    {
        int idx = h(k, a, b, p) % m;
        if (seen[idx])
            return false;
        seen[idx] = 1;
    }
    return true;
}

bool build_sec(int idx)
{
    auto &keys = buckets[idx];
    int k = keys.size();
    if (k == 0)
    {
        second[idx].t.clear();
        return true;
    }
    if (k == 1)
    {
        second[idx].t.assign(1, keys[0]);
        second[idx].a = 1;
        second[idx].b = 0;
        second[idx].p = P;
        return true;
    }
    int m = k * k;
    for (int it = 0; it < 1000; ++it)
    {
        int a, b;
        rnd(a, b);
        if (collision_free(keys, a, b, P, m))
        {
            second[idx].t.assign(m, -1);
            second[idx].a = a;
            second[idx].b = b;
            second[idx].p = P;
            for (int x : keys)
                second[idx].t[h(x, a, b, P) % m] = x;
            return true;
        }
    }
    return false;
}

bool insert_key(int key)
{
    int bidx = h(key, a1, b1, P) % primarySize;
    buckets[bidx].push_back(key);
    return build_sec(bidx);
}

bool find_key(int key)
{
    int bidx = h(key, a1, b1, P) % primarySize;
    auto &s = second[bidx];
    if (s.t.empty())
        return false;
    int idx = h(key, s.a, s.b, s.p) % (int)s.t.size();
    return s.t[idx] == key;
}

void show()
{
    cout << "Primary=" << primarySize << "\n";
    for (int i = 0; i < primarySize; i++)
    {
        cout << i << ": ";
        for (int x : buckets[i])
            cout << x << " ";
        if (!buckets[i].empty())
            cout << " | secSize=" << second[i].t.size();
        cout << "\n";
    }
}

int main()
{
    primarySize = 5;
    buckets.assign(primarySize, {});
    second.assign(primarySize, Sec());
    rnd(a1, b1);

    vector<int> keys = {10, 25, 35, 45, 15, 20, 30};
    for (int k : keys)
    {
        cout << "insert " << k << " -> ";
        bool ok = insert_key(k);
        cout << (ok ? "ok" : "fail") << "\n";
    }
    show();

    cout << "\nsearch tests:\n";
    for (int q : {25, 100, 15, 50, 30})
        cout << q << ": " << (find_key(q) ? "FOUND" : "NOT") << "\n";

        
    for (int k : {50, 60, 70})
    {
        insert_key(k);
    }
    cout << "\nafter more inserts:\n";
    show();

    return 0;
}
