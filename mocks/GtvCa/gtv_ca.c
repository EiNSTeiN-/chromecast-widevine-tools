#include <string.h>
#include "GtvCa/gtv_ca.h"

int gtv_ca_load_key_advance(struct OpenCrypto_Key **p_key, char *store, int store_size, int a4, int a5)
{
  printf("(mock) gtv_ca_load_key_advance p_key=%p store=%p store_size=%u a4=%u a5=%u\n", 
    *p_key, store, store_size, a4, a5);
  return 0;
}


int gtv_ca_sign_crt(struct OpenCrypto_Key *p_key, char *input, size_t insize, int a4,
                                                  char *output, size_t *outsize, int a7)
{
  printf("(mock) gtv_ca_sign_crt p_key=%p input=%p insize=%u a4=%u output=%p outsize=%u a7=%u\n", 
    p_key, input, insize, a4, output, *outsize, a7);
  return 0;
}

int gtv_ca_unload_key(struct OpenCrypto_Key **p_key)
{
  printf("(mock) gtv_ca_unload_key p_key=%p\n", *p_key);
  return 0;
}
