#include <cassert>
#include <cstdio>
#include <sys/mman.h>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <unistd.h>

#define SECRET_PROLOGUE __attribute__((section("secret.a")))
#define SECRET __attribute__((section("secret.b")))
#define SECRET_EPILOGUE __attribute__((section("secret.c")))

SECRET_PROLOGUE void secret_start(){};

SECRET void increase(char* buff, int size)
{
    for(int i = 0; i < size; ++i){
        buff[i] += 1;
    }
}

SECRET_EPILOGUE void secret_end(){};

const int KEY = 3;

void decrypt(size_t start_addr, size_t end_addr)
{
    for(size_t addr = start_addr; addr < end_addr; ++addr)
    {
        *(char*)(addr) ^= KEY;
    }
}

int main(int argc, char** argv)
{
//    assert(argc > 1);
//
//    //  Find page size for this system.
//    size_t pagesize = sysconf(_SC_PAGESIZE);
//
//    //  Calculate start and end addresses for the write.
//    auto start = (uintptr_t) &secret_start;
//    auto end = (uintptr_t) &secret_end;
//
//    //  Calculate start of page for mprotect.
//    uintptr_t pagestart = start & -pagesize;
//
//    if (mprotect((void*)pagestart, end - pagestart, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
//        decrypt(start - 1, end);
//    }
//    else {
//        printf("failed! %s",strerror(errno));
//        return 1;
//    }
//    increase(argv[1], 4);
//    printf("%s", argv[1]);
    int a = 'a';
    printf("%s", argv[1]);
    if(argv[1][0] > a){
        a = static_cast<unsigned char>(argv[1][0]);
    }
    return a;
}