#ifdef HAVE_FCHDIR
if (t->openCount > t->maxOpenCount)
					t->maxOpenCount = t->openCount;
