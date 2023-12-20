# OS-Concept-Project

Part 1 Overview
Write a simple shell program called shell. When ran, the parent process will print out the
prompt which looks like

cmd>

and will then wait for the user to enter a command such as ls, ps, or any other command. For
example:

cmd> ls

The parent process will then use fork() in order to create a child and then call wait() in order
to wait for the child to terminate. The child process will use execlp() in order to replace its
program with the program entered at the command line. After the child produces the output,
the parent will prompt the user for another command. For example:
cmd>ls
file.txt fork fork.c mystery1 mystery1.cpp mystery2 shell shell.cpp

The parent will repeat the above sequence until the user types the exit command, which will
cause the parent process to exit.

Part 2 Overview
n this part you will design a two programs that make use of fork(), execlp(), and wait()
functions to fetch weather information for a bunch of locations from a web-based weather service
API. The basic logic of each program will be as follows:
1. The program reads the latitude and longitude location from the specified file.
2. The program creates a child that uses the curl program to contact the weather service,
fetch the weather information (in JSON format), and save it to the file.
3. Repeat the process for the next location specified in the file. If there are no more locations
left, exit
The difference between the two programs is the method they use for fetching weather for multiple
locations:
1. a serial fetcher: which will fetch the city information one city at a time. That is, the
parent must wait for each child to finish fetching the weather for its location before creating
another child.
2. a parallel fetching: the parent will create a child for each location (i.e., without waiting
for a child to complete) and only once all children have been created, the parent will wait
for all of them to terminate.
You will then compare the performance of the two types of fetchers using the time utility.
Both fetchers will use the Linux curl program in order to communicate with the weather API
and fetch the weather information that is formatted according to the JavaScript Object Notation
format. You can read more about the https://www.tutorialspoint.com/json/json quick guide.htm.
The command line to fetch the JSON weather data for location at latitude location 52.52 and
longitude location 13.41 and then save it in file file1.json is as follows:
/usr/bin/curl -o file1.json "https://api.open-meteo.com/v1/forecast?latitude=52.520000&longitude=13.410000&current weather=True
Where
• /usr/bin/curl: The name of the curl program
• -o: Specifies that we want to save the data fetched to the file.
• file1.json: The name of the file where we want to save the fetched data.
• https://api.open-meteo.com/v1/forecast?latitude=52.520000&longitude=13.410000&current weather=True :
is the URL of the web API from which to fetch the data. The values in bold blue
represent latitude and longitude of locations from which to fetch the weather.
