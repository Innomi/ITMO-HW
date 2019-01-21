#include <dirent.h>       // Defines DT_* constants
#include <fcntl.h>        // Defines O_* constants
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>     // Defines structure for stat, fstat, lstat
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)
       
#define print_error(msg) \
        do { fprintf(stderr, msg); exit(EXIT_FAILURE); } while (0)

#define BUF_SIZE 1024
#define PATH_LEN 1024

struct linux_dirent
{
    ino_t          d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

typedef struct
{
    ino_t   inum;
    nlink_t nlinks;
    off_t   size;
    char*   exec_path;
    char*   name;
    char**  arge;
    char    size_option; //0 - undefined, '-' - less, '=' - equal, '+' - more
} Params;

void get_name(char* name, const char* path)
{
    size_t j = 0;
    for (size_t i = 0; path[i] != '\0' && i < PATH_LEN; ++i)
    {
        if (path[i] == '/')
        {
            j = 0;
            continue;
        }
        name[j] = path[i];
        ++j;
    }
    name[j] = '\0';
}

void exec(char* exec_path, char* arg, char** arge)
{
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        char* args[] = { exec_path, arg, NULL };
        execve(args[0], args, arge);
        handle_error("Execve");
    }
    else
    {
        if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("Fork");
        }
    }
}

unsigned int is_equal(const char* path, Params* prms)
{
    struct stat st;
    if (lstat(path, &st) < 0)
    {
        perror("Lstat");
        return 0;
    }
    if (prms->inum > 0 && prms->inum != st.st_ino)
    {
        return 0;
    }
    if (prms->nlinks > 0 && prms->nlinks != st.st_nlink)
    {
        return 0;
    }
    if (prms->size_option > 0)
    {
        switch (prms->size_option)
        {
            case '-' :
            {
                if (prms->size <= st.st_size)
                {
                    return 0;
                }
            }
            case '=' :
            {
                if (prms->size != st.st_size)
                {
                    return 0;
                }
            }
            case '+' :
            {
                if (prms->size >= st.st_size)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void output(char* path, char* name, Params* prms)
{
    if (is_equal(path, prms)
     && (prms->name == NULL
     || !strcmp(prms->name, name)))
    {
        if (prms->exec_path == NULL)
        {
            printf("%s\n", path);
        }
        else
        {
            exec(prms->exec_path, path, prms->arge);
        }
    }
}

void search(char* dir, Params* prms)
{
    char buf[BUF_SIZE];
    struct linux_dirent* d;
    int bpos, nread, fd;
    char path[PATH_LEN];
    char d_type;
    fd = open(dir, O_RDONLY | O_DIRECTORY | O_NOFOLLOW);
    if (fd == -1)
    {
        if (errno != ELOOP && errno != ENOTDIR)
        {
            fprintf(stderr, "Open: ");
            perror(dir);
        }
        return;
    }
    
    if (dir[strlen(dir) - 1] == '/')
    {
        dir[strlen(dir) - 1] = '\0';
    }
    
    while (1)
    {
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == -1)
        {
            perror("Getdents");
            return;
        }

        if (nread == 0)
        {
            break;
        }

        for (bpos = 0; bpos < nread; )
        {
            d = (struct linux_dirent*)(buf + bpos);
            d_type = *(buf + bpos + d->d_reclen - 1);
            strcpy(path, dir);
            strcat(path, "/");
            strcat(path, d->d_name);
            if (strcmp(d->d_name, "..") && strcmp(d->d_name, "."))
            {
                output(path, d->d_name, prms);
                if (d_type == DT_DIR)
                {
                    search(path, prms);
                }
            }
            bpos += d->d_reclen;
        }
    }
    close(fd);
}

//                 WARNING!!!
// Wrong arguments can lead to undefined behaviour.
// Seriously, Earth can be destroyed, 
// but more important that your cat can burn.

int main(int argc, char* argv[], char* arge[])
{
    if (argc < 2)
    {
       print_error("Wrong number of arguments\n");
    }
    
    Params prms = { 0, 0, 0, NULL, NULL, arge, 0 };
    
    const char wrong_args[] = "Invalid arguments\n";
    
    for (size_t i = 2; i < argc; i += 2)
    {
        if (argc == i + 1)
        {
            print_error(wrong_args);
        }
        
        if (!strcmp(argv[i], "-inum"))
        {
            prms.inum = (ino_t)atol(argv[i + 1]);
            continue;
        }
        if (!strcmp(argv[i], "-name"))
        {
            prms.name = argv[i + 1];
            continue;
        }
        if (!strcmp(argv[i], "-size"))
        {
            prms.size_option = argv[i + 1][0];
            if (prms.size_option != '-'
             && prms.size_option != '='
             && prms.size_option != '+')
            {
                print_error(wrong_args);
            }
            prms.size = (off_t)atol(argv[i + 1] + 1);
            continue;
        }
        if (!strcmp(argv[i], "-nlinks"))
        {
            prms.nlinks = (nlink_t)atol(argv[i + 1]);
            continue;
        }
        if (!strcmp(argv[i], "-exec"))
        {
            prms.exec_path = argv[i + 1];
            continue;
        }
        
        print_error(wrong_args);
    }
    
    char name[PATH_LEN];
    get_name(name, argv[1]);
    output(argv[1], name, &prms);
    
    search(argv[1], &prms);
    
    exit(EXIT_SUCCESS);
}
