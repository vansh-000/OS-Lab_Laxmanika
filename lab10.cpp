#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
struct Process
{
    int pid, arrival_time, burst_time, waiting_time, turnaround_time,
        remaining_time, completion_time;
};
void sjfScheduling(vector<Process> &processes)
{
    int n = processes.size(), time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.arrival_time < b.arrival_time; });
    while (completed < n)
    {
        int shortest = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].burst_time < min_burst)
            {
                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }
        if (shortest == -1)
        {
            time++;
            continue;
        }
        time += processes[shortest].burst_time;
        processes[shortest].waiting_time = time - processes[shortest].arrival_time -
                                           processes[shortest].burst_time;
        processes[shortest].turnaround_time = time -
                                              processes[shortest].arrival_time;
        processes[shortest].remaining_time = 0;
        completed++;
        total_wt += processes[shortest].waiting_time;
        total_tat += processes[shortest].turnaround_time;
    }
    cout << "\nSJF Scheduling:";
    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";
}
void srtfScheduling(vector<Process> &processes)
{
    int n = processes.size(), time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    for (auto &p : processes)
    {
        p.remaining_time = p.burst_time;
    }
    while (completed < n)
    {
        int shortest = -1, min_rem = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_rem)
            {
                min_rem = processes[i].remaining_time;
                shortest = i;
            }
        }
        if (shortest == -1)
        {
            time++;
            continue;
        }
        processes[shortest].remaining_time--;
        time++;
        if (processes[shortest].remaining_time == 0)
        {
            completed++;
            processes[shortest].completion_time = time;
            processes[shortest].turnaround_time = time -
                                                  processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time -
                                               processes[shortest].burst_time;
            total_wt += processes[shortest].waiting_time;
            total_tat += processes[shortest].turnaround_time;
        }
    }
    cout << "\nSRTF Scheduling:";
    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";
}
int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }
    sjfScheduling(processes);
    srtfScheduling(processes);
    return 0;
}
