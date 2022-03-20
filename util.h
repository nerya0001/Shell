#ifndef _UTIL_H_
#define _UTIL_H_

#define NORMAL  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"

#define BUF_SIZE 20

  // initiate the client code
  void initClient();

  // initiate the server code
  void initServer();

  // instead of ls, list the content of the current directory
  void listDirCont();

  // get the current working directory
  void getCurPath();

  // echo
  void echo(char* buffer);

  // cd
  void changeDir(char* buffer);

  // copy a file from src to dst
  void copySrcToDst(char* buffer);

  // delete file
  void del(char* buffer);

  // instead of using system()
  int sysReplacement(char* buffer);

  #endif