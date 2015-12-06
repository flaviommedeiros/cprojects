return(ssl3_num_ciphers()
#ifndef OPENSSL_NO_SSL2
	       + ssl2_num_ciphers()
#endif
	    );
