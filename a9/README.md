CS5008, Spring 2021\
Homework 9\
Xuan Guo

cd:
- Change the current directory to provided directory
- The command would change the current directory to provided directory DIR. if suceed, will return " Changed directory to: DIR"; if no such directory found, will return "Unable to find the directory"
- I implemented this using chdir(). And I used the argv[0] to identify if it is cd command and pass argv[1] to chdir as parameter

help:
- Display information about builtin commands.
- Display information about builtin commands: cd, help, exit, game
- I implemented this using printf(). And I used the argv[0] to identify if it is help command

exit:
- Exit the shell
- terminate the shell
- I implemented this using exit(0). And I used the argv[0] to identify if it is exit command

game:
- Generate a dancing DONUT for 5 seconds.
- This command generate ASCII art in form of a spinning donut, and it lasts for 5 seconds.
- I implemented this by applying rotation matrix to a static donut shape and followed online tutorial.

PLEASE use to make to compile and ./shell to run.

1. How many hours did it take you to complete this assignment?\
12 hours.
2. Did you collaborate with any other students/TAs/Professors? Who?\
Self.
3. Did you use any external resources? (Cite them below)\
Google.
4. (Optional) What was your favorite part of the assignment?
5. (Optional) How would you improve the assignment?
