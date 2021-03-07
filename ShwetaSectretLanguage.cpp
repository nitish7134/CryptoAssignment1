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
int inverse[2][2];
int key[2][2];
int input[2][2];
int keyInverse[2][2];
int inverseMod;
void matrixMultiplier()
{
    key[0][0] = (inverse[0][0] * input[0][0] + inverse[0][1] * input[1][0]) % 26;
    key[1][0] = (inverse[1][0] * input[0][0] + inverse[1][1] * input[1][0]) % 26;
    key[0][1] = (inverse[0][0] * input[0][1] + inverse[0][1] * input[1][1]) % 26;
    key[1][1] = (inverse[1][0] * input[0][1] + inverse[1][1] * input[1][1]) % 26;
}
int modInverse(int a, int m)
{
    fori(x, m - 1) if (((a % m) * (x % m)) % m == 1) return x;
}
int main()
{
    IOS;
    string cipherText;

    cin >> cipherText;
    if (cipherText.size() % 2 == 1)
    {
        cipherText = cipherText + 'Z';
    }
    inverse[0][0] = 4;
    inverse[1][0] = 19;
    inverse[0][1] = 19;
    inverse[1][1] = 19;
    fo(i,2)
    {
        fo(j,2)
        {
            char temp;
            cin >> temp;
            input[i][j] = temp - 'A';
        }
    }
    matrixMultiplier();
    fo(i,2)
    {
        fo(j,2)
        {
            keyInverse[i][j] = key[i][j];
        }
    }
    swap(keyInverse[1][1], keyInverse[0][0]);
    keyInverse[0][1] *= -1;
    keyInverse[1][0] *= -1;
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = det % 26;
    inverseMod = modInverse(det, 26);
    fo(i,2)
    {
        fo(j,2)
        {
            keyInverse[i][j] *= inverseMod;
            keyInverse[i][j] %= 26;
            if (keyInverse[i][j] < 0)
            {
                keyInverse[i][j] += 26;
            }
        }
    }
    string plainText = "";
    for (int i = 0; i < cipherText.size(); i = i + 2)
    {
        char one = cipherText[i], two = cipherText[i + 1];
        int first = one - 'A';
        int second = two - 'A';
        int decryptedf = first * keyInverse[0][0] + second * keyInverse[1][0];
        decryptedf %= 26;
        int decrypteds = first * keyInverse[0][1] + second * keyInverse[1][1];
        decrypteds %= 26;
        char x = 'A' + decryptedf;
        char y = 'A' + decrypteds;
        plainText = plainText + x;
        plainText = plainText + y;
    }
    cout << plainText;
}
