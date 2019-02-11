#include "../includes/ft_select.h"
static int termput_c(int c)
{
	return(write(1, &c,1));
}
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
	hide_cursor();

	return original;
}

void disableRawMode(struct termios original)
{
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH, &original)== -1)
	   perror_exit("Disable Raw Mode tcsetattr failure");
	display_cursor();
}

void display_cursor()
{
	tputs (tgetstr("ve",NULL),1,termput_c);
}

void hide_cursor()
{
	tputs (tgetstr("vi",NULL),1,termput_c);
}