#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
public:
    string processName;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int responseTime;
};

bool compare(Process a, Process b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.processName < b.processName;
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int numOfProcesses;
    cout << "Enter no. of processes: ";
    cin >> numOfProcesses;

    vector<Process> processes(numOfProcesses);

    for (int i = 0; i < numOfProcesses; i++) {
        cout << "\nEnter Process Name for " << (i + 1) << ": ";
        cin >> processes[i].processName;
        cout << "Enter Arrival Time for Process " << (i + 1) << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter Burst Time for Process " << (i + 1) << ": ";
        cin >> processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compare);

    int currentTime = 0; 
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    for (int i = 0; i < numOfProcesses; i++) {

        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime; 
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;

        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

        cout << "\nProcess " << processes[i].processName << ":\n";
        cout << "Completion Time: " << processes[i].completionTime << endl;
        cout << "Waiting Time: " << processes[i].waitingTime << endl;
        cout << "Turn Around Time: " << processes[i].turnAroundTime << endl;
    }

    cout << "\n\nAverage Waiting Time: " << (float)totalWaitingTime / numOfProcesses;
    cout << "\nAverage Turn Around Time: " << (float)totalTurnAroundTime / numOfProcesses << endl;

    return 0;
}

