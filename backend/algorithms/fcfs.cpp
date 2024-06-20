#include <iostream>
#include <fstream>
#include <vector>

struct Task {
    int id;
    int arrival;
    int duration;
};

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    int count;
    inputFile >> count;
    std::vector<Task> tasks(count);
    for (int i = 0; i < count; ++i) {
        inputFile >> tasks[i].id >> tasks[i].arrival >> tasks[i].duration;
    }

    std::vector<int> waitTime(count), turnTime(count), responseTime(count);
    int elapsedTime = 0;
    for (int i = 0; i < count; ++i) {
        if (elapsedTime < tasks[i].arrival) {
            elapsedTime = tasks[i].arrival;
        }
        waitTime[i] = elapsedTime - tasks[i].arrival;
        turnTime[i] = waitTime[i] + tasks[i].duration;
        responseTime[i] = waitTime[i];
        elapsedTime += tasks[i].duration;
    }

    double averageWait = 0, averageTurn = 0, averageResponse = 0;
    for (int i = 0; i < count; ++i) {
        averageWait += waitTime[i];
        averageTurn += turnTime[i];
        averageResponse += responseTime[i];
    }
    averageWait /= count;
    averageTurn /= count;
    averageResponse /= count;

    outputFile << averageWait << std::endl;
    outputFile << averageTurn << std::endl;
    outputFile << averageResponse << std::endl;

    return 0;
}
