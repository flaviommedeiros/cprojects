punctuation_t default_punctuations[] =
{
	//binary operators
	{">>=",P_RSHIFT_ASSIGN, NULL},
	{"<<=",P_LSHIFT_ASSIGN, NULL},
	//
	{"...",P_PARMS, NULL},
	//define merge operator
	{"##",P_PRECOMPMERGE, NULL},
	//logic operators
	{"&&",P_LOGIC_AND, NULL},
	{"||",P_LOGIC_OR, NULL},
	{">=",P_LOGIC_GEQ, NULL},
	{"<=",P_LOGIC_LEQ, NULL},
	{"==",P_LOGIC_EQ, NULL},
	{"!=",P_LOGIC_UNEQ, NULL},
	//arithmatic operators
	{"*=",P_MUL_ASSIGN, NULL},
	{"/=",P_DIV_ASSIGN, NULL},
	{"%=",P_MOD_ASSIGN, NULL},
	{"+=",P_ADD_ASSIGN, NULL},
	{"-=",P_SUB_ASSIGN, NULL},
	{"++",P_INC, NULL},
	{"--",P_DEC, NULL},
	//binary operators
	{"&=",P_BIN_AND_ASSIGN, NULL},
	{"|=",P_BIN_OR_ASSIGN, NULL},
	{"^=",P_BIN_XOR_ASSIGN, NULL},
	{">>",P_RSHIFT, NULL},
	{"<<",P_LSHIFT, NULL},
	//reference operators
	{"->",P_POINTERREF, NULL},
	//C++
	{"::",P_CPP1, NULL},
	{".*",P_CPP2, NULL},
	//arithmatic operators
	{"*",P_MUL, NULL},
	{"/",P_DIV, NULL},
	{"%",P_MOD, NULL},
	{"+",P_ADD, NULL},
	{"-",P_SUB, NULL},
	{"=",P_ASSIGN, NULL},
	//binary operators
	{"&",P_BIN_AND, NULL},
	{"|",P_BIN_OR, NULL},
	{"^",P_BIN_XOR, NULL},
	{"~",P_BIN_NOT, NULL},
	//logic operators
	{"!",P_LOGIC_NOT, NULL},
	{">",P_LOGIC_GREATER, NULL},
	{"<",P_LOGIC_LESS, NULL},
	//reference operator
	{".",P_REF, NULL},
	//seperators
	{",",P_COMMA, NULL},
	{";",P_SEMICOLON, NULL},
	//label indication
	{":",P_COLON, NULL},
	//if statement
	{"?",P_QUESTIONMARK, NULL},
	//embracements
	{"(",P_PARENTHESESOPEN, NULL},
	{")",P_PARENTHESESCLOSE, NULL},
	{"{",P_BRACEOPEN, NULL},
	{"}",P_BRACECLOSE, NULL},
	{"[",P_SQBRACKETOPEN, NULL},
	{"]",P_SQBRACKETCLOSE, NULL},
	//
	{"\\",P_BACKSLASH, NULL},
	//precompiler operator
	{"#",P_PRECOMP, NULL},
#ifdef DOLLAR
	{"$",P_DOLLAR, NULL},
#endif //DOLLAR
	{NULL, 0}
};
