#ifndef WALLET_H
  #define WALLET_H

  #define USD_S "USD"
  #define RS_S  "R$"
  #define BTC_S "BTC"
  #define ETH_S "ETH"
  #define MAX_COINS 4

  #include <stdint.h>

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
    char szIdPbc[65];
    char szIdPvd[65];
    STASSETBALANCE astAtivos[4];

  }STWALLET, *PSWALLET;

  PSWALLET psCreateWallet(char szIdPbc[65], char szIdPvd[65]);
  void vLerDados         (const PSWALLET Dono);

#endif