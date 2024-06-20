#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

struct Job {
    int id;
    int arrival;
    int burst;
    int remaining;
};

int main() {
    std::ifstream inFile("input.txt");
    std::ofstream outFile("output.txt");
    int numJobs;
    inFile >> numJobs;
    std::vector<Job> jobList(numJobs);
    for (int i = 0; i < numJobs; ++i) {
        inFile >> jobList[i].id >> jobList[i].arrival >> jobList[i].burst;
        jobList[i].remaining = jobList[i].burst;
    }

    std::vector<int> waitTimes(numJobs), turnaroundTimes(numJobs), responseTimes(numJobs, -1);
    int currentTime = 0, jobsCompleted = 0;

    while (jobsCompleted < numJobs) {
        int shortestJobIndex = -1;
        int minimumRemaining = INT_MAX;

        for (int i = 0; i < numJobs; ++i) {
            if (jobList[i].arrival <= currentTime && jobList[i].remaining > 0 && jobList[i].remaining < minimumRemaining) {
                minimumRemaining = jobList[i].remaining;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex != -1) {
            if (responseTimes[shortestJobIndex] == -1) {
                responseTimes[shortestJobIndex] = currentTime - jobList[shortestJobIndex].arrival;
            }
            currentTime++;
            jobList[shortestJobIndex].remaining--;
            if (jobList[shortestJobIndex].remaining == 0) {
                jobsCompleted++;
                waitTimes[shortestJobIndex] = currentTime - jobList[shortestJobIndex].arrival - jobList[shortestJobIndex].burst;
                turnaroundTimes[shortestJobIndex] = currentTime - jobList[shortestJobIndex].arrival;
            }
        } else {
            currentTime++;
        }
    }

    double totalWaitTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    for (int i = 0; i < numJobs; ++i) {
        totalWaitTime += waitTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
        totalResponseTime += responseTimes[i];
    }
    double avgWaitTime = totalWaitTime / numJobs;
    double avgTurnaroundTime = totalTurnaroundTime / numJobs;
    double avgResponseTime = totalResponseTime / numJobs;

    outFile << avgWaitTime << std::endl;
    outFile << avgTurnaroundTime << std::endl;
    outFile << avgResponseTime << std::endl;

    return 0;
}
