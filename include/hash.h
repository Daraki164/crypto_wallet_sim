#ifndef HASH_H
  #define HASH_H

  #include <stddef.h>

  #define SALT_LEN 16
  #define HASH_LEN 32
  #define ITERACOES 200000
  #define HEX_SALT_LEN (SALT_LEN * 2 + 1)
  #define HEX_HASH_LEN (HASH_LEN * 2 + 1)

  int  bGerarHashSenha (
    const char *szSenha,
    unsigned char pSalt[SALT_LEN],
    unsigned char pHash[HASH_LEN]
  );

  int  bVerificarSenha (
    const char *szSenha,
    const unsigned char pSalt[SALT_LEN],
    const unsigned char pHash[HASH_LEN]
  );

  void vHexEncode(const unsigned char *pIn, size_t n, char *szOut);
  int  bHexDecode(const char *szIn, unsigned char *pOut, size_t n);

#endif