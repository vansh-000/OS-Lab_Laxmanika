#include <iostream>
using namespace std;

struct Process {
    int ID, AT, BT, remaining, CT, TAT, WT;
};

void LRTF(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int maxIndex = -1, maxRemaining = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && p[i].remaining > 0) {
                if (p[i].remaining > maxRemaining) {
                    maxRemaining = p[i].remaining;
                    maxIndex = i;
                }
            }
        }

        if (maxIndex == -1) {
            time++; // CPU remains idle
            continue;
        }

        p[maxIndex].remaining--;
        time++;

        if (p[maxIndex].remaining == 0) {
            completed++;
            p[maxIndex].CT = time;
            p[maxIndex].TAT = p[maxIndex].CT - p[maxIndex].AT;
            p[maxIndex].WT = p[maxIndex].TAT - p[maxIndex].BT;

            totalWT += p[maxIndex].WT;
            totalTAT += p[maxIndex].TAT;
        }
    }

    cout << "\nLRTF Scheduling Results:\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].ID << "\t" << p[i].AT << "\t" << p[i].BT << "\t"
             << p[i].CT << "\t" << p[i].TAT << "\t" << p[i].WT << "\n";
    }

    cout << "\n<WT> = " << (totalWT / n) << "\n";
    cout << "<TAT> = " << (totalTAT / n) << "\n";
}

int main() {
    const int n = 6;
    Process p[n] = {
        {1, 0, 5, 5, 0, 0, 0}, 
        {2, 1, 3, 3, 0, 0, 0}, 
        {3, 2, 8, 8, 0, 0, 0}, 
        {4, 3, 6, 6, 0, 0, 0}, 
        {5, 4, 2, 2, 0, 0, 0}, 
        {6, 5, 4, 4, 0, 0, 0}
    };

    LRTF(p, n);
    return 0;