switch (dynamic_shared_memory_type)
	{
#ifdef USE_DSM_WINDOWS
		case DSM_IMPL_WINDOWS:
			{
				HANDLE		hmap;

				if (!DuplicateHandle(GetCurrentProcess(), impl_private,
									 PostmasterHandle, &hmap, 0, FALSE,
									 DUPLICATE_SAME_ACCESS))
				{
					char		name[64];

					snprintf(name, 64, "%s.%u", SEGMENT_NAME_PREFIX, handle);
					_dosmaperr(GetLastError());
					ereport(ERROR,
							(errcode_for_dynamic_shared_memory(),
						  errmsg("could not duplicate handle for \"%s\": %m",
								 name)));
				}
				break;
			}
#endif
		default:
			break;
	}
