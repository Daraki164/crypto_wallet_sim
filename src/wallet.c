#include <wallet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <log.h>
#include <history.h>
#include <key.h>

void vFreeUser(PSUSER User){
  free(User->wallet);
  free(User);
}

PSUSER psCreateUser(char *szNome, char *szSenha){
  PSUSER psUser = calloc(1, sizeof(STUSER));

  if(psUser == NULL){
    vLog("erro de alocação, psUser == NULL");
    return NULL;
  }

  strncpy(psUser->szNome, szNome, sizeof(psUser->szNome)-1);

  if (!bGerarHashSenha(szSenha, psUser->szSenhaSalt, psUser->szSenhaHash)){
    vLog("erro ao gerar hash da senha");
    free(psUser);
    return NULL;
  }

  psUser->wallet = psCreateWallet();

  if (psUser->wallet == NULL) {
    vLog("erro ao criar wallet");
    free(psUser);
    return NULL;
  }

  psUser->fHistorico = fCreateHistory(psUser->szNome);

  return psUser;
}

void vLerDados(const PSWALLET Dono){
  printf(
    "Chave Publica: %s\n",
    Dono->szIdPbc
  );

  int ii;
  for(ii = 0; ii < MAX_COINS; ii++){
    printf("%ld de %s\n", Dono->astAtivos[ii].iQuant, Dono->astAtivos[ii].szSigla);
  }
}


PSWALLET psCreateWallet(){
  PSWALLET wallet = calloc(1, sizeof(STWALLET));

  if(wallet == NULL){
    vLog("erro de alocação, wallet == NULL");
    return NULL;
  }

  if (!bGerarParChaves(wallet->szIdPbc, wallet->szIdPvd)){
    vLog("erro ao gerar par de chaves");
    free(wallet);
    return NULL;
  }

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