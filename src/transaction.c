#include <stdlib.h>
#include <transaction.h>
#include <time.h>
#include <string.h>


PSTRANSACTION psCreateTransaction(
    TIPO_TRANSACAO eTipo,
    uint8_t eCoin,
    uint64_t iValor,
    const char *szOrigem,
    const char *szDestino
){

  if (szOrigem == NULL || szDestino == NULL)
    return NULL;

  if (eCoin < 0 || eCoin >= MAX_COINS)
    return NULL;


  PSTRANSACTION t = calloc(1, sizeof(STTRANSACTION));
  if (t == NULL) return NULL;

  if (!bProximoIdTransacao(&t->iId)){
      free(t);
      return NULL;
  }

  t->eTipo = eTipo;
  t->iCoin = eCoin;
  t->iValor = iValor;
  t->tTimestamp = time(NULL);

  strncpy(t->szOrigem, szOrigem, sizeof(t->szOrigem) - 1);
  t->szOrigem[sizeof(t->szOrigem) - 1] = '\0';

  strncpy(t->szDestino, szDestino, sizeof(t->szDestino) - 1);
  t->szDestino[sizeof(t->szDestino) - 1] = '\0';

  return t;
}

int bProximoIdTransacao(uint64_t *pId){
  uint64_t uId = 0;

  FILE *f = fopen(SEQ_FILE, "r");
  if (f != NULL) {
    if (fscanf(f, "%" SCNu64, &uId) != 1)
        uId = 0;
    fclose(f);
  }

  uId++;

  f = fopen(SEQ_TMP, "w");
  if (f == NULL) return 0;

  fprintf(f, "%" PRIu64 "\n", uId);
  fflush(f);
  fclose(f);

  if (rename(SEQ_TMP, SEQ_FILE) != 0) {
    remove(SEQ_TMP);
    return 0;
  }

  *pId = uId;
  return 1;
}

void vFreeTransaction(PSTRANSACTION Transacao){
  free(Transacao);
}

const char *szStatusTransacao(STATUS_TRANSACAO eStatus){
  switch(eStatus){
    case TRANSACAO_OK:
      return "ok";

    case TRANSACAO_ERRO_VALOR:
      return "erro de valor";

    case TRANSACAO_ERRO_SALDO:
      return "saldo insuficiente";

    case TRANSACAO_ERRO_PONTEIRO:
      return "erro de ponteiro";

    case TRANSACAO_ERRO_MESMA_CARTEIRA:
      return "erro ao selecionar a mesma carteira";

    case TRANSACAO_ERRO_HISTORICO:
      return "erro ao registrar no historico";

    case TRANSACAO_ERRO_ATIVO:
      return "ativo inexistente";
  }
}