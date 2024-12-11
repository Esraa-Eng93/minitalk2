#include "minitalk.h"

void handle_error(const char *msg)
{
    write(1, msg, ft_strlen(msg));
    exit(1);
}

char	*add_char(char *start, char c)
{
	size_t i;
    char *tmp;

    tmp = malloc(ft_strlen(start) + 2);
    if (tmp == NULL)
        return (NULL);
    i = 0;
    while (start[i] != '\0')
    {
        tmp[i] = start[i];
        i++;
    }
    tmp[i] = c;
   tmp[i + 1] = '\0';
    free(start);
    return (tmp);
	}

void	signal_handler(int sig)
{
	static char	*message = NULL;
	static int	bitcount = 0;
	static char     current_char = 0;
	
	if (message == NULL)
	{
		message = ft_strdup("");
		if ( message == NULL )
		    handle_error("Memory allocation error\n");
	}

	if (sig == SIGUSR1)
	        current_char = current_char | 1;
	bitcount++;
	if (bitcount == 8)
	{
	        message = add_char(message, current_char);
	        if ( message == NULL )
		      handle_error("Memory allocation error\n");
	         //write(1, &current_char, 1);
	        if(current_char == '\0')
	        {
	              write(1, message, ft_strlen(message)); 
                     write(1, "\n", 1);
                     free(message); 
                     message = NULL;
               }
		current_char = 0;
		bitcount = 0;
	}
	else
	current_char <<= 1;
}


int main(void)
{
    
    char *pid;

    pid = ft_itoa(getpid());
    write(1, "Server PID: ", 12);
    write(1, pid, ft_strlen(pid));
    write(1, "\n", 1);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
     free(pid);
    while (1)
        pause();
    return (0);
}
