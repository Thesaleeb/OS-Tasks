#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int arrival;
    int burst;
};

// FCFS
double fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int time = 0, totalWait = 0;

    for (int i = 0; i < p.size(); i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;

        totalWait += time - p[i].arrival;
        time += p[i].burst;
    }

    return (double)totalWait / p.size();
}

// Simple SJF (non-preemptive)
double sjf(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);

    int time = 0, finished = 0, totalWait = 0;

    while (finished < n) {
        int idx = -1;
        int minBurst = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        totalWait += time - p[idx].arrival;
        time += p[idx].burst;

        done[idx] = true;
        finished++;
    }

    return (double)totalWait / n;
}

// Simple Round Robin
double roundRobin(vector<Process> p, int q) {
    int n = p.size();
    vector<int> rem(n), wait(n, 0);

    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;

    int time = 0;
    bool done;

    while (true) {
        done = true;

        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && p[i].arrival <= time) {
                done = false;

                if (rem[i] > q) {
                    time += q;
                    rem[i] -= q;
                } else {
                    time += rem[i];
                    wait[i] = time - p[i].burst - p[i].arrival;
                    rem[i] = 0;
                }
            }
        }

        if (done)
            break;

        time++;
    }

    int totalWait = 0;
    for (int i = 0; i < n; i++)
        totalWait += wait[i];

    return (double)totalWait / n;
}

// Simple text bar chart
void drawChart(double a, double b, double c) {
    cout << "\n--- Bar Chart ---\n";

    cout << "FCFS: ";
    for (int i = 0; i < a; i++) cout << "#";
    cout << " (" << a << ")\n";

    cout << "SJF : ";
    for (int i = 0; i < b; i++) cout << "#";
    cout << " (" << b << ")\n";

    cout << "RR  : ";
    for (int i = 0; i < c; i++) cout << "#";
    cout << " (" << c << ")\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "Arrival time: ";
        cin >> p[i].arrival;

        cout << "Burst time: ";
        cin >> p[i].burst;
    }

    int q;
    cout << "Enter time quantum: ";
    cin >> q;

    double fc = fcfs(p);
    double sj = sjf(p);
    double rr = roundRobin(p, q);

    cout << "\nAverage Waiting Times:\n";
    cout << "FCFS: " << fc << endl;
    cout << "SJF: " << sj << endl;
    cout << "Round Robin: " << rr << endl;

    drawChart(fc, sj, rr);

    return 0;
}