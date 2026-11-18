#include <wallet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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


PSWALLET psCreateWallet(char szIdPbc[64], char szIdPvd[64]){
  PSWALLET wallet = (PSWALLET)malloc(sizeof(STWALLET));
 

  strncpy(wallet->szIdPbc, szIdPbc, sizeof(wallet->szIdPbc)-1);
  strncpy(wallet->szIdPvd, szIdPvd, sizeof(wallet->szIdPvd)-1);

  int ii;
  for(ii = 0; ii < MAX_COINS; ii++){
    switch(ii){
      case DOLAR:
        strncpy(wallet->astAtivos[ii].szSigla, USD_S, sizeof(wallet->astAtivos[ii].szSigla));
        wallet->astAtivos[ii].iCoin = DOLAR;
        wallet->astAtivos[ii].iQuant = 0;
        break;
      case REAL:
        strncpy(wallet->astAtivos[ii].szSigla, RS_S, sizeof(wallet->astAtivos[ii].szSigla)-1);
        wallet->astAtivos[ii].iCoin = REAL;
        wallet->astAtivos[ii].iQuant = 0;
        break;
      case BTC:
        strncpy(wallet->astAtivos[ii].szSigla, BTC_S, sizeof(wallet->astAtivos[ii].szSigla)-1);
        wallet->astAtivos[ii].iCoin = BTC;
        wallet->astAtivos[ii].iQuant = 0;
        break;
      case ETH:
        strncpy(wallet->astAtivos[ii].szSigla, ETH_S, sizeof(wallet->astAtivos[ii].szSigla)-1);
        wallet->astAtivos[ii].iCoin = ETH;
        wallet->astAtivos[ii].iQuant = 0;
        break;
    }
  }

  return wallet;

}