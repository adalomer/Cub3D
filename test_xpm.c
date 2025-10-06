#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int fd = open("textures/simple.xpm", O_RDONLY);
    if (fd == -1) {
        printf("Failed to open file\n");
        return 1;
    }
    printf("File opened successfully, fd=%d\n", fd);
    
    int size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        printf("Failed to get file size\n");
        close(fd);
        return 1;
    }
    printf("File size: %d bytes\n", size);
    
    char *ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Failed to mmap\n");
        close(fd);
        return 1;
    }
    printf("mmap successful\n");
    printf("First 100 chars: %.100s\n", ptr);
    
    munmap(ptr, size);
    close(fd);
    return 0;
}
