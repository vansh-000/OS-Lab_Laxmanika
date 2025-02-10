#include <iostream>
using namespace std;

struct Process {
    int ID, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime, priority;
};

void executePriorityNonPreemptiveScheduling(Process pro[], int totalpro) {
    int currentTime = 0, finishedpro = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    bool isCompleted[totalpro] = {false};

    while (finishedpro < totalpro) {
        int index = -1, highestPriority = 1e9;

        for (int i = 0; i < totalpro; i++) {
            if (pro[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (pro[i].priority < highestPriority || 
                   (pro[i].priority == highestPriority && pro[i].arrivalTime < pro[index].arrivalTime)) {
                    highestPriority = pro[i].priority;
                    index = i;
                }
            }
        }

        if (index == -1) {
            currentTime++;
            continue;
        }

        currentTime += pro[index].burstTime;
        pro[index].completionTime = currentTime;
        pro[index].turnaroundTime = pro[index].completionTime - pro[index].arrivalTime;
        pro[index].waitingTime = pro[index].turnaroundTime - pro[index].burstTime;

        totalWaitingTime += pro[index].waitingTime;
        totalTurnaroundTime += pro[index].turnaroundTime;

        isCompleted[index] = true;
        finishedpro++;
    }

    cout << "ID\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (int i = 0; i < totalpro; i++) {
        cout << pro[i].ID << "\t" << pro[i].arrivalTime << "\t" << pro[i].burstTime << "\t"
             << pro[i].priority << "\t" << pro[i].completionTime << "\t" << pro[i].turnaroundTime << "\t" << pro[i].waitingTime << "\n";
    }

    cout << "Average Turnaround Time = " << (totalTurnaroundTime / totalpro) << "\n";
    cout << "Average Waiting Time = " << (totalWaitingTime / totalpro) << "\n";
}

int main() {
    const int totalpro = 6;
    Process pro[totalpro] = {
        {1, 0, 5, 0, 0, 0, 2}, 
        {2, 1, 3, 0, 0, 0, 1}, 
        {3, 2, 8, 0, 0, 0, 4}, 
        {4, 3, 6, 0, 0, 0, 3}, 
        {5, 4, 2, 0, 0, 0, 5}, 
        {6, 5, 4, 0, 0, 0, 2}
    };

    executePriorityNonPreemptiveScheduling(pro, totalpro);
    return 0;
}
