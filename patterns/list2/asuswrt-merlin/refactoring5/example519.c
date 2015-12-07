#ifdef RTCONFIG_HTTPS
if(do_ssl){
			//websWrite(wp, T("<meta http-equiv=\"refresh\" content=\"0; url=https://%s/%s\">\r\n"), gethost(), url);
			websWrite(wp,"<script>parent.location.href='/%s';</script>\n",url);
		}else
#endif	
		{
			//websWrite(wp, T("<meta http-equiv=\"refresh\" content=\"0; url=http://%s/%s\">\r\n"), gethost(), url);
			websWrite(wp,"<script>parent.location.href='/%s';</script>\n",url);
		}
