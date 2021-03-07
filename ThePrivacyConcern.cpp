#include <bits/stdc++.h>
#define IOS                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);                   \
    cerr.tie(NULL)

using namespace std;

string railfence(string text, int key)
{

    char rail[key][(text.length())];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '*';

    bool direction = false;
    int row = 0, col = 0;

    for (int i = 0; i < text.length(); i++)
    {

        if (row == 0 || row == key - 1)
            direction = !direction;
        rail[row][col++] = text[i];
        direction ? row++ : row--;
    }
    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '*')
                result.push_back(rail[i][j]);

    return result;
}

string spiralFill(string a)
{
    char revMat[5][5];
    int alphctr = 0;
    int k = 0, l = 0, m = 5, n = 5;
    while (k < m && l < n)
    {
        for (int i = m - 1; i >= k; --i)
            revMat[n - 1][i] = a[alphctr++];
        n--;

        for (int i = n - 1; i >= l; --i)
            revMat[i][k] = a[alphctr++];
        k++;
        if (k < m)
        {
            for (int i = k; i < m; ++i)
                revMat[l][i] = a[alphctr++];
            l++;
        }

        if (l < n)
        {
            for (int i = l; i < n; ++i)
                revMat[i][m - 1] = a[alphctr++];
            m--;
        }
    }
    int ptr = 0;
    string res(25, '*');
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            res[ptr++] = revMat[i][j];
    }
    return res;
}
string changeMatrix(string a, int key)
{
    return spiralFill(railfence(a, key));
}
pair<int, int> findLocation(char a, char mat[5][5])
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (a == mat[i][j] || (a == 'i' && mat[i][j] == 'j') || (a == 'j' && mat[i][j] == 'i'))
            {
                pair<int, int> location{i, j};
                return location;
            }
        }
    }
}
string playFull(string plainText, char keyMat[5][5])
{
    string cipherText = "";
    for (int i = 0; i < plainText.size(); i += 2)
    {
        pair<int, int> loc1, loc2;
        loc1 = findLocation(plainText[i], keyMat);
        if (plainText[i] == plainText[i + 1])
        {
            loc2 = findLocation(plainText[i] == 'z' ? 'y' : 'z', keyMat);
            i--;
        }
        else
        {
            loc2 = findLocation(plainText[i + 1], keyMat);
        }
        char char1, char2;
        if (loc1.first == loc2.first)
        {
            char1 = keyMat[loc1.first % 5][(loc1.second + 1) % 5];
            char2 = keyMat[loc1.first % 5][(loc2.second + 1) % 5];
        }
        else if (loc1.second == loc2.second)
        {
            char1 = keyMat[(loc1.first + 1) % 5][loc1.second % 5];
            char2 = keyMat[(loc2.first + 1) % 5][loc1.second % 5];
        }
        else
        {
            char1 = keyMat[loc1.first % 5][loc2.second % 5];
            char2 = keyMat[loc2.first % 5][loc1.second % 5];
        }
        cipherText += char1;
        cipherText += char2;
    }
    return cipherText;
}
int solve()
{
    char playKeyMat[5][5];
    int Completed[26] = {0};
    int RKey, changeCount;
    string playKey, plainText;
    cin >> RKey;
    cin >> playKey;
    cin >> changeCount;
    cin >> plainText;
    int alphctr = 0;
    int playkeySize = playKey.size();
    int ct = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {

            if (ct < playkeySize)
            {
                char temp = playKey[ct];

                if (Completed[temp - 'a'] == 1)
                    j--;
                else
                {
                    playKeyMat[i][j] = temp;
                    if (temp == 'i' || temp == 'j')
                    {
                        Completed['i' - 'a'] = 1;
                        Completed['j' - 'a'] = 1;
                    }
                    else
                        Completed[temp - 'a'] = 1;
                }
                ct++;
                continue;
            }
            else
            {
                while (Completed[alphctr++] != 0)
                    ;
                playKeyMat[i][j] = alphctr + 'a' - 1;
                char temp = alphctr + 'a' - 1;
                if (temp == 'i' || temp == 'j')
                {
                    Completed['i' - 'a'] = 1;
                    Completed['j' - 'a'] = 1;
                }
                Completed[alphctr + 'a' - 1] = 1;
            }
        }
    }

    string platKeyMatString = "";
    int ptr = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            platKeyMatString += playKeyMat[i][j];
        }
    }
    string resKey = spiralFill(platKeyMatString);
    for (int i = 0; i < changeCount; i++)
    {
        resKey = changeMatrix(resKey, RKey);
    }
    ptr = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            playKeyMat[i][j] = resKey[ptr++];

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << playKeyMat[i][j] << " ";
        }
        cout << endl;
    }
    string editedPlainText = "";
    for (int i = 0; i < plainText.size(); i++)
    {
        editedPlainText += plainText[i];

        if (plainText[i] == plainText[i + 1])
        {
            editedPlainText += plainText[i] == 'z' ? 'y' : 'z';
        }
        }
    if (editedPlainText.size() & 1)
        editedPlainText += editedPlainText[editedPlainText.size() - 1] == 'z' ? 'y' : 'z';
    cout << playFull(editedPlainText, playKeyMat) << endl;
    return 0;
}
int main()
{
    IOS;
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}