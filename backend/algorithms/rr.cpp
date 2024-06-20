#include <bits/stdc++.h>
#define sz(a) ((int)((a).size()))
#define uchar unsigned char

using namespace std; 
typedef long long int64;
typedef long double ldouble;

struct Job {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
};

bool compareArrival(const Job &A, const Job &B) {
    if (A.arrival == B.arrival) {
        return A.pid < B.pid;
    } else {
        return A.arrival < B.arrival;
    }
}

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    int numJobs, timeSlice;
    inFile >> numJobs;
    
    vector<Job> jobs(numJobs);
    for (int i = 0; i < numJobs; ++i) {
        inFile >> jobs[i].pid >> jobs[i].arrival >> jobs[i].burst;
    }
    inFile >> timeSlice;
    
    sort(jobs.begin(), jobs.end(), compareArrival);
    queue<Job> jobQueue;
    map<int, int> completionMap;
    map<int, int> firstRunMap;

    int currentTime = 0;
    int index = 0;
    if (jobs[index].arrival > currentTime) {
        currentTime = jobs[index].arrival;
    }
    
    while (index < numJobs && jobs[index].arrival <= currentTime) {
        jobQueue.push(jobs[index]);
        ++index;
    }
    
    while (index < numJobs) {
        Job currentJob = jobQueue.front();
        if (firstRunMap.count(currentJob.pid) == 0) {
            firstRunMap[currentJob.pid] = currentTime;
        }
        jobQueue.pop();
        bool jobCompleted = false;
        if (currentJob.burst <= timeSlice) {
            currentTime += currentJob.burst;
            jobCompleted = true;
            completionMap[currentJob.pid] = currentTime;
        } else {
            currentTime += timeSlice;
            currentJob.burst -= timeSlice;
        }
        while (index < numJobs && jobs[index].arrival <= currentTime) {
            jobQueue.push(jobs[index]);
            ++index;
        }
        if (!jobCompleted) {
            jobQueue.push(currentJob);
        }
    }

    while (!jobQueue.empty()) {
        Job currentJob = jobQueue.front();
        if (firstRunMap.count(currentJob.pid) == 0) {
            firstRunMap[currentJob.pid] = currentTime;
        }
        jobQueue.pop();
        if (currentJob.burst <= timeSlice) {
            currentTime += currentJob.burst;
            completionMap[currentJob.pid] = currentTime;
        } else {
            currentTime += timeSlice;
            currentJob.burst -= timeSlice;
            jobQueue.push(currentJob);
        }
    }

    for (auto &job : jobs) {
        job.completion = completionMap[job.pid];
        job.turnaround = job.completion - job.arrival;
        job.waiting = job.turnaround - job.burst;
        job.response = firstRunMap[job.pid] - job.arrival;
    }
    
    ldouble avgWaiting = 0, avgResponse = 0, avgTurnaround = 0;
    for (const auto &job : jobs) {
        avgResponse += job.response;
        avgWaiting += job.waiting;
        avgTurnaround += job.turnaround;
    }
    
    avgWaiting /= numJobs;
    avgResponse /= numJobs;
    avgTurnaround /= numJobs;
    
    outFile << avgWaiting << endl;
    outFile << avgTurnaround << endl;
    outFile << avgResponse << endl;

    return 0;
}
