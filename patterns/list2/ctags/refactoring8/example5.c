static kindOption RubyKinds [] = {
	{ TRUE, 'c', "class",  "classes" },
	{ TRUE, 'f', "method", "methods" },
	{ TRUE, 'm', "module", "modules" },
	{ TRUE, 'F', "singletonMethod", "singleton methods" },
#if 0
	/* Following two kinds are reserved. */
	{ TRUE, 'd', "describe", "describes and contexts for Rspec" },
	{ TRUE, 'C', "constant", "constants" },
#endif
};
