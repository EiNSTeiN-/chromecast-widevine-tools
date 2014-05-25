#include <string.h>

int _oecc01(int a1)
{
  __printf_chk(1, "(mock) _oecc01 // OEMCrypto_Initialize\n");
  return 0;
}

int _oecc02(int a1)
{
  __printf_chk(1, "(mock) _oecc02 // OEMCrypto_Terminate\n");
  return 0;
}

int _oecc03(/* todo */)
{
  __printf_chk(1, "(mock) _oecc03\n");
  return -1;
}

int _oecc04(char *buffer, int *p_length, int security_level)
{
  __printf_chk(1, "(mock) _oecc04 // Get token\n");
  memset(buffer, 0, *p_length);
  return 0;
}

int _oecc05(int security_level)
{
  __printf_chk(1, "(mock) _oecc05\n");
  return -1;
}

int _oecc06(char *buffer, int length)
{
  __printf_chk(1, "(mock) _oecc06 // Get random data\n");
  memset(buffer, 4, length); // Chosen by a fair dice roll.
  return 0;
}

int _oecc07(char *buffer, int *p_length, int security_level)
{
  __printf_chk(1, "(mock) _oecc07\n");
  return -1;
}

int _oecc09(int *p_session_id, int security_level)
{
  __printf_chk(1, "(mock) _oecc09 // OpenSession\n");
  *p_session_id = 0x800;
  return 0;
}

int _oecc10(int session_id)
{
  __printf_chk(1, "(mock) _oecc10 // CloseSession\n");
  return 0;
}

int _oecc12(int session_id, char *mac_ctx, int mac_ctx_len, char *enc_ctx, int enc_ctx_len)
{
  __printf_chk(1, "(mock) _oecc12 // Prepare request\n");
  return 0;
}

int _oecc13(int session_id, char *msg, int msglen, char *sig, int *p_siglen)
{
  __printf_chk(1, "(mock) _oecc13 // Sign message\n");
  memset(sig, 0, *p_siglen);
  return 0;
}

int _oecc14(int session_id, int *nonce)
{
  __printf_chk(1, "(mock) _oecc14 // Generate nonce\n");
  *nonce = 0x04040404;
  return 0;
}

int _oecc15(/* todo */)
{
  __printf_chk(1, "(mock) _oecc15\n");
  return -1;
}

int _oecc16(/* todo */)
{
  __printf_chk(1, "(mock) _oecc16\n");
  return -1;
}

int _oecc17(/* todo */)
{
  __printf_chk(1, "(mock) _oecc17\n");
  return -1;
}

int _oecc18(/* todo */)
{
  __printf_chk(1, "(mock) _oecc18\n");
  return -1;
}

int _oecc19(int session_id, char *key, int keylen)
{
  __printf_chk(1, "(mock) _oecc19\n");
  return -1;
}

int _oecc20(int session_id, char *msg, int msglen, char *sig, int *p_siglen)
{
  __printf_chk(1, "(mock) _oecc20\n");
  return -1;
}

int _oecc21(int session_id, char *a3, int a3_len, 
    char *mac_ctx, int mac_ctx_len, char *enc_ctx, int enc_ctx_len)
{
  __printf_chk(1, "(mock) _oecc21\n");
  return -1;
}
