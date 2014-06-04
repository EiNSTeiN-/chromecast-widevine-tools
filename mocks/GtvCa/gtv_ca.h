#include <OpenCrypto/open_crypto.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DLLEXPORTS
#define EXPORT __declspec (dllexport)
#else
#define EXPORT
#endif

/* Does roughly the same as gtv_ca_load_key_advance but then 
  call MV_OpenCrypto_ImportKey and then MV_OpenCrypto_ReleaseKey */
EXPORT
int gtv_ca_load_key(struct OpenCrypto_Key **p_key, int a2, int a3, int a4);

/*
  Load a key by calling MV_OpenCrypto_CreateKey and then MV_OpenCrypto_SetKeyParm.
  A newly allocated structure is returned in *p_key.
  The data at `store` is the content of /factory/client.key.bin starting at offset 124.
  Called with a4=4 and a5=2.
*/
EXPORT
int gtv_ca_load_key_advance(struct OpenCrypto_Key **p_key, char *store, int store_size, int a4, int a5);

/* Do nothing. Return 0 (no error) if *p_key is non-NULL, or -1 (error) if *p_key is NULL. */
EXPORT
int gtv_ca_unload_key(struct OpenCrypto_Key **p_key);

/* Print %02x formatted buffer. */
EXPORT
int GtvCaDebugDump(char *buffer, unsigned int length);

EXPORT
int gtv_ca_provision_key(void /* todo */);

/* Generate a signature */
EXPORT
int gtv_ca_sign(void /* todo */);

/*
  Generate a signature for a certificate
  Call MV_OpenCrypto_Sign_CRT under the hood.
  a4 is the hash type, either 0, 1, 2.
  a7 is 1.
*/
EXPORT
int gtv_ca_sign_crt(struct OpenCrypto_Key *p_key, char *input, size_t insize, int a4,
                                                  char *output, size_t *outsize, int a7);

/* Just call MV_OpenCrypto_Decrypt underneath */
EXPORT
int gtv_ca_decrypt(int a1, int a2, int a3, int a4, int a5);

#ifdef __cplusplus
}
#endif

