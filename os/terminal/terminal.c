#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXTOKEN 2048
#define MAXARGC 32

const char* EXIT = "exit";
const char EOL = '\n';

const char* paths[] =
{
    "",
    "/bin/",
    "/usr/bin/",
    "/usr/sbin/"
};

int num_paths()
{
  return sizeof(paths) / sizeof(char*);
}

int main(int arga, char* argv[], char* arge[])
{
    while (1)
    {
        char* args[MAXARGC];
        unsigned int argc = 1;
        printf(">>---> ");
        args[0] = malloc(MAXTOKEN);
        char c;
        while ((c = getchar()) == ' ' || c == EOL || c == '\t') {}
        if (c == EOF)
        {
            free(args[0]);
            break;
        }
        char str[MAXTOKEN];
        str[0] = c;
        str[1] = '\0';
        scanf("%s", args[0]);
        strcat(str, args[0]);
        strcpy(args[0], str);
        if (!strcmp(args[0], EXIT))
        {
            free(args[0]);
            break;
        }
        c = '\0';
        while (1)
        {
            if (c != EOL)
            {
                while ((c = getchar()) == ' ' || c == EOF || c == '\t') {}
            }
            if (c == EOL)
            {
                args[argc] = NULL;
                pid_t pid;
                int status;
                pid = fork();
                if (pid == 0)
                {
                    char path[MAXTOKEN] = "";
                    char command[MAXTOKEN];
                    strcpy(command, args[0]);
                    for (size_t i = 0; i < num_paths(); ++i)
                    {
                        strcat(path, paths[i]);
                        strcat(path, command);
                        strcpy(args[0], path);
                        execve(args[0], args, arge);
                        path[0] = '\0';
                    }
                    perror("Execve failed");
                    return 0;
                }
                else
                {
                    if (pid > 0)
                    {
                        waitpid(pid, &status, 0);
                        printf("Child process terminated with status: %d\n", status);
                    }
                    else
                    {
                        perror("Fork failed");
                    }
                }
                break;
            }
            unsigned int pos = 1;
            args[argc] = malloc(MAXTOKEN);
            args[argc][0] = c;
            while ((c = getchar()) != ' ' && c != EOL && c != '\t')
            {
                if (c == EOF)
                {
                    continue;
                }
                args[argc][pos] = c;
                ++pos;
            }
            args[argc][pos] = '\0';
            ++argc;
        }
        for (size_t i = 0; i < argc; ++i)
        {
            free(args[i]);
        }
    }
    return 0;
}
//wc -l <file> - word counting
//cat /etc/passwd | wc -l
//                ^-redirect output in input


//lsof -np <pid> show streams info
// (descripor num)> redirect stream (&1) &stream num
