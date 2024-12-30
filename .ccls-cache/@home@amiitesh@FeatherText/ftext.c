#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRaw(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRaw(){
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRaw);


  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(){
  enableRaw();
  char c;
  while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
  return 0;
}
