#include <wallet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <log.h>
#include <history.h>


PSUSER psCreateUser(char *szNome, char *szIdPbc, char *szIdPvd){
  PSUSER psUser = calloc(1, sizeof(STUSER));

  if(psUser == NULL){
    vLog("erro de alocação, psUser == NULL");
    return NULL;
  }

  strncpy(psUser->szNome, szNome, sizeof(psUser->szNome)-1);
  psUser->wallet = psCreateWallet(szIdPbc, szIdPvd);
  psUser->fHistorico = fCreateHistory(psUser->szNome);

  return psUser;
}

void vLerDados(const PSWALLET Dono){
  printf(
    "Chave Publica: %s\n"
    "Chave Privada: %s\n",
    Dono->szIdPbc,
    Dono->szIdPvd
  );

  int ii;
  for(ii = 0; ii < MAX_COINS; ii++){
    printf("%ld de %s\n", Dono->astAtivos[ii].iQuant, Dono->astAtivos[ii].szSigla);
  }
}


PSWALLET psCreateWallet(char *szIdPbc, char *szIdPvd){
  PSWALLET wallet = calloc(1, sizeof(STWALLET));

  if(wallet == NULL){
    vLog("erro de alocação, wallet == NULL");
    return NULL;
  }

  strncpy(wallet->szIdPbc, szIdPbc, sizeof(wallet->szIdPbc)-1);
  strncpy(wallet->szIdPvd, szIdPvd, sizeof(wallet->szIdPvd)-1);

  int ii;
  for(ii = 0; ii < MAX_COINS; ii++){
    switch(ii){
      case DOLAR:
        strncpy(wallet->astAtivos[ii].szSigla, USD_S, sizeof(wallet->astAtivos[ii].szSigla));
        wallet->astAtivos[ii].iCoin = DOLAR;
        wallet->astAtivos[ii].iQuant = 1000;
        break;

      case REAL:
        strncpy(wallet->astAtivos[ii].szSigla, RS_S, sizeof(wallet->astAtivos[ii].szSigla)-1);
        wallet->astAtivos[ii].iCoin = REAL;
        wallet->astAtivos[ii].iQuant = 1000;
        break;

      case BTC:
        strncpy(wallet->astAtivos[ii].szSigla, BTC_S, sizeof(wallet->astAtivos[ii].szSigla)-1);
        wallet->astAtivos[ii].iCoin = BTC;
        wallet->astAtivos[ii].iQuant = 1000;
        break;

      case ETH:
        strncpy(wallet->astAtivos[ii].szSigla, ETH_S, sizeof(wallet->astAtivos[ii].szSigla)-1);
        wallet->astAtivos[ii].iCoin = ETH;
        wallet->astAtivos[ii].iQuant = 1000;
        break;
    }
  }

  return wallet;

}