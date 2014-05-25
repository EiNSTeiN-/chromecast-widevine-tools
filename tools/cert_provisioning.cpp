#include <iostream>
#include <stdio.h>

#include <certificate_provisioning.hpp>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wire_format_lite_inl.h>

using namespace std;
using namespace wvcdm;
using namespace google::protobuf;

int main(void)
{
  CertificateProvisioning prov;
  string provisioning_server;
  string query_string;

  prov.GetProvisioningRequest(SECURITY_LEVEL0, &query_string, &provisioning_server);

  printf("provisioning server: %s\n", provisioning_server.c_str());
  printf("query_string: %s\n", query_string.c_str());

  return 0;
}
