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

int main(int argc, char *argv[])
{
  struct OpenCrypto_Key *key = NULL;
  const char *keystore_filename = NULL;
  unsigned int keystore_length = 0, keystore_length_ = 0;
  char *keystore = NULL;
  int i, type;
  unsigned int err;

  char *der_cert_filename = NULL;
  char *cert_der = NULL;
  unsigned int cert_der_length = 0;
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
    }
    if(!strcasecmp(argv[i], "--cert") && i+1 < argc) {
      der_cert_filename = argv[i+1];
    }
  }

  // Set some defaults
  if(!keystore_filename) {
    keystore_filename = DEFAULT_KEYSTORE_FILENAME;
    printf("Using default keystore: %s\n", keystore_filename);
  }

  if(!der_cert_filename) {
    fprintf(stderr, "please specify --cert <filename>\n");
    return -1;
  }

  if(read_file(keystore_filename, &keystore, &keystore_length) != 0) {
    fprintf(stderr, "read file: unable to load keystore %s\n", keystore_filename);
    return -1;
  }

  if(read_file(der_cert_filename, &cert_der, &cert_der_length) != 0) {
    fprintf(stderr, "read file: unable to load cert %s\n", der_cert_filename);
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

  for(type=0;type<=2;type++) {
    sig_length = 256;
    sig = (char *)malloc(sig_length);
    if(!sig) {
      fprintf(stderr, "malloc: failed to allocate %u\n", sig_length);
      return -1;
    }
    memset(sig, 0, sig_length);

    printf("trying gtv_ca_sign_crt with a4=%u\n", type);
    if((err = gtv_ca_sign_crt(key, cert_der, cert_der_length, type, sig, &sig_length, 1)) != 0) {
      fprintf(stderr, "gtv_ca_unload_key: failed %u\n", err);
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
  }

  if((err = gtv_ca_unload_key(&key)) != 0) {
    fprintf(stderr, "gtv_ca_unload_key: failed %u\n", err);
    return -1;
  }

  return 0;
}
