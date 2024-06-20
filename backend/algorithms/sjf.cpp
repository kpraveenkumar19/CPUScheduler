#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Job {
    int id;
    int arrival;
    int burst;
};

bool burstTimeComparator(Job a, Job b) {
    return a.burst < b.burst;
}

int main() {
    std::ifstream inFile("input.txt");
    std::ofstream outFile("output.txt");
    int jobCount;
    inFile >> jobCount;
    std::vector<Job> jobList(jobCount);
    for (int i = 0; i < jobCount; ++i) {
        inFile >> jobList[i].id >> jobList[i].arrival >> jobList[i].burst;
    }

    std::sort(jobList.begin(), jobList.end(), burstTimeComparator);

    std::vector<int> waitTime(jobCount), turnTime(jobCount), respTime(jobCount);
    int currentTime = 0;
    for (int i = 0; i < jobCount; ++i) {
        if (currentTime < jobList[i].arrival) {
            currentTime = jobList[i].arrival;
        }
        waitTime[i] = currentTime - jobList[i].arrival;
        turnTime[i] = waitTime[i] + jobList[i].burst;
        respTime[i] = waitTime[i];
        currentTime += jobList[i].burst;
    }

    double avgWait = 0, avgTurn = 0, avgResp = 0;
    for (int i = 0; i < jobCount; ++i) {
        avgWait += waitTime[i];
        avgTurn += turnTime[i];
        avgResp += respTime[i];
    }
    avgWait /= jobCount;
    avgTurn /= jobCount;
    avgResp /= jobCount;

    outFile << avgWait << std::endl;
    outFile << avgTurn << std::endl;
    outFile << avgResp << std::endl;

    return 0;
}
