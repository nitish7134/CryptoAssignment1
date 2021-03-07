#include <bits/stdc++.h>
#define IOS                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);                   \
    cerr.tie(NULL)
#define ll long long
#define test  \
    int t;    \
    cin >> t; \
    while (t--)
#define fo(i, n) for (ll i = 0; i < n; i++)
#define foi(i, initial, n) for (ll i = initial; i < n; i++)
#define fori(i, n) for (int i = 1; i <= n; i++)
#define vi vector<int>
#define ii pair<int, int>
#define vii vector<ii>
#define vvi vector<vi>
#define int32 _int32
#define sortarr(a, n) sort(a, a + n)
#define sortvec(a) sort(a.begin(), a.end())
#define endl "\n"
#define inp(a, n) fo(i, n) cin >> a[i]
#define printvec(a) fo(i, a.size()) cout << a[i] << " "

using namespace std;

int main()
{
    IOS;

    int keys[3][3];
    string cipherText = "***";
    string key, plainText;
    cin >> key >> plainText;
    int x = 0;
    fo(i, 3)
    {
        fo(j, 3)
        {
            keys[j][i] = key[x] - 'a';
            x++;
        }
    }
    fo(i, 3)
    {
        plainText[i] = plainText[i] - 'a';
    }
    fo(i, 3)
    {
        cipherText[i] = (plainText[0] * keys[0][i] + plainText[1] * keys[1][i] + plainText[2] * keys[2][i]) % 26 + 'a';
    }
    cout << cipherText;
}