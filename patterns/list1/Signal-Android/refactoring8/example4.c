static char *srp_usage[]={
"usage: srp [args] [user] \n",
"\n",
" -verbose        Talk alot while doing things\n",
" -config file    A config file\n",
" -name arg       The particular srp definition to use\n",
" -srpvfile arg   The srp verifier file name\n",
" -add            add an user and srp verifier\n",
" -modify         modify the srp verifier of an existing user\n",
" -delete         delete user from verifier file\n",
" -list           list user\n",
" -gn arg         g and N values to be used for new verifier\n",
" -userinfo arg   additional info to be set for user\n",
" -passin arg     input file pass phrase source\n",
" -passout arg    output file pass phrase source\n",
#ifndef OPENSSL_NO_ENGINE
" -engine e         - use engine e, possibly a hardware device.\n",
#endif
NULL
};
