# Shell

> Made by [Nerya Bigon](https://github.com/nerya0001).  


Custom shell in c  

Assignment in OS course.  

# GOAL
The goal of this project was to build a basic shell, in order to have deeper understanding of how unix based oparating systems works in general in particular how proccesses works.  

# capability

  1. basic comands such as `ls`, `cd` etc, - basic implementaion with `system()` as well as more advance one with `fork()`, `exec()` and `wait()`.  
  2. menaging TCP server and client.  
  3. Copying and pasting files.  
  4. deleteing files.  

## How To Run
Download this repository and extart it.

1. open a terminal in the main folder and compile the shell by running the following comand:  

```
make all
```  

2. run the shell with the following command:  

```
./main
```  

3. If you want to run the client and server as well, first open a second terminal and run the server:  

```
./server
```  

and then run in the shell terminal the following command (after the shell is active):  

```
TCP PORT
```  


