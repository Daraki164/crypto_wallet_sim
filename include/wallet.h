#ifndef WALLET_H
  #define WALLET_H

  #define USD_S "USD"
  #define RS_S  "R$"
  #define BTC_S "BTC"
  #define ETH_S "ETH"
  #define MAX_COINS 4
  #define MAX_LENGTH 128

  #include <stdint.h>
  #include <stdio.h>
  #include <hash.h>

  typedef enum{
    DOLAR = 0,
    REAL, 
    BTC, 
    ETH  
  }Coins;

  typedef struct{
    uint8_t iCoin;
    uint64_t iQuant;
    char szSigla[8];

  }STASSETBALANCE, *PSASSETBALANCE;

  typedef struct{
    char szIdPbc[MAX_LENGTH];
    char szIdPvd[MAX_LENGTH];
    STASSETBALANCE astAtivos[4];

  }STWALLET, *PSWALLET;

  typedef struct{
    char szNome[MAX_LENGTH];
    PSWALLET wallet;
    FILE *fHistorico;
    unsigned char szSenhaSalt[SALT_LEN];
    unsigned char szSenhaHash[HASH_LEN];
  }STUSER, *PSUSER;

  PSWALLET psCreateWallet();
  PSUSER psCreateUser    (char *szNome, char *szSenha);
  void vLerDados         (const PSWALLET Dono);
  void vFreeUser         (PSUSER User);

#endif