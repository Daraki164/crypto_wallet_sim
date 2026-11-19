#include <wallet.h>
#include <log.h>
#include <stdlib.h>
#include <history.h>



int main(){
  vTrace_Init();
  PSUSER daraki = psCreateUser("daraki", "chavepubica111", "chaveprivada222");
  vLerDados(daraki->wallet);


  FILE *historico = fCreateHistory("daraki");
  historico = fopen("history/daraki", "a");
  fprintf(historico, "teste1\n");
  fclose(historico);



  free(daraki);
  vTrace_Close();
  return 0;
}