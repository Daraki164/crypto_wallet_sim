#include <wallet.h>

int main(){
  PSWALLET daraki = psCreateWallet("chavepubica111", "chaveprivada222");
  vLerDados(daraki);
  return 0;
}