#include <key.h>
#include <hash.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

int bGerarParChaves(char szPbc[KEY_HEX_LEN], char szPvd[KEY_HEX_LEN]){
  unsigned char ucPvd[KEY_BYTES];
  unsigned char ucPbc[KEY_BYTES];

  if (RAND_bytes(ucPvd, KEY_BYTES) != 1)
      return 0;

  SHA256(ucPvd, KEY_BYTES, ucPbc);

  vHexEncode(ucPvd, KEY_BYTES, szPvd);
  vHexEncode(ucPbc, KEY_BYTES, szPbc);

  return 1;
}
