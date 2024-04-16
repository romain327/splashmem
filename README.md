# splashmem
A little school project of a kind of 2D version of splatoon with SDL. There are players that can move according to a list of movements, each movements make them spend credits and the game stops when all the players' credits reach 0. Being able to do that would give us a 15/20 grade, and we were asked to enhance the project in order to get a 20/20. That's why this projects contains actually 2 version of splashmem :
- the basic project that can be found in the ```splashmem``` folder.
- the enhanced project that can be found in the ```splashmem_enhanced``` folder.

## About splashmem_enhanced
We were given exemple of what an enhanced project could be : make a better display, a little menu, things like this...
I decided to use my system programming knowledge from CS bachelor to make a server-client version of the game, where each player could be controlled by a client processus, and each player's moves would be bound on a key. This version works for 4 players max. More client could connect to the server but the game would crash because I didn't handle the "if a new client connects it creates a new player" part because of a lack of time. But from one to four players it works perfectly.

We have a socket connection between the server and the players, and a shared array between the server process and the game process. When a clients connects it can send keys to the server, which will write the received char in the shared array at the index of the client (first client's keys will be written at index 0 and so on). Then the game process loops on the array and execute the action linked to the char it reads.

### Try the programm

To try this programm, open a bash, go to the folder splashmem_enhanced and type : ```make all```, then ```./run.sh```. This will start the server. To lunch clients, in the folder ```cl```, open a new bash and type ```./client``` and the client process will connect to the server, then you can start sending commands.

The credits number is 9000, it's huge so if you want to close the game, you have two ways : 
- wait for all 4 players to reach 0 credits
- click on the SDL window and press the q key. This will close the window and stop the server with a SIGTERM signal.

To stop the client, just press x in the client process.

## Libraries
You may need to install libraries for SDL. In order to do that, open a shell and type ```sudo apt-get install libsdl2-2.0-0``` or whatever package manager you use. 

## About splashmem_rebuild
This is a rebuild of splashmem using SDL renderer in order to try to make the game smoother.
This version is still under construction.

## Coming soon
I'll try to build this project for Windows too.

## Related
As a following of this project, we were given another project in which we had to make a downloadable version of this game, and parameter this game from a website. The source code is visible [here]{https://github.com/romain327/better_splashmem}, and you can follow the instructions and the project explanations here : https://brouard.dev/splashmem

Enjoy :)