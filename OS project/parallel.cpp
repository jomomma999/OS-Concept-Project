#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    string location;
    if (!inputFile.is_open()) {
        perror("Error: can't open input file\n");
        return 1;
    }
    int locationNumber = 1;
    int numLocations = 0;

    while (inputFile >> location) {
        numLocations++;
    }
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);
    pid_t childPids[numLocations];
    //child process
    for (int i = 0; i < numLocations; i++) {
        pid_t childPid = fork();
        int execlpRetVal;

        if (childPid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (childPid == 0) { 
            ostringstream filename;
            filename << "file" << locationNumber << ".json";

            // Execute curl 
            execlpRetVal= execlp("/usr/bin/curl", "curl", "-o", "file1.json", "https://api.open-meteo.com/v1/forecast?latitude=52.520000&longitude=13.410000&current_weather=True", NULL);
            if(execlpRetVal < 0){
			    perror("Error: can't execute curl\n");
			    exit(1);
		    }
        } else { // Parent process
            childPids[i] = childPid;
            locationNumber++;
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < numLocations; i++) {
        waitpid(childPids[i], NULL, 0);
    }

    // Close the input file
    inputFile.close();

    return 0;
}