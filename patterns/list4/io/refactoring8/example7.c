IoMethodTable methodTable[] = {
	{"clone", IoMessage_clone},

	{"name", IoMessage_protoName},
	{"setName", IoMessage_protoSetName},

	{"next", IoMessage_next},
	{"setNext", IoMessage_setNext},
	{"isEndOfLine", IoMessage_isEOL},
	{"nextIgnoreEndOfLines", IoMessage_nextIgnoreEOLs},
	{"last", IoMessage_last},
	{"lastBeforeEndOfLine", IoMessage_lastBeforeEOL},

	{"argAt", IoMessage_argAt},
	{"arguments", IoMessage_arguments},
	{"setArguments", IoMessage_setArguments},
	{"appendArg", IoMessage_appendArg},
	{"appendCachedArg", IoMessage_appendCachedArg},
	{"argCount", IoMessage_argCount_},

	{"cachedResult", IoMessage_cachedResult},
	{"setCachedResult", IoMessage_setCachedResult},
	{"removeCachedResult", IoMessage_removeCachedResult},
	{"hasCachedResult", IoMessage_hasCachedResult},

	{"lineNumber", IoMessage_lineNumber},
	{"setLineNumber", IoMessage_setLineNumber},

	{"characterNumber", IoMessage_characterNumber},
	{"setCharacterNumber", IoMessage_setCharacterNumber},

	{"label", IoMessage_label},
	{"setLabel", IoMessage_setLabel},

	{"code", IoMessage_descriptionString},
	{"doInContext", IoMessage_doInContext},
	{"fromString", IoMessage_fromString},
	{"argsEvaluatedIn", IoMessage_argsEvaluatedIn},
	{"asString", IoMessage_asString},

	{"asMessageWithEvaluatedArgs", IoMessage_asMessageWithEvaluatedArgs},

	{"opShuffle", IoMessage_opShuffle},
	{"opShuffleC", IoMessage_opShuffle},
	
	#ifdef IOMESSAGE_HASPREV
	{"previous", IoMessage_previous},
	#endif

	{NULL, NULL},
	};
