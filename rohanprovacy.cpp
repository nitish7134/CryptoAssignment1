#include <bits/stdc++.h>
#include <iostream>

using namespace std;

char matrix_rev[5][5];
char matrix_fair[5][5];
string key_fair, text_pl;
int RailFenceKey, Change_mat_loop;
string final_ptxt;
string stringkey;

string manner_spiral(string a)
{
    int var3, var2, var1, var4;
    int new_num = 0;
    int num_ctr = 0;

    var1 = 0;

    var2 = 0;

    var3 = 5;

    var4 = 5;

    while (var2 < var4 && var1 < var3)
    {
        int i = var3 - 1;

        while (i > var1 - 1)
        {
            matrix_rev[var4 - 1][i] = a[num_ctr++];
            --i;
        }
        var4--;
        i = var4 - 1;

        while (i > var2 - 1)
        {
            matrix_rev[i][var1] = a[num_ctr++];
            --i;
        }
        var1++;

        if (var1 < var3)
        {
            i = var1;
            while (i < var3)
            {
                matrix_rev[var2][i] = a[num_ctr++];

                ++i;
            }
            var2++;
        }

        if (var2 < var4)
        {
            i = var2;

            while (i < var4)
            {
                matrix_rev[i][var3 - 1] = a[num_ctr++];

                ++i;
            }
            var3--;
        }
    }

    string res(25, '*');

    int i = 0;

    while (i <= 4)
    {
        int j = 0;

        while (j <= 4)
        {
            res[new_num] = matrix_rev[i][j];

            ++j;

            ++new_num;
        }

        ++i;
    }
    return res;
}

string rlfnc(int key, string txt_inp)
{
    string fin_rslt = "";

    int txt_len = 0;

    txt_len = txt_inp.length();

    bool dir;

    int num_row;
    int num_col;

    char rl_matrix[key][(txt_len)];

    dir = false;

    int i = 0;

    while (i <= key - 1)
    {

        int j = 0;
        while (j <= txt_len - 1)
        {
            rl_matrix[i][j] = '*';

            ++j;
        }
        ++i;
    }

    num_row = 0;

    num_col = 0;

    int v1 = 0;

    while (v1 <= txt_len - 1)
    {

        if (num_row == key - 1 || num_row == 0)
        {

            dir = !dir;
        }

        rl_matrix[num_row][num_col] = txt_inp[v1];

        ++num_col;

        if (dir)

        {

            ++num_row;
        }
        else
            --num_row;

        ++v1;
    }
    int v2 = 0;

    while (v2 <= key - 1)
    {

        int v3 = 0;
        while (v3 <= txt_len - 1)
        {
            if (rl_matrix[v2][v3] != '*')
            {

                fin_rslt.push_back(rl_matrix[v2][v3]);
            }
            ++v3;
        }
        ++v2;
    }
    return fin_rslt;
}

pair<int, int> get_loc(char a, char new_mat[5][5]) //findind the location
{
    int i = 0;

    while (i < 5)
    {
        int j = 0;
        while (j < 5)
        {
            if ((a == new_mat[i][j]) || (new_mat[i][j] == 'i' && a == 'j') || (new_mat[i][j] == 'j' && a == 'i'))
            {
                pair<int, int> ret_loc{i, j};

                return ret_loc;
            }
            ++j;
        }
        ++i;
    }
}
string playFull(string text_pl, char Matrix_k[5][5]) // returns cipher text
{
    int i;

    string CT_text;
    i = 0;

    CT_text = "";

    while (i <= text_pl.size() - 1)
    {
        pair<int, int> po, uo;

        po = get_loc(text_pl[i], Matrix_k); //calling the location finder function

        if (text_pl[i + 1] == text_pl[i])
        {
            uo = get_loc(text_pl[i] == 'z' ? 'y' : 'z', Matrix_k);
            i--;
        }
        else
        {
            uo = get_loc(text_pl[i + 1], Matrix_k);
        }
        int var5 = po.first % 5;
        int var10 = (po.first + 1) % 5;
        int var12 = uo.first % 5;
        int var9 = (uo.first + 1) % 5;

        int var11 = uo.second % 5;
        int var6 = (uo.second + 1) % 5;
        int var7 = (po.second + 1) % 5;
        int var8 = (po.second % 5);

        char prop1, prop2; // equalising the value for character 1 and character 2 acoordingly
        if (po.first == uo.first)
        {
            prop2 = Matrix_k[var5][var6];
            prop1 = Matrix_k[var5][var7];
        }
        else if (po.second == uo.second)
        {
            prop2 = Matrix_k[var9][var8];
            prop1 = Matrix_k[var10][var8];
        }
        else
        {
            prop1 = Matrix_k[var5][var11];
            prop2 = Matrix_k[var12][var8];
        }

        i = i + 2;

        // adding the character to the cipher text
        CT_text = CT_text + prop1;

        CT_text = CT_text + prop2;
    }

    return CT_text;
}

int main()
{
    int w;
    cin >> w; // input number of test cases you wnt to run
    while (w--)
    { 
//input key for railfence cipher
        cin >> RailFenceKey;
        //input key for playfair cipher (only lowercase alphabets)
        cin >> key_fair;

        int size_fair = key_fair.size();
        //input number of times loop should be called
        cin >> Change_mat_loop;

        //input the plaintext

        cin >> text_pl;
        int i = 0;
        int num_ctr;

        int numb = 0;
        num_ctr = 0;
        int done[26] = {0};
        while (i <= 4)
        {
            for (int j = 0; j <= 4; ++j)
            {

                if (numb < size_fair)
                {
                    char numct = key_fair[numb];

                    if (done[numct - 'a'] == 1)
                    {

                        j--;
                    }
                    else
                    {
                        matrix_fair[i][j] = numct;
                        if (numct == 'j' || numct == 'i')
                        {

                            done['i' - 'a'] = 1;

                            done['j' - 'a'] = 1;
                        }
                        else

                        {
                            done[numct - 'a'] = 1;
                        }
                    }

                    numb++;

                    continue;
                }
                else
                {
                    while (done[num_ctr++] != 0)
                        ;
                    char numct;

                    matrix_fair[i][j] = 'a' + num_ctr - 1;
                    numct += 'a' - 1;

                    if (numct == 'i' || numct == 'j')
                    {

                        done['i' - 'a'] = 1;

                        done['j' - 'a'] = 1;
                    }

                    done['a' + num_ctr - 1] = 1;
                }
            }
            ++i;
        }

        int ts = 0;
        stringkey = "";
        int new_num = 0;

        for (int i = 0; i <= 4; ++i)
        {
            int j = 0;

            while (j <= 4)
            {

                stringkey = stringkey + matrix_fair[i][j];

                ++j;
            }
        }
        string manner_keyspiral = manner_spiral(stringkey);
         i = 0;
      
      
        while (ts <= Change_mat_loop - 1)
        {

            manner_keyspiral = manner_spiral(rlfnc(RailFenceKey, manner_keyspiral));

            ++ts;
        }
    

        i = 0;
        final_ptxt = "";
        new_num = 0;

        while (i <= 4)
        {
            int j = 0;
            while (j <= 4)
            {

                matrix_fair[i][j++] = manner_keyspiral[new_num++];
            }
            ++i;
        }
        i = 0;
        while (i <= 4)
        {
            int j = 0;

            while (j <= 4)
            {

                cout << matrix_fair[i][j++] << " ";
            }

            cout << endl;

            ++i;
        }

        i = 0;
        while (i < text_pl.size()) //looping across the plaintext
        {
            final_ptxt = final_ptxt + text_pl[i];

            if (text_pl[i + 1] == text_pl[i])
            {

                if (text_pl[i] == 'z')

                {
                    final_ptxt += 'y'; //adding y if the next alphabet is same as the previous and is z
                }
                else //adding z if the next alphabet is same as the previous

                    final_ptxt += 'z';
            }
            ++i;
        }
        if (final_ptxt.size() & 1) // checking for if the text right now is odd or not
        {
            if (final_ptxt[final_ptxt.size() - 1] == 'z')
            {

                final_ptxt = final_ptxt + 'y'; //adding y
            }

            else

                //adding z
                final_ptxt += 'z';
        }

        cout << playFull(final_ptxt, matrix_fair);
        cout << "\n";

    }
    return 0;
}