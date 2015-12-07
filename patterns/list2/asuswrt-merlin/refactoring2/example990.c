#if 0
if (!(!nvram_match("switch_wantag", "none")&&!nvram_match("switch_wantag", "")))
#endif
					{
						modprobe("hw_nat");
						sleep(1);
					}
