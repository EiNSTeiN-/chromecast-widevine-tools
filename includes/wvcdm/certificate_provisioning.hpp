#include <crypto_session.hpp>

namespace wvcdm {
  using wvcdm::CryptoSession;
  
  class CertificateProvisioning {
  public:
    /* Create a provisioning request, sign it with derived keys, and return the 
      request as a query string. */
    static int GetProvisioningRequest(SecurityLevel security_level, 
      std::string *query_string, std::string *default_provisioning_server);

    /* Take a provisioning request serialized as string and return a query string. */
    static int ComposeJsonRequestAsQueryString(CryptoSession *session, 
      const std::string &provisioning_msg, std::string *query_string);
  };
};
