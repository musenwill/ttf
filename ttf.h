#ifndef _TTF_H_
#define _TTF_H_

#define NUMBER  4
#define NUMBUF  24
#define SYMBOL  3
#define SYMBUF  64

PUBLIC void initSymBuf();
PUBLIC void printSymBuf();
PUBLIC void initNumBuf(IN unsigned int uiNum1, IN unsigned int uiNum2, IN unsigned int uiNum3, IN unsigned int uiNum4);
PUBLIC void printNumBuf();
PUBLIC void calculate();

#endif
