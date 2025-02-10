#include <iostream>
using namespace std;

struct Process {
    int ID, arrivalTime, burstTime, remainingTime, completionTime, turnaroundTime, waitingTime, priority;
};

void fxn(Process processes[], int totalProcesses) {
    int currentTime = 0, finishedProcesses = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (finishedProcesses < totalProcesses) {
        int index = -1, highestPriority = 1e9;

        for (int i = 0; i < totalProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].priority < highestPriority || 
                   (processes[i].priority == highestPriority && processes[i].remainingTime < processes[index].remainingTime)) {
                    highestPriority = processes[i].priority;
                    index = i;
                }
            }
        }

        if (index == -1) {
            currentTime++;
            continue;
        }

        processes[index].remainingTime--;
        currentTime++;

        if (processes[index].remainingTime == 0) {
            finishedProcesses++;
            processes[index].completionTime = currentTime;
            processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
            processes[index].waitingTime = processes[index].turnaroundTime - processes[index].burstTime;

            totalWaitingTime += processes[index].waitingTime;
            totalTurnaroundTime += processes[index].turnaroundTime;
        }
    }

    cout << "ID\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (int i = 0; i < totalProcesses; i++) {
        cout << processes[i].ID << "\t" << processes[i].arrivalTime << "\t" << processes[i].burstTime << "\t"
             << processes[i].priority << "\t" << processes[i].completionTime << "\t" << processes[i].turnaroundTime << "\t" << processes[i].waitingTime << "\n";
    }

    cout << "Average Turnaround Time = " << (totalTurnaroundTime / totalProcesses) << "\n";
    cout << "Average Waiting Time = " << (totalWaitingTime / totalProcesses) << "\n";
}

int main() {
    const int totalProcesses = 6;
    Process processes[totalProcesses] = {
        {1, 0, 5, 5, 0, 0, 0, 2}, 
        {2, 1, 3, 3, 0, 0, 0, 1}, 
        {3, 2, 8, 8, 0, 0, 0, 4}, 
        {4, 3, 6, 6, 0, 0, 0, 3}, 
        {5, 4, 2, 2, 0, 0, 0, 5}, 
        {6, 5, 4, 4, 0, 0, 0, 2}
    };

    for (int i = 0; i < totalProcesses; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    fxn(processes, totalProcesses);
    return 0;
}
