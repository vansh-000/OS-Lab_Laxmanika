#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
struct Process
{
    int id;
    int AT;
    int BT;
    int CT;
    int WT;
    int TAT;
};
void fxn(vector<Process> &process, string algorithm)
{
    int n = process.size();
    int current_time = 0;
    int total_WT = 0;
    int total_TAT = 0;
    int idle_time = 0;
    sort(process.begin(), process.end(), [](Process a, Process b)
         { return a.AT < b.AT; });
    if (algorithm == "SJF")
    {
        vector<bool> completed(n, false);
        int count1 = 0;
        while (count1 < n)
        {
            int idx = -1;
            int min_BT = INT_MAX;
            for (int i = 0; i < n; ++i)
            {
                if (!completed[i] && process[i].AT <= current_time && process[i].BT < min_BT)
                {
                    min_BT = process[i].BT;
                    idx = i;
                }
            }
            if (idx != -1)
            {
                current_time += process[idx].BT;
                process[idx].CT = current_time;
                process[idx].TAT = process[idx].CT - process[idx].AT;
                process[idx].WT = process[idx].TAT - process[idx].BT;
                total_WT += process[idx].WT;
                total_TAT += process[idx].TAT;
                completed[idx] = true;
                ++count1;
            }
            else
            {
                ++current_time;
                ++idle_time;
            }
        }
    }
    else if (algorithm == "FCFS")
    {
        for (int i = 0; i < n; ++i)
        {
            if (current_time < process[i].AT)
            {
                idle_time += process[i].AT - current_time;
                current_time = process[i].AT;
            }
            current_time += process[i].BT;
            process[i].CT = current_time;
            process[i].TAT = process[i].CT - process[i].AT;
            process[i].WT = process[i].TAT - process[i].BT;
            total_WT += process[i].WT;
            total_TAT += process[i].TAT;
        }
    }
    cout << "\n"
         << algorithm << " Scheduling:\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto &p : process)
    {
        cout << "P" << p.id << "\t" << p.AT << "\t" << p.BT << "\t" << p.CT << "\t" << p.TAT << "\t" << p.WT << "\n";
    }
    cout << "Average Waiting Time: " << (double)total_WT / n << "\n";
    cout << "Average Turnaround Time: " << (double)total_TAT / n << "\n";
    cout << "CPU Idle Time: " << idle_time << "\n";
}
int main()
{
    int n;
    cout << "Enter the number of process: ";
    cin >> n;
    vector<Process> process(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; ++i)
    {
        process[i].id = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> process[i].AT >> process[i].BT;
    }
    vector<Process> sjf_process = process;
    vector<Process> fcfs_process = process;
    fxn(fcfs_process, "FCFS");
    fxn(sjf_process, "SJF");
    return 0;
}