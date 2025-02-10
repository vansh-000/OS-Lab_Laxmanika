#include <iostream>
using namespace std;

struct Process {
    int ID, AT, BT, CT, TAT, WT;
};

void LJF(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int maxIndex = -1, maxBT = -1;

        // Find the process with the longest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && p[i].BT > maxBT && p[i].CT == 0) {
                maxBT = p[i].BT;
                maxIndex = i;
            }
        }

        if (maxIndex == -1) {
            time++; // CPU remains idle
            continue;
        }

        time += p[maxIndex].BT;
        p[maxIndex].CT = time;
        p[maxIndex].TAT = p[maxIndex].CT - p[maxIndex].AT;
        p[maxIndex].WT = p[maxIndex].TAT - p[maxIndex].BT;

        totalWT += p[maxIndex].WT;
        totalTAT += p[maxIndex].TAT;
        completed++;
    }

    cout << "\nLJF Scheduling Results:\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].ID << "\t" << p[i].AT << "\t" << p[i].BT << "\t"
             << p[i].CT << "\t" << p[i].TAT << "\t" << p[i].WT << "\n";
    }

    cout << "<TAT> = " << (totalTAT / n) << "\n";
    cout << "\n<WT> = " << (totalWT / n) << "\n";
}

int main() {
    const int n = 6;
    Process p[n] = {
        {1, 0, 5, 0, 0, 0}, 
        {2, 1, 3, 0, 0, 0}, 
        {3, 2, 8, 0, 0, 0}, 
        {4, 3, 6, 0, 0, 0}, 
        {5, 4, 2, 0, 0, 0}, 
        {6, 5, 4, 0, 0, 0}
    };

    LJF(p, n);
    return 0;
}