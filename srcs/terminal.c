#include "../includes/ft_select.h"

struct termios enableRawMode()
{
    struct termios raw;
	struct termios original;

   	if( tcgetattr(STDIN_FILENO, &raw) == -1)
	   perror_exit("Enable Raw Mode tcgetattr failure");
	original = raw;
    raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	   perror_exit("Enable Raw Mode tcsetattr failure");
	return original;
}

void disableRawMode(struct termios original)
{
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH, &original)== -1)
	   perror_exit("Disable Raw Mode tcsetattr failure");
}
