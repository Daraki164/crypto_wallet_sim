
#ifndef LOG_H
#define LOG_H

#define LOG "wallet.log"

void vTrace_Init(void);

void vTrace_Log(
    const char *szFile,
    int iLine,
    const char *szFunc,
    const char *szFmt,
    ...
);

void vTrace_Close(void);

#define vLog(...) \
    vTrace_Log(__FILE__, __LINE__, __func__, __VA_ARGS__)

#endif
