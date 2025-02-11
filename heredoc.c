#include "minishell.h"

int main(int argc, char *argv[])
{
    char buffer[1024];
    ssize_t bytes_read;
    int fd;
    char *delimitor;
    
    delimitor = ft_strdup(argv[1]); // change this 
    while (1)
    {
        write(0, "> ", 2);
        bytes_read = read(0, buffer, sizeof(buffer) - 1); // use gnl instead?
        if (bytes_read <= 0)
            break;

        buffer[bytes_read - 1] = '\0';
        if (ft_strcmp(buffer, delimitor) == 0)
            break;
    }
    if (argc > 2)
    {
        fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            return(free (delimitor), 1);
    }
    free (delimitor);
    return 0;
}

