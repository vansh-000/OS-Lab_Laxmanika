#include <iostream>
#include <queue>
using namespace std;

class Process {
public:
    string processName;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int completionTime;
    int responseTime;
    int turnAroundTime;
    int remainingTime;
    bool started;

    void initialize() {
        waitingTime = 0;
        responseTime = -1; 
        turnAroundTime = 0;
        remainingTime = burstTime;
        started = false;
    }
};

int main() {
    int numOfProcesses, timeQuantum;
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;
    cout << "Enter number of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];
    queue<int> readyQueue;

    for (int n = 0; n < numOfProcesses; n++) {
        cout << "\nEnter Process Name for " << (n + 1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for " << processes[n].processName << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for " << processes[n].processName << ": ";
        cin >> processes[n].burstTime;
        processes[n].initialize();
    }

    int currentTime = 0, completedProcesses = 0;
    int lastAddedIndex = 0;

    while (completedProcesses < numOfProcesses) {
        for (int i = lastAddedIndex; i < numOfProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime) {
                readyQueue.push(i);
                lastAddedIndex++;
            } else {
                break;
            }
        }

        if (readyQueue.empty()) {
            currentTime = processes[lastAddedIndex].arrivalTime;
            continue;
        }

        int i = readyQueue.front();
        readyQueue.pop();

        if (!processes[i].started) {
            processes[i].responseTime = currentTime - processes[i].arrivalTime;
            processes[i].started = true;
        }

        int executionTime = min(timeQuantum, processes[i].remainingTime);
        currentTime += executionTime;
        processes[i].remainingTime -= executionTime;
        for (int j = lastAddedIndex; j < numOfProcesses; j++) {
            if (processes[j].arrivalTime <= currentTime) {
                readyQueue.push(j);
                lastAddedIndex++;
            } else {
                break;
            }
        }

        if (processes[i].remainingTime > 0) {
            readyQueue.push(i);
        } else {
            processes[i].completionTime = currentTime;
            processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
            completedProcesses++;
        }
    }

    int sumResponseTime = 0, sumWaitingTime = 0, sumTurnAroundTime = 0;

    for (int n = 0; n < numOfProcesses; n++) {
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n";

        sumResponseTime += processes[n].responseTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }

    cout << "\nAverage Response Time: " << (float)sumResponseTime / numOfProcesses;
    cout << "\nAverage Waiting Time: " << (float)sumWaitingTime / numOfProcesses;
    cout << "\nAverage Turn Around Time: " << (float)sumTurnAroundTime / numOfProcesses << endl;

    return 0;
}