#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Type.h"
#include "ttf.h"

static unsigned int g_auiNum[NUMBUF][NUMBER];
static char         g_szSym[SYMBUF][SYMBOL];
static unsigned int g_uiNumTotal = 0;

PRIVATE void allOrder(INOUT unsigned int *puiBuf, IN unsigned int uiIndex);
PRIVATE void swap(INOUT unsigned int *puiBuf, IN unsigned int uipt1, IN unsigned int uipt2);
PRIVATE void printRpf1(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void printRpf2(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void printRpf3(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void printRpf4(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void printRpf5(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void calc1(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void calc2(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void calc3(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void calc4(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE void calc5(IN unsigned int *puiBuf, IN char *pcBuf);
PRIVATE float binaryCalc(IN float fnum1, IN float fnum2, IN char cc);
PRIVATE bool is24(IN float fnum);

PUBLIC void initSymBuf()
{
    char szSymbol[4] = {'+','-','*','/'};
    
    unsigned int uiSymCount = 0;
    unsigned int uiFirst;
    for(uiFirst = 0; uiFirst < 4; uiFirst++)
    {
        unsigned int uiSecond;
        for(uiSecond = 0; uiSecond < 4; uiSecond++)
        {
            unsigned int uiThird;
            for(uiThird = 0; uiThird < 4; uiThird++)
            {
                g_szSym[uiSymCount][0] = szSymbol[uiFirst];
                g_szSym[uiSymCount][1] = szSymbol[uiSecond];
                g_szSym[uiSymCount][2] = szSymbol[uiThird];
                uiSymCount++;
            }
        }
    }
}

PUBLIC void printSymBuf()
{
    unsigned int uiCount;
    for(uiCount = 0; uiCount < SYMBUF; uiCount++)
    {
        printf("%c %c %c\n", g_szSym[uiCount][0], g_szSym[uiCount][1], g_szSym[uiCount][2]);
    }
}

PUBLIC void initNumBuf(IN unsigned int uiNum1, IN unsigned int uiNum2, IN unsigned int uiNum3, IN unsigned int uiNum4)
{
    assert(uiNum1 >= 1 && uiNum1 <= 13);
    assert(uiNum2 >= 1 && uiNum1 <= 13);
    assert(uiNum3 >= 1 && uiNum1 <= 13);
    assert(uiNum4 >= 1 && uiNum1 <= 13);
    
    g_uiNumTotal = 0;
    unsigned int auiNumber[NUMBER] = {uiNum1, uiNum2, uiNum3, uiNum4};
    allOrder(auiNumber, 0);
    
    return;
}

PUBLIC void printNumBuf()
{
    unsigned int uiCount;
    for(uiCount = 0; uiCount < g_uiNumTotal; uiCount++)
    {
        printf("%2d %2d %2d %2d\n", g_auiNum[uiCount][0], g_auiNum[uiCount][1], g_auiNum[uiCount][2], g_auiNum[uiCount][3]);
    }
    
    return;
}

PUBLIC void calculate()
{
    unsigned int uinumIndex;
    for(uinumIndex = 0; uinumIndex < g_uiNumTotal; uinumIndex++)
    {
        unsigned int uisymIndex;
        for(uisymIndex = 0; uisymIndex < SYMBUF; uisymIndex++)
        {
            calc1(g_auiNum[uinumIndex], g_szSym[uisymIndex]);
            calc2(g_auiNum[uinumIndex], g_szSym[uisymIndex]);
            calc3(g_auiNum[uinumIndex], g_szSym[uisymIndex]);
            calc4(g_auiNum[uinumIndex], g_szSym[uisymIndex]);
            calc5(g_auiNum[uinumIndex], g_szSym[uisymIndex]);
        }
    }
}



PRIVATE void allOrder(INOUT unsigned int *puiBuf, IN unsigned int uiIndex)
{
    assert(NULL != puiBuf);
    assert(uiIndex >= 0 && uiIndex < NUMBER);
    
    if(1 == NUMBER - uiIndex)
    {
        unsigned int uiCount;
        for(uiCount = 0; uiCount < NUMBER; uiCount++)
        {
            g_auiNum[g_uiNumTotal][uiCount] = puiBuf[uiCount];
        }
        g_uiNumTotal++;
        return;
    }
    
    unsigned int uiCount;
    for(uiCount = uiIndex; uiCount < NUMBER; uiCount++)
    {
        bool bContinueFlag = false;
        int icmpIndex;
        for(icmpIndex = uiCount-1; icmpIndex >= (int)uiIndex; icmpIndex--)
        {
            if(puiBuf[uiCount] == puiBuf[icmpIndex])
            {
                bContinueFlag = true;
                break;
            }
        }
        if(false != bContinueFlag)
        {
            continue;
        }
       
        swap(puiBuf, uiIndex, uiCount);
        allOrder(puiBuf, uiIndex+1);
        swap(puiBuf, uiIndex, uiCount);
    }
    
    return;
}

PRIVATE void swap(INOUT unsigned int *puiBuf, IN unsigned int uipt1, IN unsigned int uipt2)
{
    assert(NULL != puiBuf);
    assert(uipt1 < NUMBER && uipt2 < NUMBER);
    
    unsigned int uitmp = puiBuf[uipt1];
    puiBuf[uipt1] = puiBuf[uipt2];
    puiBuf[uipt2] = uitmp;
    
    return;   
}

PRIVATE void printRpf1(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    printf("24 = ((%2d %c %2d) %c %2d) %c %2d\n", 
            puiBuf[0], pcBuf[0], 
            puiBuf[1], pcBuf[1], 
            puiBuf[2], pcBuf[2],
            puiBuf[3]);
    return;
}

PRIVATE void printRpf2(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    printf("24 = (%2d %c %2d) %c (%2d %c %2d)\n", 
            puiBuf[0], pcBuf[0], 
            puiBuf[1], pcBuf[2], 
            puiBuf[2], pcBuf[1],
            puiBuf[3]);
    return;
}

PRIVATE void printRpf3(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    printf("24 = (%2d %c (%2d %c %2d)) %c %2d\n", 
            puiBuf[0], pcBuf[1], 
            puiBuf[1], pcBuf[0], 
            puiBuf[2], pcBuf[2],
            puiBuf[3]);
    return;
}

PRIVATE void printRpf4(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    printf("24 = %2d %c ((%2d %c %2d) %c %2d)\n", 
            puiBuf[0], pcBuf[2], 
            puiBuf[1], pcBuf[0], 
            puiBuf[2], pcBuf[1],
            puiBuf[3]);
    return;
}

PRIVATE void printRpf5(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    printf("24 = %2d %c (%2d %c (%2d %c %2d))\n", 
            puiBuf[0], pcBuf[2], 
            puiBuf[1], pcBuf[1], 
            puiBuf[2], pcBuf[0],
            puiBuf[3]);
    return;
}

PRIVATE void calc1(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    float fret;
    fret = binaryCalc(puiBuf[0], puiBuf[1], pcBuf[0]);
    fret = binaryCalc(fret, puiBuf[2], pcBuf[1]);
    fret = binaryCalc(fret, puiBuf[3], pcBuf[2]);
       
    if(false != is24(fret))
    {
        printRpf1(puiBuf, pcBuf);
    } 
    
    return;
}

PRIVATE void calc2(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    float fret, fret1, fret2;
    fret1 = binaryCalc(puiBuf[0], puiBuf[1], pcBuf[0]);
    fret2 = binaryCalc(puiBuf[2], puiBuf[3], pcBuf[1]);
    fret = binaryCalc(fret1, fret2, pcBuf[2]);
       
    if(false != is24(fret))
    {
        printRpf2(puiBuf, pcBuf);
    } 
    
    return;
}

PRIVATE void calc3(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    float fret;
    fret = binaryCalc(puiBuf[1], puiBuf[2], pcBuf[0]);
    fret = binaryCalc(puiBuf[0], fret, pcBuf[1]);
    fret = binaryCalc(fret, puiBuf[3], pcBuf[2]);
       
    if(false != is24(fret))
    {
        printRpf3(puiBuf, pcBuf);
    } 
    
    return;
}

PRIVATE void calc4(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    float fret;
    fret = binaryCalc(puiBuf[1], puiBuf[2], pcBuf[0]);
    fret = binaryCalc(fret, puiBuf[3], pcBuf[1]);
    fret = binaryCalc(puiBuf[0], fret, pcBuf[2]);
       
    if(false != is24(fret))
    {
        printRpf4(puiBuf, pcBuf);
    } 
    
    return;
}

PRIVATE void calc5(IN unsigned int *puiBuf, IN char *pcBuf)
{
    assert(NULL != puiBuf);
    assert(NULL != pcBuf);
    
    float fret;
    fret = binaryCalc(puiBuf[2], puiBuf[3], pcBuf[0]);
    fret = binaryCalc(puiBuf[1], fret, pcBuf[1]);
    fret = binaryCalc(puiBuf[0], fret, pcBuf[2]);
       
    if(false != is24(fret))
    {
        printRpf5(puiBuf, pcBuf);
    } 
    
    return;
}

PRIVATE float binaryCalc(IN float fnum1, IN float fnum2, IN char cc)
{
    
    switch(cc)
    {
        case '+':   return fnum1 + fnum2;
        case '-':   return fnum1 - fnum2;
        case '*':   return fnum1 * fnum2;
        case '/':  return fnum1 / fnum2;
        default:
        {
            assert(0);
        }
    }
    return 0;
}

PRIVATE bool is24(IN float fnum)
{
    if(23.9 < fnum && fnum < 24.1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


