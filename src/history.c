#include <history.h>
#include <stdlib.h>
#include <string.h>
#include <log.h>
#include <wallet.h>

FILE *pfCreateHistory(char *szNome){
  char szText[MAX_LENGTH];
  if(strlen(szNome) + strlen("history/.txt") >= MAX_LENGTH){
    vLog("nome muito grade");

    return NULL;
  }

  snprintf(szText, MAX_LENGTH, "history/%s.txt", szNome);
  
  FILE *fHistory = fopen(szText, "a+");

  return fHistory;
}