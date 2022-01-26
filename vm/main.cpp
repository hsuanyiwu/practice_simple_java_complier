
#include <stdio.h>
#include <stdlib.h>

int ip,sp,fp;
int temp = 10;
int stack[1024];

enum
{
    HALT,
    ICONST,
    PRINT,

    IADD,
    ISUB,
    IMUL,

    ILT,
    IEQ,
    BRT,
    BRF,

    ILOAD,
    CALL,
    RET,
};

struct opcode_info {
    const char* name;
    int size;
};

opcode_info opcode_infos [] = {
    { "halt", 1 },
    { "iconst", 2 },
    { "print", 1 },

    { "iadd", 1 },
    { "isub", 1 },
    { "imul", 1 },

    { "ilt", 1 },
    { "ieq", 1 },
    { "brt", 1 },
    { "brf", 1},

    { "iload", 2 },
    { "call", 3 },
    { "ret", 1 },
};

#define S_PUSH(x) stack[++sp] = x
#define S_POP() stack[sp--];

void trace(const int* code)
{
    opcode_info *info = &opcode_infos[code[ip]];
    printf("%04d:",ip);
    printf("\t%s", info->name);

    printf("\t");
    for(int i=1; i<info->size; ++i)
        printf(" %d",code[ip+i]);

    printf("\t[ ");
    for(int i=0; i<=sp; ++i)
        printf("%d ",stack[i]);
    printf("]");

    printf("\n");
}

void run_cpu(int* code)
{
    ip = 0;
    sp = fp = -1;
    fp = 0;

    int val,a,b,n,addr,offset;

    while(*code)
    {
        int opcode = code[ip];
        trace(code);
        ++ip;

        switch(opcode)
        {
        case HALT:
            return;
        // iconst,val
        case ICONST:
            val = code[ip++];
            S_PUSH(val);
            break;
        case PRINT:
            val = S_POP();
            printf("%d\n",val);
            break;

        case IADD:
            b = S_POP();
            a = S_POP();
            val = a+b;
            S_PUSH(val);
            break;
        case ISUB:
            b = S_POP();
            a = S_POP();
            val = a-b;
            S_PUSH(val);
            break;
        case IMUL:
            b = S_POP();
            a = S_POP();
            val = a*b;
            S_PUSH(val);
            break;

        case ILT:
            b = S_POP();
            a = S_POP();
            val = a < b;
            S_PUSH(val);
            break;
        case IEQ:
            b = S_POP();
            a = S_POP();
            val = a == b;
            S_PUSH(val);
            break;
        case BRT:
            addr = code[ip++];
            val = S_POP();
            if(val!=0)
                ip = addr;
            break;
        case BRF:
            addr = code[ip++];
            val = S_POP();
            if(val==0)
                ip = addr;
            break;

        // load,offset
        case ILOAD:
            offset = code[ip++];
            val = stack[fp+offset];
            S_PUSH(val);
            break;

        // call,argc,addr
        case CALL:
            n = code[ip++];
            addr = code[ip++];
            S_PUSH(n);
            S_PUSH(ip);
            S_PUSH(fp);
            fp = sp;
            ip = addr;
            break;

        case RET:
            val = S_POP();
            sp = fp;
            fp = S_POP();
            ip = S_POP();
            n = S_POP();
            sp -= n;
            S_PUSH(val);
            break;
        }
    }
}


int main(int argc, char** argv)
{
    // print 100+200
    int code_add[] = {
        ICONST, 100,
        ICONST,200,
        IADD,
        PRINT,
        HALT,
    };

    // function f(){ return 10 }
    // print f()
    int code_f[] = {
        CALL,0,5,       // 0
        PRINT,
        HALT,           // 3
        ICONST,10,
        RET,
    };

    // function f(a){ print a+10 }
    // f(100)
    int code_f2[] = {
        ICONST,100, // 0
        CALL,1,6,   // 2
        HALT,       // 5
        ILOAD,-3,   // 6
        ICONST,10,
        IADD,
        PRINT,
        ICONST,0,
        RET,
    };

    /*function fact(x){
        if(x < 2)
            return 1;
        return x * fact(x-1);
    }
    print fact(4)
    */

    int factorial[] = {
        ICONST,2,   // 0
        CALL,1,7,   // 2
        PRINT,      // 5
        HALT,
        ILOAD,-3,   // 7
        ICONST,2,
        ILT,
        BRF,17,     // 12
        ICONST,1,
        RET,
        ILOAD,-3,
        ILOAD,-3,
        ICONST,1,
        ISUB,
        CALL,1,7,
        IMUL,
        RET,
    };

    run_cpu(factorial);

    return 0;
}