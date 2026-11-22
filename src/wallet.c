#include <wallet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <log.h>
#include <history.h>
#include <key.h>

void vFreeUser(PSTRUCT_USER pstUser){
  free(pstUser->pstWallet);
  free(pstUser);
}

PSTRUCT_USER pstCreateUser(char *szNome, char *szSenha){
  PSTRUCT_USER pstUser = calloc(1, sizeof(STRUCT_USER));

  if(pstUser == NULL){
    vLog("erro de alocação, pstUser == NULL");
    return NULL;
  }

  strncpy(pstUser->szNome, szNome, sizeof(pstUser->szNome)-1);

  if(!bGerarHashSenha(szSenha, pstUser->szSenhaSalt, pstUser->szSenhaHash)){
    vLog("erro ao gerar hash da senha");
    free(pstUser);
    return NULL;
  }

  pstUser->pstWallet = pstCreateWallet();

  if(pstUser->pstWallet == NULL){
    vLog("erro ao criar pstWallet");
    free(pstUser);
    return NULL;
  }

  pstUser->fHistorico = pfCreateHistory(pstUser->szNome);

  return pstUser;
}

void vLerDados(const PSTRUCT_WALLET pstDono){
  printf(
    "Chave Publica: %s\n",
    pstDono->szIdPbc
  );

  int ii;
  for(ii = 0; ii < MAX_COINS; ii++){
    printf("%ld de %s\n", pstDono->astAtivos[ii].iQuant, pstDono->astAtivos[ii].szSigla);
  }
}


PSTRUCT_WALLET pstCreateWallet(){
  PSTRUCT_WALLET pstWallet = calloc(1, sizeof(STRUCT_WALLET));

  if(pstWallet == NULL){
    vLog("erro de alocação, pstWallet == NULL");
    return NULL;
  }

  if (!bGerarParChaves(pstWallet->szIdPbc, pstWallet->szIdPvd)){
    vLog("erro ao gerar par de chaves");
    free(pstWallet);
    return NULL;
  }

  int ii;
  for(ii = 0; ii < MAX_COINS; ii++){
    switch(ii){
      case DOLAR:
        strncpy(pstWallet->astAtivos[ii].szSigla, USD_S, sizeof(pstWallet->astAtivos[ii].szSigla));
        pstWallet->astAtivos[ii].iCoin = DOLAR;
        pstWallet->astAtivos[ii].iQuant = 1000;
        break;

      case REAL:
        strncpy(pstWallet->astAtivos[ii].szSigla, RS_S, sizeof(pstWallet->astAtivos[ii].szSigla)-1);
        pstWallet->astAtivos[ii].iCoin = REAL;
        pstWallet->astAtivos[ii].iQuant = 1000;
        break;

      case BTC:
        strncpy(pstWallet->astAtivos[ii].szSigla, BTC_S, sizeof(pstWallet->astAtivos[ii].szSigla)-1);
        pstWallet->astAtivos[ii].iCoin = BTC;
        pstWallet->astAtivos[ii].iQuant = 1000;
        break;

      case ETH:
        strncpy(pstWallet->astAtivos[ii].szSigla, ETH_S, sizeof(pstWallet->astAtivos[ii].szSigla)-1);
        pstWallet->astAtivos[ii].iCoin = ETH;
        pstWallet->astAtivos[ii].iQuant = 1000;
        break;
    }
  }

  return pstWallet;

}