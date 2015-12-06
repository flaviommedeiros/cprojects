char const *unlang_keyword[] = {
	"",
	"single",
	"group",
	"load-balance group",
	"redundant-load-balance group",
#ifdef WITH_UNLANG
	"if",
	"else",
	"elsif",
	"update",
	"switch",
	"case",
	"foreach",
	"break",
	"return",
	"map",
#endif
	"policy",
	"reference",
	"xlat",
	NULL
};
