#include <iostream>
#include <limits>
using namespace std;

class Process {
public:
    string processName;
    int arrivalTime;
    int burstTime;

    bool isCompleted;
    int completionTime;
    int waitingTime;
    int turnAroundTime;

    void initialize() {
        isCompleted = false;
    }
};
int main() {
    int numOfProcesses;
    cout << "Enter number of processes: ";
    cin >> numOfProcesses;
    Process processes[numOfProcesses];
    for (int n = 0; n < numOfProcesses; n++) {
        cout << "\nEnter Process Name for " << (n + 1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n + 1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n + 1) << ": ";
        cin >> processes[n].burstTime;
        processes[n].initialize();
    }
    cout << "\n";
    for (int i = 0; i < numOfProcesses - 1; i++) {
        for (int j = i + 1; j < numOfProcesses; j++) {
            if (processes[j].arrivalTime < processes[i].arrivalTime) {
                swap(processes[j], processes[i]);
            }
        }
    }

    int currentTime = 0;
    int completedProcesses = 0;
    while (completedProcesses < numOfProcesses) {
        int currentLongestJobIndex = -1;
        int currentLongestJobBurstTime = -1; 
        for (int i = 0; i < numOfProcesses; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime > currentLongestJobBurstTime) { 
                    currentLongestJobBurstTime = processes[i].burstTime;
                    currentLongestJobIndex = i;
                }
            }
        }

        if (currentLongestJobIndex == -1) {

            currentTime++;
            continue;
        }

        currentTime += processes[currentLongestJobIndex].burstTime;
        processes[currentLongestJobIndex].completionTime = currentTime;
        processes[currentLongestJobIndex].turnAroundTime = processes[currentLongestJobIndex].completionTime - processes[currentLongestJobIndex].arrivalTime;
        processes[currentLongestJobIndex].waitingTime = processes[currentLongestJobIndex].turnAroundTime - processes[currentLongestJobIndex].burstTime;
        processes[currentLongestJobIndex].isCompleted = true;
        completedProcesses++;
    }
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
    for (int n = 0; n < numOfProcesses; n++) {
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Completion Time: " << processes[n].completionTime << endl;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n";

        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }
    cout << "\n\nAverage Waiting Time: " << (float)sumWaitingTime / numOfProcesses;
    cout << "\nAverage Turn Around Time: " << (float)sumTurnAroundTime / numOfProcesses << endl;

    return 0;
}