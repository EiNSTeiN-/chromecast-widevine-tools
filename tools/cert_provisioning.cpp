#include <iostream>

#include <certificate_provisioning.hpp>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wire_format_lite_inl.h>

using namespace std;
using namespace wvcdm;
using namespace google::protobuf;

int main(void)
{
  CryptoSession session;
  string provisioning_server;
  string query_string;

  CertificateProvisioning::GetProvisioningRequest(SECURITY_LEVEL0, &query_string, &provisioning_server);

  return 0;
}
