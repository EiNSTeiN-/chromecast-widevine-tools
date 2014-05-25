
#define EXPORT extern "C" __declspec (dllexport)

/*
  Initialize the crypto module
  Called by CryptoSession::Init
*/
EXPORT
int _oecc01(int a1);

/*
  Un-initialize the crypto module
  Called by CryptoSession::Terminate
*/
EXPORT
int _oecc02(int a1);

/* */
EXPORT
int _oecc03(/* todo */);

/* */
EXPORT
int _oecc04(char *buffer, int *p_length, int security_level);

/* */
EXPORT
int _oecc05(int security_level);

/*
  Fills `buffer` with `length` bytes of random data.
  Called by CryptoSession::Open
*/
EXPORT
int _oecc06(char *buffer, int length);

/* */
EXPORT
int _oecc07(char *buffer, int *p_length, int security_level);

/* OpenSession */
EXPORT
int _oecc09(int *p_session_id, int security_level);

/*
  Close the session.
  Called by CryptoSession::Close
*/
EXPORT
int _oecc10(int session_id);

/*
  Called from CryptoSession::GenerateDerivedKeys with the output of 
  CryptoSession::GenerateMacContext and CryptoSession::GenerateEncryptContext.
*/
EXPORT
int _oecc12(int session_id, char *mac_ctx, int mac_ctx_len, char *enc_ctx, int enc_ctx_len);

/*
  Fill `sig` with a valid signature for `msg`
  Called by CryptoSession::GenerateSignature
*/
EXPORT
int _oecc13(int session_id, char *msg, int msglen, char *sig, int *p_siglen);

/*
  Return 4 bytes of nonce.
  Called by CryptoSession::GenerateNonce
*/
EXPORT
int _oecc14(int session_id, uint32_t *nonce);

EXPORT
int _oecc15(/* todo */);

EXPORT
int _oecc16(/* todo */);

EXPORT
int _oecc17(/* todo */);

EXPORT
int _oecc18(/* todo */);

/*
  Fill `key` with a valid signature for `msg`
  Called by CryptoSession::LoadCertificatePrivateKey
*/
EXPORT
int _oecc19(int session_id, char *key, int keylen);

/*
  Fill `sig` with a valid signature for `msg`
  Called by CryptoSession::GenerateSignature
*/
EXPORT
int _oecc20(int session_id, char *msg, int msglen, char *sig, int *p_siglen);

/*
  Much like oecc12 but from an overloaded version of CryptoSession::GenerateDerivedKeys
  which pass an extra agrument `a3`.
*/
EXPORT
int _oecc21(int session_id, char *a3, int a3_len, 
    char *mac_ctx, int mac_ctx_len, char *enc_ctx, int enc_ctx_len);

};

