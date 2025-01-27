#include <bits/stdc++.h>
using namespace std;

void srtfScheduling(vector<vector<int>> &arr)
{
    int n = arr.size();
    vector<int> remainingTime(n);
    for (int i = 0; i < n; i++)
        remainingTime[i] = arr[i][2];

    int complete = 0, currentTime = 0, minRemainingTime = INT_MAX;
    int shortest = -1, finishTime;
    bool found = false;

    while (complete != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i][1] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemainingTime)
            {
                minRemainingTime = remainingTime[i];
                shortest = i;
                found = true;
            }
        }

        if (!found)
        {
            currentTime++;
            continue;
        }

        remainingTime[shortest]--;
        minRemainingTime = remainingTime[shortest];

        if (minRemainingTime == 0)
            minRemainingTime = INT_MAX;

        if (remainingTime[shortest] == 0)
        {
            complete++;
            found = false;

            finishTime = currentTime + 1;
            arr[shortest][3] = finishTime;                          // Completion time
            arr[shortest][4] = arr[shortest][3] - arr[shortest][1]; // Turnaround time
            arr[shortest][5] = arr[shortest][4] - arr[shortest][2]; // Waiting time
        }

        currentTime++;
    }
}

int main()
{
    // pNo,AT, BT, CT, TAT, WT
    vector<vector<int>> arr = {
        {1, 3, 4, 0, 0, 0},
        {2, 4, 2, 0, 0, 0},
        {3, 5, 1, 0, 0, 0},
        {4, 2, 6, 0, 0, 0},
        {5, 1, 8, 0, 0, 0},
        {6, 2, 4, 0, 0, 0}};

    int n = arr.size();

    sort(arr.begin(), arr.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[1] < b[1]; });

    srtfScheduling(arr);

    sort(arr.begin(), arr.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });

    cout << "  PNo  AT   BT   CT  TAT   WT\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << setw(4) << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
