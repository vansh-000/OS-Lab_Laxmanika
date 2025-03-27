#include <iostream>
#include <limits>
using namespace std;
class Process
{
public:
    string processName;
    int arrivalTime;
    int burstTime;
    int priority;

    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    void initialize()
    {
        remainingTime = burstTime;
    }
};
int main()
{
    int numOfProcesses;
    cout << "Enter the number of processes: ";
    cin >> numOfProcesses;
    Process processes[numOfProcesses];
    for (int n = 0; n < numOfProcesses; n++)
    {
        cout << "\nEnter Process Name for " << (n + 1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for " << (n + 1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for " << (n + 1) << ": ";
        cin >> processes[n].burstTime;
        cout << "Enter Priority for " << (n + 1) << ": ";
        cin >> processes[n].priority;
        processes[n].initialize();
    }
    int currentTime = 0;
    int completedProcesses = 0;
    while (completedProcesses < numOfProcesses)
    {
        int highestPriorityIndex = -1;
        int highestPriority = numeric_limits<int>::min();
        for (int i = 0; i < numOfProcesses; i++)
        {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime)
            {
                if (processes[i].priority > highestPriority)
                {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
                else if (processes[i].priority == highestPriority)
                {
                    if (processes[i].arrivalTime < processes[highestPriorityIndex].arrivalTime)
                    {
                        highestPriorityIndex = i;
                    }
                }
            }
        }
        if (highestPriorityIndex == -1)
        {
            currentTime++;
            continue;
        }
        processes[highestPriorityIndex].remainingTime--;
        currentTime++;
        if (processes[highestPriorityIndex].remainingTime == 0)
        {
            processes[highestPriorityIndex].completionTime = currentTime;
            completedProcesses++;
        }
    }
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
    for (int n = 0; n < numOfProcesses; n++)
    {
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;
        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Completion Time: " << processes[n].completionTime << endl;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n"
             << endl;

        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }
    cout << "\n\nAverage Waiting Time for " << numOfProcesses << " Processes: "
         << (float)sumWaitingTime / numOfProcesses;
    cout << "\nAverage Turn Around Time for " << numOfProcesses << " Processes: "
         << (float)sumTurnAroundTime / numOfProcesses << endl;

    return 0;
}