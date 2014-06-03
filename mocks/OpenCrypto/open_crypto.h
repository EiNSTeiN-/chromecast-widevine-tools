
#define EXPORT extern "C" __declspec (dllexport)

/* 20 bytes, allocated using DRM_GaloisMalloc */
struct OpenCrypto_Key {
  int field1;
  int field2;
  int field3;
  int field4;
  int field5;
};

/*
  Initialize the key structure and return a pointer to it in *p_key.
  The parameters field3 and field4 are stored in the corresponding 
  fields of the Key structure.

  field1 is a 4-byte value returned by the RPC call.
  field2 is set to 'BCDE'

  RPC Call: 0xA62
*/
EXPORT
int MV_OpenCrypto_CreateKey(struct OpenCrypto_Key **p_key, int field3, int field4);

/*
  Make RPC call to release the key. The 'key' structure is zeroed and free'd.

  RPC Call: 0xA72
*/
EXPORT
int MV_OpenCrypto_ReleaseKey(struct OpenCrypto_Key *key);

/*
  Set the key data from a keystore. The 'store' is the data read from 
  a keystore such as '/factory/client.key.bin' at offset 124.

  Best guess (to be confirmed): the RPC server will decrypt the key data and
  use this key for subsequent calls.

  RPC Call: 0xA63
*/
EXPORT
int MV_OpenCrypto_SetKeyParm(struct OpenCrypto_Key *key, char *store, int store_size, 
  int a4, int a5, void *a6, size_t n, int a8, int a9);

/*
  Set the IV for this key.

  RPC Call: 0xA75
*/
EXPORT
int MV_OpenCrypto_SetIV(struct OpenCrypto_Key *key, char *IV, size_t length);


/*
  Set the mode for this key.

  RPC Call: 0xA76
*/
EXPORT
int MV_OpenCrypto_SetMode(struct OpenCrypto_Key *key, int mode);


/*
  RPC Call: 0xA66
*/
EXPORT
int MV_OpenCrypto_Decrypt(struct OpenCrypto_Key *key, char *input, size_t input_length, 
                                                      char *output, size_t *output_length);

/*
  RPC Call: 0xA67
*/
EXPORT
int  MV_OpenCrypto_Encrypt(struct OpenCrypto_Key *key, char *input, size_t input_length,
                                                       char *output, size_t *output_length);

/*
  RPC Call: 0xA64
*/
EXPORT
int MV_OpenCrypto_ImportKey(struct OpenCrypto_Key *key, int a2, void *a3, size_t a4, int a5, 
  int field3, int a7, int field4, OpenCrypto_Key **a9);

/*
  Fill *buffer, *key_length and *a4 with the output of the rcp call.
  RPC Call: 0xA65
*/
EXPORT
int MV_OpenCrypto_ExportKeyDat(struct OpenCrypto_Key *key, char *buffer, int *key_length, int *a4);

/*
  The RPC call is done with the content of 'input' as argument and the 
  returned data is copied into 'output'. The 'output' buffer is assumed
  to be at least 'input_length' bytes and the exact copied size is 
  returned in '*output_length'.

  RPC Call: 0xA71
*/
EXPORT
int MV_OpenCrypto_EncKeyDat(struct OpenCrypto_Key *key, int a2, void *input, size_t input_length, 
                                                        int a5, void *output, int *output_length);

/*
  The RPC call is done with the content of 'input' as argument and the
  returned data is copied into 'output'.

  The data copied to 'output' will be at most 256 bytes long, and the exact
  size is returned in 'output_length'.

  RPC Call: 0xA68
*/
EXPORT
int MV_OpenCrypto_Sign(struct OpenCrypto_Key *key, char *input, size_t input_length, 
                                                   char *output, size_t *output_length);

/*
  Exact same as MV_OpenCrypto_Sign except an extra argument a6 is 
  passed to the RPC call (the call number is also different).

  RPC Call: 0xA85
*/
EXPORT
int MV_OpenCrypto_Sign_CRT(struct OpenCrypto_Key *key, char *input, size_t input_length, 
                                                   char *output, size_t *output_length, 
                                                   int a6);

/*
  Make the RPC call wiht buffer1 and buffer2, and return 4 bytes in *ret.

  RPC Call: 0xA69
*/
EXPORT
int MV_OpenCrypto_Verify(OpenCrypto_Key *key, char *buffer1, size_t buffer1_length, 
                                              char *buffer2, size_t buffer2_length,
                                              int *ret);

/*
  Make the RPC call and just return a 4 bytes value in *a2.
  RPC Call: 0xA6A
*/
EXPORT
int MV_OpenCrypto_MoveKey(OpenCrypto_Key *key, int *a2);

/*
  Make the RPC call and just return a 4 bytes value in *a2.
  RPC Call: 0xA77
*/
EXPORT
int MV_OpenCrypto_MoveKey_Ext(OpenCrypto_Key *key, int *a2);

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_CreateHash();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_ReleaseHash();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_SetHashParm();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_MakeDigest();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_HashInit();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_HashUpdate();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_HashFinalize();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_GetSecureClock();

/*
  RPC Call: 
*/
EXPORT
int MV_OpenCrypto_R2R_KeyLadder();

