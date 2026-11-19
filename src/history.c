#include <history.h>
#include <stdlib.h>
#include <string.h>
#include <log.h>

FILE *fCreateHistory(char *szNome){
  char *szText = calloc(128, sizeof(char));
  if(strlen(szNome) + strlen("history/.txt") >= sizeof(szText)){
    vLog("nome muito grade");
    free(szText);
    return NULL;
  }

  snprintf(szText, strlen(szNome), "history/%s.txt", szNome);
  
  FILE *fHistory = fopen(szText, "a+");

  free(szText);
  return fHistory;
}