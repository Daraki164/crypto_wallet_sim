
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"

static FILE *pfLog = NULL;

static void vGet_Time(char *szTexto, size_t tamanho)
{
    time_t t = time(NULL);
    struct tm *info = localtime(&t);

    if (info == NULL) {
        snprintf(szTexto, tamanho, "[data indisponivel]");
        return;
    }

    snprintf(
        szTexto,
        tamanho,
        "[%02d/%02d/%04d %02d:%02d:%02d]",
        info->tm_mday,
        info->tm_mon + 1,
        info->tm_year + 1900,
        info->tm_hour,
        info->tm_min,
        info->tm_sec
    );
}

void vTrace_Init(void)
{
    pfLog = fopen(LOG, "a");

    if (pfLog == NULL)
        perror("Erro ao abrir log");
}

void vTrace_Log(
    const char *szFile,
    int iLine,
    const char *szFunc,
    const char *szFmt,
    ...
)
{
    if (pfLog == NULL)
        return;

    char szHora[64];
    char szMsg[1024];

    vGet_Time(szHora, sizeof(szHora));

    va_list args;
    va_start(args, szFmt);
    vsnprintf(szMsg, sizeof(szMsg), szFmt, args);
    va_end(args);

    fprintf(
        pfLog,
        "%s [%s:%d | %s] %s\n",
        szHora,
        szFile,
        iLine,
        szFunc,
        szMsg
    );

    fflush(pfLog);
}

void vTrace_Close(void)
{
    if (pfLog != NULL) {
        fclose(pfLog);
        pfLog = NULL;
    }
}
