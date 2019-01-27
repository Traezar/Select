#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../includes/ft_select.h"
void enableRawMode(struct termios *original)
{
    struct termios raw;

    raw = *original;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(struct termios *original)
{
    tcsetattr(STDIN_FILENO,TCSAFLUSH, original);
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