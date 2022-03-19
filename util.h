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


  // initiate the client code
  void initClient();

  // initiate the server code
  void initServer();

  // instead of ls, list the content of the current directory
  void listDirCont();

  // get the current working directory
  void getCurPath();

  // copy a file from src to dst
  void copySrcToDst(char *src, char *dst);

  #endif