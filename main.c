#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Type.h"
#include "ttf.h"

static void help();
static bool check(IN const char *pcstr);

int main(int argc, char *argv[])
{
    unsigned int auiBuf[4];    
    
    if(5 != argc)
    {
        help();
        return 0;
    }    
    
    unsigned int uiCount;
    for(uiCount = 1; uiCount < 5; uiCount++)
    {
        if(false == check(argv[uiCount]))
        {
            help();
            return 0;
        }
        
        unsigned int uitmp = atoi(argv[uiCount]);
        if(uitmp < 1 || uitmp > 13)
        {
            help();
            return 0;
        }
        
        auiBuf[uiCount-1] = uitmp;
    }
    
    initNumBuf(auiBuf[0], auiBuf[1], auiBuf[2], auiBuf[3]);
    initSymBuf();
    calculate();
    return 0;
}

static void help()
{
    printf("usage: ttf num1 num2 num3 num4\n");
    printf("number should be between 1 and 13\n");
    return;
}

static bool check(IN const char *pcstr)
{
    assert(NULL != pcstr);
    
    bool bret = true;
    
    unsigned int uilen = strlen(pcstr);
    if(uilen < 1 || uilen >= 3)
    {
        return false;
    }
    
    unsigned int uiCount;
    for(uiCount = 0; uiCount < uilen; uiCount++)
    {
        if(false == isdigit(pcstr[uiCount]))
        {
            bret = false;
            break;
        }
    }
    
    return bret;
}
