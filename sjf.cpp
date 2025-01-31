#include <bits/stdc++.h>
using namespace std;

void schedulearr(vector<vector<int>> &arr, int n, int &done, int currentTime)
{
    if (done == n)
        return;

    for (int i = 0; i < n; i++)
    {
        if (arr[i][3] == 0 && arr[i][1] <= currentTime)
        {
            currentTime += arr[i][2];
            arr[i][3] = currentTime;
            arr[i][4] = arr[i][3] - arr[i][1];
            arr[i][5] = arr[i][4] - arr[i][2];
            done++;
        }
    }

    schedulearr(arr, n, done, currentTime);
}

void calculateSchedule(vector<vector<int>> &arr, int index)
{
    int n = arr.size();
    int done = 1;
    int currentTime = arr[index][1] + arr[index][2];
    arr[index][3] = currentTime;
    arr[index][4] = arr[index][3] - arr[index][1];
    arr[index][5] = arr[index][4] - arr[index][2];

    schedulearr(arr, n, done, currentTime);
}

int main()
{
    // pNo. AT. BT  CT TAT WT
    vector<vector<int>> arr = {
        {1, 3, 4, 0, 0, 0},
        {2, 4, 2, 0, 0, 0},
        {3, 5, 1, 0, 0, 0},
        {4, 2, 6, 0, 0, 0},
        {5, 1, 8, 0, 0, 0},
        {6, 2, 4, 0, 0, 0}};

    int n = arr.size();

    sort(arr.begin(), arr.end(), [](const vector<int> &a, const vector<int> &b)
         { return (a[2] < b[2]) || (a[2] == b[2] && a[1] < b[1]); });

    int firstProcessIndex = 0;
    int min = 100;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][1] < min)
        {
            min = arr[i][1];
            firstProcessIndex = i;
        }
    }

    calculateSchedule(arr, firstProcessIndex);

    sort(arr.begin(), arr.end());

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
