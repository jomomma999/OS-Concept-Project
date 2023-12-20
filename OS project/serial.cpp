#include <iostream>
#include <fstream>
#include <sstream>
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

    while (inputFile >> location) {
        // Creates child process
        pid_t childPid = fork();

        int execlpRetVal;
        int childEventInfo;
        int waitReturn; 

        if (childPid < 0) {
            perror("Error: could not fork\n");
            return 1;
        }

        if (childPid == 0) { // Child process
            // Print process information
            fprintf(stderr, "Child: I am a child. My process id is %d\n", getpid());
            fprintf(stderr, "Child: The process id of my parent is %d\n", getppid());
            string filename = "file" + to_string(locationNumber ) + ".json";
            // Execute curl in the child process
            execlpRetVal = execlp("/usr/bin/curl", "curl", "-o", "file1.json", "https://api.open-meteo.com/v1/forecast?latitude=52.520000&longitude=13.410000&current_weather=True", NULL);


            if(execlpRetVal < 0){
			    perror("Error: can't execute curl\n");
			    exit(1);
		    }
        } else { // Parent process
            waitReturn = wait(&childEventInfo);

            if(waitReturn < 0){
                perror("wait");
                exit(1);
            }
            if(WIFEXITED(childEventInfo)){
                fprintf(stderr, "Parent: The child with pid=%d has terminated\n", waitReturn);
                fprintf(stderr, "Paent: The child's exit code is %d\n", WEXITSTATUS(childEventInfo));	
		    }
            // Fork another child for the next location
            locationNumber++;
        }
    }
    inputFile.close();
    return 0;
}

