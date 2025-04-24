#include <windows.h>

int putchar(int c) {  
    DWORD written;  
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), &c, 1, &written, NULL);  
    return (written == 1) ? (unsigned char)c : -1;  
} 

#define TAPE_SIZE 100

#ifndef REALESE
#define DEBUG
#define TRANSLATE
#endif

#ifdef TRANSLATE
void translateSingleToBrainFuck(char *code)
{
    char table[] = {'>','<','+','-','.',',','[',']'};
    unsigned char count = 0;
    putchar('\n');
    for (unsigned char pc = 0; code[pc]; pc++) {
        if (code[pc] == 's')
            putchar(table[count % 8]);
        count++;
    }
}
#endif

int main(int argc, char *argv[]) 
{
    unsigned char tape[TAPE_SIZE] = {0};
    unsigned char* ptr = tape;
    
    if (argc < 2)
        return 1;

    char *code = argv[1];
    char *input = (argc > 2) ? argv[2] : "";

#ifdef TRANSLATE  
    translateSingleToBrainFuck(code);
#endif

    putchar('\n');
    unsigned char count = 0;
    for (unsigned char pc = 0; code[pc]; pc++) {
        if (code[pc] == 's')
        {
            switch (count % 8) {
                case 0: if (ptr - tape + 1 >= TAPE_SIZE) ptr = tape; else ++ptr; break;
                case 1: if (ptr - tape - 1 < 0) ptr = tape + TAPE_SIZE - 1; else --ptr; break;
                case 2: ++*ptr; break;
                case 3: --*ptr; break;
                case 4: putchar(*ptr); break;
                case 5: *ptr = *input ? *(input++) : 0; break;
                case 6:
                    if (*ptr == 0) {
                        unsigned char depth = 1;
                        while (depth && code[++pc]) {
                            ++count;
                            if (code[pc] == 's') {
                                if (count % 8 == 6) depth++;
                                if (count % 8 == 7) depth--;
                            }
                        }
                    }
                    break;
                case 7:
                    if (*ptr != 0) {
                        unsigned char depth = 1;
                        while (depth && pc > 0) {
                            --pc;
                            --count;                
                            if (code[pc] == 's') {
                                if (count % 8 == 7) depth++;
                                if (count % 8 == 6) depth--;
                            }
                        }
                        --pc;   
                        continue;
                    }
                    break;
            }
        }            
        ++count;
    }
#ifdef DEBUG  
    for (int i = 0; i < 100; ++i)
        putchar(tape[i]);
#endif
}