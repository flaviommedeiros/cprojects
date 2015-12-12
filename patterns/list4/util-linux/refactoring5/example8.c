#ifdef HAVE_LIBUUID
if (ctl->uuid) {
			char uuid_string[37];
			uuid_unparse(ctl->uuid, uuid_string);
			printf("UUID=%s\n", uuid_string);
		} else
#endif
			printf(_("no uuid\n"));
