static char const *action_codes[] = {
	"INVALID",
	"run",
	"done",
	"dup",
	"timer",
#ifdef WITH_PROXY
	"proxy-reply"
#endif
};
