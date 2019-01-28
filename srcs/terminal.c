#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../includes/ft_select.h"
void enableRawMode(struct termios original)
{
    struct termios raw;

    raw = original;
   	if( tcgetattr(STDIN_FILENO, &raw) == -1)
	   perror_exit("Enable Raw Mode tcgetattr failure");
    raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	   perror_exit("Enable Raw Mode tcsetattr failure");
}

void disableRawMode(struct termios original)
{
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH, &original)== -1)
	   perror_exit("Disable Raw Mode tcsetattr failure");
}

int getWindowSize(int *rows, int *cols)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col <= 0)
		return (-1);
	else
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return (0);
	}
}