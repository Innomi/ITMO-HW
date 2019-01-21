#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define SIZE 4096

void* alloc_writable_memory(size_t size)
{
    void* ptr = mmap(0, size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }
    return ptr;
}

int free_memory(void* ptr, size_t size)
{
    if (munmap(ptr, size) == -1)
    {
        perror("munmap");
        return -1;
    }
    return 0;
}

int switch_memory_prot(void* ptr, size_t size, int prot)
{
    if (mprotect(ptr, size, PROT_READ | prot) == -1)
    {
        perror("mprotect");
        return -1;
    }
    return 0;
}

int main()
{
    void* memory = alloc_writable_memory(SIZE);
    unsigned char code[] =
    {
        0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00, //mov $0x01, %rdi
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00, //mov $0x01, %rax
        0x48, 0x8d, 0x35, 0x00, 0x00, 0x00, 0x00, //lea (%rip), %rsi
        0x48, 0x83, 0xc6, 0x21,                   //add $0x21, %rsi
        0x48, 0xc7, 0xc2, 0x0e, 0x00, 0x00, 0x00, //mov $0x0e, %rdx
        0x0f, 0x05,                               //syscall
        0x48, 0x29, 0xc2,                         //sub %rax, %rdx
        0x48, 0x01, 0xc6,                         //add %rax, %rsi
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00, //mov $0x01, %rax
        0x48, 0x83, 0xfa, 0x00,                   //cmp $0x00, %rdx
        0x75, 0xeb,                               //jne <syscall>
        0xc3,                                     //ret
        0x48, 0x65, 0x6c, 0x6c, 0x6f,             //Hello
        0x2c,                                     //,
        0x20,                                     //\s
        0x77, 0x6f, 0x72, 0x6c, 0x64,             //world
        0x21,                                     //!
        0x0a                                      //\n
    };
    memcpy(memory, code, sizeof(code));
    void (*func)() = memory;

    char c;
    char buf[128];
    unsigned char* len = memory + 28;
    unsigned char word_len = 0;
    char* last_word = memory + sizeof(code) - 7;

    printf("Print some names and get greetings!\n");
    printf("Symbols after 126th in each name will be ignored. ¯\\_(ツ)_/¯\n");

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            continue;
        }
        buf[0] = c;
        word_len = 1;
        while ((c = getchar()) != '\n')
        {
            if (c == EOF || word_len > 125)
            {
                continue;
            }
            buf[word_len] = c;
            ++word_len;
        }
        buf[word_len] = '!';
        ++word_len;
        buf[word_len] = '\n';
        ++word_len;
        memcpy(last_word, buf, word_len);
        *len = 7 + word_len;

        switch_memory_prot(memory, SIZE, PROT_EXEC);
        func();
        switch_memory_prot(memory, SIZE, PROT_WRITE);
    }

    free_memory(memory, SIZE);
    return 0;
}
