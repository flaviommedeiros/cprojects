#ifndef OPENSSL_NO_SRP
if ((i == 2) && (type & SSL_kSRP))
				{
				*p = nr[i];
				p++;
				}
			else
#endif
			s2n(nr[i],p);
