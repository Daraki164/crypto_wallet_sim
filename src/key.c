#include <key.h>
#include <hash.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

int bGerarParChaves(char szPbc[KEY_HEX_LEN], char szPvd[KEY_HEX_LEN]){
  unsigned char pvd[KEY_BYTES];
  unsigned char pbc[KEY_BYTES];

  if (RAND_bytes(pvd, KEY_BYTES) != 1)
      return 0;

  SHA256(pvd, KEY_BYTES, pbc);

  vHexEncode(pvd, KEY_BYTES, szPvd);
  vHexEncode(pbc, KEY_BYTES, szPbc);

  return 1;
}
