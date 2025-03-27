#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Process
{
    int id, arrival, burst, remaining, completion, waiting, turnaround;
};
bool compareLJF(Process a, Process b)
{
    return a.burst > b.burst;
}
bool compareArrival(Process a, Process b)
{
    return a.arrival < b.arrival;
}
void LJF(vector<Process> &processes)
{
    sort(processes.begin(), processes.end(), compareArrival);
    vector<Process> readyQueue;
    int time = 0, totalWaiting = 0, totalTurnaround = 0, count = 0;
    while (!processes.empty() || !readyQueue.empty())
    {
        while (!processes.empty() && processes.front().arrival <= time)
        {
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());
        }
        if (!readyQueue.empty())
        {
            sort(readyQueue.begin(), readyQueue.end(), compareLJF);
            Process &current = readyQueue.front();
            time += current.burst;
            current.completion = time;
            current.turnaround = current.completion - current.arrival;
            current.waiting = current.turnaround - current.burst;
            totalWaiting += current.waiting;
            totalTurnaround += current.turnaround;
            count++;
            cout << "Process " << current.id << " | Completion Time: " << current.completion
                 << " | Turnaround Time: " << current.turnaround << " | Waiting Time : " << current.waiting << endl;
            readyQueue.erase(readyQueue.begin());
        }
        else
        {
            cout << "CPU Idle at time " << time << endl;
            time++;
        }
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaiting / count;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnaround / count << endl;
}
void LRTF(vector<Process> &processes)
{
    int time = 0, completed = 0, n = processes.size();
    int totalWaiting = 0, totalTurnaround = 0;
    Process *current = nullptr;
    while (completed < n)
    {
        Process *maxProc = nullptr;
        for (auto &p : processes)
        {
            if (p.arrival <= time && p.remaining > 0)
            {
                if (!maxProc || p.remaining > maxProc->remaining)
                {
                    maxProc = &p;
                }
            }
        }
        if (maxProc)
        {
            maxProc->remaining--;
            if (maxProc->remaining == 0)
            {
                maxProc->completion = time + 1;
                maxProc->turnaround = maxProc->completion - maxProc->arrival;
                maxProc->waiting = maxProc->turnaround - maxProc->burst;
                totalWaiting += maxProc->waiting;
                totalTurnaround += maxProc->turnaround;
                cout << "Process " << maxProc->id << " | Completion Time: " << maxProc->completion
                     << " | Turnaround Time: " << maxProc->turnaround << " |Waiting Time : " << maxProc->waiting << endl;
                completed++;
            }
        }
        else
        {
            cout << "CPU Idle at time " << time << endl;
        }
        time++;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaiting / n;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnaround / n << endl;
}
int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    cout << "Enter Arrival Time and Burst Time for each process: \n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << processes[i].id << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }
    int choice;
    cout << "Choose Scheduling Algorithm: \n1. LJF (Non-Preemptive)\n2. LRTF(Preemptive)\nEnter choice: ";
    cin >> choice;
    if (choice == 1)
        LJF(processes);
    else if (choice == 2)
        LRTF(processes);
    else
        cout << "Invalid choice!";
    return 0;
}