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

  typedef enum eCoins{
    DOLAR = 0,
    REAL, 
    BTC, 
    ETH  
  }Coins;

  typedef struct STRUCT_BALANCE{
    uint8_t iCoin;
    uint64_t iQuant;
    char szSigla[8];

  }STRUCT_BALANCE, *PSTRUCT_BALANCE;

  typedef struct STRUCT_WALLET{
    char szIdPbc[MAX_LENGTH];
    char szIdPvd[MAX_LENGTH];
    STRUCT_BALANCE astAtivos[4];

  }STRUCT_WALLET, *PSTRUCT_WALLET;

  typedef struct STRUCT_USER{
    char szNome[MAX_LENGTH];
    PSTRUCT_WALLET pstWallet;
    FILE *fHistorico;
    unsigned char szSenhaSalt[SALT_LEN];
    unsigned char szSenhaHash[HASH_LEN];
  }STRUCT_USER, *PSTRUCT_USER;

  PSTRUCT_WALLET pstCreateWallet();
  PSTRUCT_USER pstCreateUser    (char *szNome, char *szSenha);
  void vLerDados         (const PSTRUCT_WALLET pstDono);
  void vFreeUser         (PSTRUCT_USER pstUser);

#endif