#ifdef SUPPORT_PCRE8
if ((return_value = return_value8[0]) != return_value8[1]) {
					printf("\n8 bit: Return value differs(J8:%d,I8:%d): [%d] '%s' @ '%s'\n",
						return_value8[0], return_value8[1], total, current->pattern, current->input);
					is_successful = 0;
				} else
#endif
#ifdef SUPPORT_PCRE16
				if ((return_value = return_value16[0]) != return_value16[1]) {
					printf("\n16 bit: Return value differs(J16:%d,I16:%d): [%d] '%s' @ '%s'\n",
						return_value16[0], return_value16[1], total, current->pattern, current->input);
					is_successful = 0;
				} else
#endif
#ifdef SUPPORT_PCRE32
				if ((return_value = return_value32[0]) != return_value32[1]) {
					printf("\n32 bit: Return value differs(J32:%d,I32:%d): [%d] '%s' @ '%s'\n",
						return_value32[0], return_value32[1], total, current->pattern, current->input);
					is_successful = 0;
				} else
#endif
#if defined SUPPORT_PCRE8 && defined SUPPORT_PCRE16
				if (return_value8[0] != return_value16[0]) {
					printf("\n8 and 16 bit: Return value differs(J8:%d,J16:%d): [%d] '%s' @ '%s'\n",
						return_value8[0], return_value16[0],
						total, current->pattern, current->input);
					is_successful = 0;
				} else
#endif
#if defined SUPPORT_PCRE8 && defined SUPPORT_PCRE32
				if (return_value8[0] != return_value32[0]) {
					printf("\n8 and 32 bit: Return value differs(J8:%d,J32:%d): [%d] '%s' @ '%s'\n",
						return_value8[0], return_value32[0],
						total, current->pattern, current->input);
					is_successful = 0;
				} else
#endif
#if defined SUPPORT_PCRE16 && defined SUPPORT_PCRE32
				if (return_value16[0] != return_value32[0]) {
					printf("\n16 and 32 bit: Return value differs(J16:%d,J32:%d): [%d] '%s' @ '%s'\n",
						return_value16[0], return_value32[0],
						total, current->pattern, current->input);
					is_successful = 0;
				} else
#endif
				if (return_value >= 0 || return_value == PCRE_ERROR_PARTIAL) {
					if (return_value == PCRE_ERROR_PARTIAL) {
						return_value = 2;
					} else {
						return_value *= 2;
					}
#ifdef SUPPORT_PCRE8
					return_value8[0] = return_value;
#endif
#ifdef SUPPORT_PCRE16
					return_value16[0] = return_value;
#endif
#ifdef SUPPORT_PCRE32
					return_value32[0] = return_value;
#endif
					/* Transform back the results. */
					if (current->flags & PCRE_UTF8) {
#ifdef SUPPORT_PCRE16
						for (i = 0; i < return_value; ++i) {
							if (ovector16_1[i] >= 0)
								ovector16_1[i] = regtest_offsetmap16[ovector16_1[i]];
							if (ovector16_2[i] >= 0)
								ovector16_2[i] = regtest_offsetmap16[ovector16_2[i]];
						}
#endif
#ifdef SUPPORT_PCRE32
						for (i = 0; i < return_value; ++i) {
							if (ovector32_1[i] >= 0)
								ovector32_1[i] = regtest_offsetmap32[ovector32_1[i]];
							if (ovector32_2[i] >= 0)
								ovector32_2[i] = regtest_offsetmap32[ovector32_2[i]];
						}
#endif
					}

					for (i = 0; i < return_value; ++i) {
#if defined SUPPORT_PCRE8 && defined SUPPORT_PCRE16
						if (ovector8_1[i] != ovector8_2[i] || ovector8_1[i] != ovector16_1[i] || ovector8_1[i] != ovector16_2[i]) {
							printf("\n8 and 16 bit: Ovector[%d] value differs(J8:%d,I8:%d,J16:%d,I16:%d): [%d] '%s' @ '%s' \n",
								i, ovector8_1[i], ovector8_2[i], ovector16_1[i], ovector16_2[i],
								total, current->pattern, current->input);
							is_successful = 0;
						}
#endif
#if defined SUPPORT_PCRE8 && defined SUPPORT_PCRE32
						if (ovector8_1[i] != ovector8_2[i] || ovector8_1[i] != ovector32_1[i] || ovector8_1[i] != ovector32_2[i]) {
							printf("\n8 and 32 bit: Ovector[%d] value differs(J8:%d,I8:%d,J32:%d,I32:%d): [%d] '%s' @ '%s' \n",
								i, ovector8_1[i], ovector8_2[i], ovector32_1[i], ovector32_2[i],
								total, current->pattern, current->input);
							is_successful = 0;
						}
#endif
#if defined SUPPORT_PCRE16 && defined SUPPORT_PCRE16
						if (ovector16_1[i] != ovector16_2[i] || ovector16_1[i] != ovector16_1[i] || ovector16_1[i] != ovector16_2[i]) {
							printf("\n16 and 16 bit: Ovector[%d] value differs(J16:%d,I16:%d,J32:%d,I32:%d): [%d] '%s' @ '%s' \n",
								i, ovector16_1[i], ovector16_2[i], ovector16_1[i], ovector16_2[i],
								total, current->pattern, current->input);
							is_successful = 0;
						}
#endif
					}
				}
