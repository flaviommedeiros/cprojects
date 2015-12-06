static const char *crl_usage[]={
"usage: crl args\n",
"\n",
" -inform arg     - input format - default PEM (DER or PEM)\n",
" -outform arg    - output format - default PEM\n",
" -text           - print out a text format version\n",
" -in arg         - input file - default stdin\n",
" -out arg        - output file - default stdout\n",
" -hash           - print hash value\n",
#ifndef OPENSSL_NO_MD5
" -hash_old       - print old-style (MD5) hash value\n",
#endif
" -fingerprint    - print the crl fingerprint\n",
" -issuer         - print issuer DN\n",
" -lastupdate     - lastUpdate field\n",
" -nextupdate     - nextUpdate field\n",
" -crlnumber      - print CRL number\n",
" -noout          - no CRL output\n",
" -CAfile  name   - verify CRL using certificates in file \"name\"\n",
" -CApath  dir    - verify CRL using certificates in \"dir\"\n",
" -nameopt arg    - various certificate name options\n",
NULL
};
