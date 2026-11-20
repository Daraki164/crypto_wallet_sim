#include <wallet.h>
#include <log.h>
#include <stdlib.h>
#include <history.h>




int main(){
  vTrace_Init();
  PSUSER daraki = psCreateUser("daraki", "daraki123");
  if (daraki == NULL) {
    vTrace_Close();
    return 1;
  }

  vLerDados(daraki->wallet);


  FILE *fHistorico = fCreateHistory("daraki");
  if (fHistorico == NULL) {
    vLog("erro ao abrir historico");
    vFreeUser(daraki);
    vTrace_Close();
    return 1;
}

  fprintf(fHistorico, "teste1\n");
  fclose(fHistorico);



  free(daraki);
  vTrace_Close();
  return 0;
}