if (!strncmp(buf, "#if", 3))
				{
					if (ifnest_false > 0 || !evaluate_condition(si, buf + 3))
						ifnest_false++;
					ifnest++;
					continue;
				}
				else if (!strncmp(buf, "#endif", 6))
				{
					if (ifnest_false > 0)
						ifnest_false--;
					if (ifnest > 0)
						ifnest--;
					continue;
				}
				else if (!strncmp(buf, "#else", 5))
				{
					if (ifnest > 0 && ifnest_false <= 1)
						ifnest_false ^= 1;
					continue;
				}
