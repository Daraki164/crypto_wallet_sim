#ifndef KEY_H
  #define KEY_H

  #define KEY_BYTES 32
  #define KEY_HEX_LEN (KEY_BYTES * 2 + 1)

  int bGerarParChaves(char szPbc[KEY_HEX_LEN], char szPvd[KEY_HEX_LEN]);

#endif