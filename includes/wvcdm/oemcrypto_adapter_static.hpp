
namespace wvcdm {

  /*
    Fill `buffer` with up to *p_length data.
    Called by CryptoSession::GetToken
  */
  int _oecc04(char *buffer, int *p_length, int security_level);

  /* */
  int _oecc05(int security_level);

  /* */
  int _oecc07(char *buffer, int *p_length, int security_level);

  /*
    Returns a new session id.
    Called by CryptoSession::Open
  */
  int _oecc09(int *p_session_id, int security_level);
};
