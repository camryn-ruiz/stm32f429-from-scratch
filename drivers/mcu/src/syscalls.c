#include <sys/types.h>
#include <sys/stat.h>

register char* stack_ptr asm("sp");

caddr_t _sbrk(int incr) {
    extern char _end; // defined by linker script
    static char *heap_end;
    char *prev_heap;

    if (!heap_end) heap_end = &_end;
    prev_heap = heap_end;
    heap_end += incr;
    return (caddr_t)prev_heap;
}

int _write(int file, char *ptr, int len) {
    // TODO: Send chars to UART
    return len;
}

int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
int _kill(int pid, int sig) { return -1; }
int _getpid(void) { return 1; }