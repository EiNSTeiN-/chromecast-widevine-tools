from OpenSSL import crypto
import hashlib
 
cert = crypto.X509()
cert.get_subject().CN = 'Leapcast'
cert.get_subject().C = 'US'
cert.get_subject().ST = 'California'
cert.get_subject().O = 'Google Inc'
cert.get_subject().OU = 'Chromecast'
cert.get_subject().L = 'Mountain View'
 
cert.set_serial_number(1000)
 
# Set the validity period (~10 years)
cert.gmtime_adj_notBefore(0)
cert.gmtime_adj_notAfter(315360000)
 
# The subject of this cert is also the issuer (self-signed cert)
cert.set_issuer(cert.get_subject())
 
# Set the public key of the cert
k = crypto.PKey()
k.generate_key(crypto.TYPE_RSA, 2048)
cert.set_pubkey(k)
 
# Sign the cert
cert.sign(k, 'sha1')
 
print crypto.dump_certificate(crypto.FILETYPE_PEM, cert)[:-1]
print crypto.dump_privatekey(crypto.FILETYPE_PEM, k)[:-1]

der = crypto.dump_certificate(crypto.FILETYPE_ASN1, cert)
sha = hashlib.sha1(der).hexdigest()

print ''
print 'Now to get this signed on your chromecast:'
print '   ./gtv_ca_sign --sha1 %s' % (sha, )
