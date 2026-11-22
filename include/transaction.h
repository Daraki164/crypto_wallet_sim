#ifndef TRANSACTION_H
  #define TRANSACTION_H

  #include <stdint.h>
  #include <time.h>
  #include <wallet.h>
  #include <inttypes.h>

  #define SEQ_FILE "history/.seq_transacao"
  #define SEQ_TMP  "history/.seq_transacao.tmp"


  typedef enum {
    DEPOSITO = 0,
    TRANSFERENCIA
  }TIPO_TRANSACAO;

  typedef enum {
    TRANSACAO_OK = 0,
    TRANSACAO_ERRO_PONTEIRO,
    TRANSACAO_ERRO_ATIVO,
    TRANSACAO_ERRO_VALOR,
    TRANSACAO_ERRO_SALDO,
    TRANSACAO_ERRO_MESMA_CARTEIRA,
    TRANSACAO_ERRO_HISTORICO
  }STATUS_TRANSACAO;

  typedef struct {
    uint64_t       iId;
    TIPO_TRANSACAO eTipo;
    uint8_t        iCoin;
    uint64_t       iValor;
    char           szOrigem[MAX_LENGTH];
    char           szDestino[MAX_LENGTH];
    time_t         tTimestamp;
  }STTRANSACTION, *PSTRANSACTION;

  PSTRANSACTION psCreateTransaction(
    TIPO_TRANSACAO eTipo,
    uint8_t eCoin,
    uint64_t iValor,
    const char *szOrigem,
    const char *szDestino
  );

  void vFreeTransaction        (PSTRANSACTION Transacao);
  const char *szStatusTransacao(STATUS_TRANSACAO eStatus);
  int bProximoIdTransacao      (uint64_t *pId);

#endif