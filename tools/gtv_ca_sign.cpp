#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <GtvCa/gtv_ca.h>
#include <OSAL/osal.h>

#define DEFAULT_KEYSTORE_FILENAME "/factory/client.key.bin"

int read_file(const char *filename, char **data, unsigned int *length)
{
  FILE *fd;

  fd = fopen(filename, "rb");
  if(!fd)
    return -1;

  fseek(fd, 0, SEEK_END);
  *length = ftell(fd);
  if(*length == 0) {
    fclose(fd);
    return -1;
  }

  *data = (char *)malloc(*length);
  if(*data == NULL) {
    fclose(fd);
    return -1;
  }

  rewind(fd);
  if(fread(*data, 1, *length, fd) != *length) {
    fclose(fd);
    return -1;
  }

  fclose(fd);
  return 0;
}

void from_hex(const char *src, int len, char *dest)
{
  int n;
  char s[3] = {0,0,0};
  for ( int j=0; j<len; j += 2 ) {
    strncpy(s, src, 2);
    sscanf(s, "%x", &n);
    src += 2;
    *dest++ = (char)n;
  }
}


int main(int argc, char *argv[])
{
  struct OpenCrypto_Key *key = NULL;
  const char *keystore_filename = NULL;
  unsigned int keystore_length = 0, keystore_length_ = 0;
  char *keystore = NULL;
  int i;
  unsigned int err;

  int hash_type = -1;
  char *hash = NULL;
  unsigned int hash_length = 0;
  char *sig = NULL;
  unsigned int sig_length = 0;

  if((err = MV_OSAL_Init()) != 0) {
    fprintf(stderr, "MV_OSAL_Init: failed %u\n", err);
    return -1;
  }

  // Parse command line arguments
  for(i=1;i<argc;i++) {
    if(!strcasecmp(argv[i], "--keystore") && i+1 < argc) {
      keystore_filename = argv[i+1];
      i++;
    }
    else if(!strcasecmp(argv[i], "--sha1") && i+1 < argc) {
      hash_type = 0;
      hash_length = strlen(argv[i+1]) / 2;
      hash = (char *)malloc(hash_length);
      from_hex(argv[i+1], strlen(argv[i+1]), hash);
      i++;
    }
  }

  // Set some defaults
  if(!keystore_filename) {
    keystore_filename = DEFAULT_KEYSTORE_FILENAME;
    printf("Using default keystore: %s\n", keystore_filename);
  }

  if(hash_type == -1 || hash_length != 20) {
    fprintf(stderr, "please specify --sha1 <hash> with 20 hex-encoded bytes.\n");
    return -1;
  }

  if(read_file(keystore_filename, &keystore, &keystore_length) != 0) {
    fprintf(stderr, "read file: unable to load keystore %s\n", keystore_filename);
    return -1;
  }

  keystore_length_ = *(unsigned int *)(keystore + 124);
  keystore_length_ += 15;
  keystore_length_ &= 0xFFFFFFF0;
  keystore_length_ += 128;
  printf("using keystore_bits=%u, should match filesize=%u\n", keystore_length_, keystore_length);

  if((err = gtv_ca_load_key_advance(&key, keystore, keystore_length_, 4, 2)) != 0) {
    fprintf(stderr, "gtv_ca_load_key_advance: failed %u\n", err);
    return -1;
  }

  sig_length = 256;
  sig = (char *)malloc(sig_length);
  if(!sig) {
    fprintf(stderr, "malloc: failed to allocate %u\n", sig_length);
    return -1;
  }
  memset(sig, 0, sig_length);

  printf("trying gtv_ca_sign_crt with type=%u\n", hash_type);
  printf("hash=");
  for(i=0;i<hash_length;i++)
    printf("%02x", hash[i]);
  printf("\n");

  if((err = gtv_ca_sign_crt(key, hash, hash_length, hash_type, sig, &sig_length, 1)) != 0) {
    fprintf(stderr, "gtv_ca_sign_crt: failed %u\n", err);
  }
  else {
    printf("sig output length = %u\n", sig_length);
    printf("sig=");
    for(i=0;i<sig_length;i++)
      printf("%02x", sig[i]);
    printf("\n");
  }

  free(sig);
  sig = NULL;

  if((err = gtv_ca_unload_key(&key)) != 0) {
    fprintf(stderr, "gtv_ca_unload_key: failed %u\n", err);
    return -1;
  }

  return 0;
}
