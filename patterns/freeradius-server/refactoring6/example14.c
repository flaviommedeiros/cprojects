if (!S_ISREG(buf.st_mode)
#ifdef S_ISSOCK
		    && !S_ISSOCK(buf.st_mode)
#endif
			) {
			fr_strerror_printf("Cannot turn %s into socket", path);
			close(sockfd);
			return -1;
		}
