if (strcasecmp(&options.listconf[15], "init") &&
				         strcasecmp(&options.listconf[15], "done") &&
				         strcasecmp(&options.listconf[15], "reset") &&
				         strcasecmp(&options.listconf[15], "prepare") &&
				         strcasecmp(&options.listconf[15], "split") &&
				         strcasecmp(&options.listconf[15], "binary") &&
				         strcasecmp(&options.listconf[15], "clear_keys") &&
				         strcasecmp(&options.listconf[15], "salt") &&
				         strcasecmp(&options.listconf[15], "tunable_cost_value") &&
				         strcasecmp(&options.listconf[15], "tunable_cost_value[0]") &&
#if FMT_TUNABLE_COSTS > 1
				         strcasecmp(&options.listconf[15], "tunable_cost_value[1]") &&
#if FMT_TUNABLE_COSTS > 2
				         strcasecmp(&options.listconf[15], "tunable_cost_value[2]") &&
#endif
#endif
					 strcasecmp(&options.listconf[15], "source") &&
				         strcasecmp(&options.listconf[15], "get_hash") &&
				         strcasecmp(&options.listconf[15], "get_hash[0]") &&
					 strcasecmp(&options.listconf[15], "get_hash[1]") &&
				         strcasecmp(&options.listconf[15], "get_hash[2]") &&
				         strcasecmp(&options.listconf[15], "get_hash[3]") &&
				         strcasecmp(&options.listconf[15], "get_hash[4]") &&
				         strcasecmp(&options.listconf[15], "get_hash[5]") &&
				         strcasecmp(&options.listconf[15], "get_hash[6]") &&
				         strcasecmp(&options.listconf[15], "set_salt") &&
				         strcasecmp(&options.listconf[15], "binary_hash") &&
				         strcasecmp(&options.listconf[15], "binary_hash[0]") &&
				         strcasecmp(&options.listconf[15], "binary_hash[1]") &&
				         strcasecmp(&options.listconf[15], "binary_hash[2]") &&
				         strcasecmp(&options.listconf[15], "binary_hash[3]") &&
				         strcasecmp(&options.listconf[15], "binary_hash[4]") &&
				         strcasecmp(&options.listconf[15], "binary_hash[5]") &&
					 strcasecmp(&options.listconf[15], "binary_hash[6]") &&
				         strcasecmp(&options.listconf[15], "salt_hash") &&
				         strcasecmp(&options.listconf[15], "salt_compare"))
				{
					fprintf(stderr, "Error, invalid option (invalid method name) %s\n", options.listconf);
					fprintf(stderr, "Valid method names are:\n");
					listconf_list_method_names();
					exit(EXIT_FAILURE);
				}
