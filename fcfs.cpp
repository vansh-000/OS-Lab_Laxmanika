#include <bits/stdc++.h>
using namespace std;

vector<int> CT;

// get Table
void getTable(vector<vector<int>> &arr)
{
    int n = arr.size();
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][0] > total)
        {
            total = arr[i][0];
        }
        total += arr[i][2];
        arr[i][3] = total;
        arr[i][4] = arr[i][3] - arr[i][0];
        arr[i][5] = arr[i][4] - arr[i][2];
    }
}

int main()
{
    // AT. pNo. BT  CT TAT WT
    vector<vector<int>> arr = {
        {6, 1, 4, 0, 0, 0},
        {2, 2, 5, 0, 0, 0},
        {3, 3, 3, 0, 0, 0},
        {1, 4, 1, 0, 0, 0},
        {4, 5, 2, 0, 0, 0},
        {5, 6, 6, 0, 0, 0}};
    // sort the vector
    sort(arr.begin(), arr.end());

    getTable(arr);

    // swap the vector
    for (int i = 0; i < arr.size(); i++)
    {
        swap(arr[i][0], arr[i][1]);
    }
    // sort the vector
    sort(arr.begin(), arr.end());
    // print the vector
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < 6; j++)
        {
             cout << setfill(' ') << setw(2) << arr[i][j] << "  ";
        }
        cout << endl;
    }
    return 0;
}
