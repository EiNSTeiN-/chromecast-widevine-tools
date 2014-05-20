#include <stdint.h>

#include <lock.hpp>

std::string *EncodeUint32(std::string *s, uint32_t n);

namespace wvcdm {
  using wvcdm::Lock;

  enum SecurityLevel {
    SECURITY_LEVEL0 = 0,
  };

  class CryptoSession {
  public:
    /* Create a new object, initialize instance variables and call Init() */
    CryptoSession(void);
    ~CryptoSession(void);

    /* Initialize the object (lock & static variables). */
    static int Init(void);
    /* Mirror call to Init() at the end of a session. */
    static int Terminate(void);

    int Open(int security_level);
    int Close(void);

    /* Call oecc05 underneath. */
    int ValidateKeybox(void);
    /* Call oecc23 underneath. */
    int GetSecurityLevel(void);

    /* Call oecc19 underneath. */
    int LoadCertificatePrivateKey(std::string *out);

    /*
    */
    int GetToken(std::string *token);

    /*
      Populate *nonce with a nonce.
      Calls oecc14 underneath.
    */
    int GenerateNonce(uint32_t *nonce);
    /*
      Fill `sig` with a valid signature for `msg`.
      `sig` is resized to the correct length.
    */
    int GenerateSignature(const std::string &msg, bool flag, std::string *sig);

    /*
      Append (char*)'AUTHENTICATION' + '\x00' + `msg` + EncodeUint32(0x200) to `context`
    */
    int GenerateMacContext(const std::string &msg, std::string *context);
    /*
      Append (char*)'ENCRYPTION' + '\x00' + `msg` + EncodeUint32(0x80) to `context`
    */
    int GenerateEncryptContext(const std::string &msg, std::string *context);
    /*
      Call GenerateMacContext and GenerateEncryptContext with the `msg` and
      then call oecc12(mac_ctx, enc_ctx)
    */
    int GenerateDerivedKeys(const std::string &msg);
    int GenerateDerivedKeys(const std::string &msg, const std::string &a3);
    /*
      Populate `sig` with the output of GenerateSignature.
      If `use_derived_keys` is true then GenerateDerivedKeys(msg) will be called prior to 
      a call to GenerateSignature.
      If derived keys are used then the `flag` argument to `GenerateSignature` will be false,
      otherwise `flag`=true.
      If `use_derived_keys=false` then `Properties::use_certificates_as_identification_` 
      must be true otherwise this call will fail/do nothing and return 0.
      The return value is what is returned by GenerateSignature.

      From CertificateProvisioning::GetProvisioningRequest this is called with use_derived_keys=true.
    */
    int PrepareRequest(const std::string &msg, bool use_derived_keys, const std::string *sig);

    static int session_count_;
    static int initialized_;
    static Lock crypto_lock;
  public:
    uint32_t is_session_open;
    uint32_t session_id;
    uint32_t f_8;
    uint8_t f_12[4];
    uint32_t security_level; // copy of 1st parameter to Open()
    uint32_t f_20;
    uint64_t random_data;
  };
};
