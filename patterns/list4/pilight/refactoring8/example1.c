static int send_queue(struct JsonNode *json, enum origin_t origin) {
	pthread_mutex_lock(&sendqueue_lock);
	logprintf(LOG_STACK, "%s(...)", __FUNCTION__);

	int match = 0, raw[MAXPULSESTREAMLENGTH-1];
	struct timeval tcurrent;
	struct clients_t *tmp_clients = NULL;
	char *uuid = NULL, *buffer = NULL;
	/* Hold the final protocol struct */
	struct protocol_t *protocol = NULL;

#ifdef _WIN32
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
#else
	/* Make sure the pilight sender gets
	   the highest priority available */
	struct sched_param sched;
	memset(&sched, 0, sizeof(sched));
	sched.sched_priority = 80;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &sched);
#endif

	struct JsonNode *jcode = NULL;
	struct JsonNode *jprotocols = NULL;
	struct JsonNode *jprotocol = NULL;

	buffer = json_stringify(json, NULL);
	tmp_clients = clients;
	while(tmp_clients) {
		if(tmp_clients->forward == 1) {
			socket_write(tmp_clients->id, buffer);
		}
		tmp_clients = tmp_clients->next;
	}
	json_free(buffer);

	if((jcode = json_find_member(json, "code")) == NULL) {
		logprintf(LOG_ERR, "sender did not send any codes");
		json_delete(jcode);
		pthread_mutex_unlock(&sendqueue_lock);
		return -1;
	} else if((jprotocols = json_find_member(jcode, "protocol")) == NULL) {
		logprintf(LOG_ERR, "sender did not provide a protocol name");
		json_delete(jcode);
		pthread_mutex_unlock(&sendqueue_lock);
		return -1;
	} else {
		json_find_string(jcode, "uuid", &uuid);
		/* If we matched a protocol and are not already sending, continue */
		if(uuid == NULL || (uuid != NULL && strcmp(uuid, pilight_uuid) == 0)) {
			jprotocol = json_first_child(jprotocols);
			while(jprotocol && match == 0) {
				match = 0;
				if(jprotocol->tag == JSON_STRING) {
					struct protocols_t *pnode = protocols;
					/* Retrieve the used protocol */
					while(pnode) {
						protocol = pnode->listener;
						/* Check if the protocol exists */
						if(protocol_device_exists(protocol, jprotocol->string_) == 0 && match == 0) {
							match = 1;
							break;
						}
						pnode = pnode->next;
					}
				}
				jprotocol = jprotocol->next;
			}
			memset(raw, 0, MAXPULSESTREAMLENGTH-1);
			protocol->raw = raw;
			if(match == 1 && protocol->createCode != NULL) {
				/* Let the protocol create his code */
				if(protocol->createCode(jcode) == 0 && main_loop == 1) {
					if(sendqueue_number <= 1024) {
						struct sendqueue_t *mnode = MALLOC(sizeof(struct sendqueue_t));
						if(mnode == NULL) {
							fprintf(stderr, "out of memory\n");
							exit(EXIT_FAILURE);
						}
						gettimeofday(&tcurrent, NULL);
						mnode->origin = origin;
						mnode->id = 1000000 * (unsigned int)tcurrent.tv_sec + (unsigned int)tcurrent.tv_usec;
						mnode->message = NULL;
						if(protocol->message != NULL) {
							char *jsonstr = json_stringify(protocol->message, NULL);
							json_delete(protocol->message);
							if(json_validate(jsonstr) == true) {
								if((mnode->message = MALLOC(strlen(jsonstr)+1)) == NULL) {
									fprintf(stderr, "out of memory\n");
									exit(EXIT_FAILURE);
								}
								strcpy(mnode->message, jsonstr);
							}
							json_free(jsonstr);
							protocol->message = NULL;
						}

						mnode->length = protocol->rawlen;
						memcpy(mnode->code, protocol->raw, sizeof(int)*protocol->rawlen);

						if((mnode->protoname = MALLOC(strlen(protocol->id)+1)) == NULL) {
							fprintf(stderr, "out of memory\n");
							exit(EXIT_FAILURE);
						}
						strcpy(mnode->protoname, protocol->id);
						mnode->protopt = protocol;

						struct options_t *tmp_options = protocol->options;
						char *stmp = NULL;
						struct JsonNode *jsettings = json_mkobject();
						struct JsonNode *jtmp = NULL;
						while(tmp_options) {
							if(tmp_options->conftype == DEVICES_SETTING) {
								if(tmp_options->vartype == JSON_NUMBER &&
								  (jtmp = json_find_member(jcode, tmp_options->name)) != NULL &&
								   jtmp->tag == JSON_NUMBER) {
									json_append_member(jsettings, tmp_options->name, json_mknumber(jtmp->number_, jtmp->decimals_));
								} else if(tmp_options->vartype == JSON_STRING && json_find_string(jcode, tmp_options->name, &stmp) == 0) {
									json_append_member(jsettings, tmp_options->name, json_mkstring(stmp));
								}
							}
							tmp_options = tmp_options->next;
						}
						char *strsett = json_stringify(jsettings, NULL);
						if((mnode->settings = MALLOC(strlen(strsett)+1)) == NULL) {
							fprintf(stderr, "out of memory\n");
							exit(EXIT_FAILURE);
						}
						strcpy(mnode->settings, strsett);
						json_free(strsett);
						json_delete(jsettings);

						if(uuid != NULL) {
							strcpy(mnode->uuid, uuid);
						} else {
							memset(mnode->uuid, '\0', UUID_LENGTH);
						}
						if(sendqueue_number == 0) {
							sendqueue = mnode;
							sendqueue_head = mnode;
						} else {
							sendqueue_head->next = mnode;
							sendqueue_head = mnode;
						}
						sendqueue_number++;
					} else {
						logprintf(LOG_ERR, "send queue full");
						pthread_mutex_unlock(&sendqueue_lock);
						return -1;
					}
					pthread_mutex_unlock(&sendqueue_lock);
					pthread_cond_signal(&sendqueue_signal);
					return 0;
				} else {
					pthread_mutex_unlock(&sendqueue_lock);
					return -1;
				}
			}
		} else {
			pthread_mutex_unlock(&sendqueue_lock);
			return 0;
		}
	}
	pthread_mutex_unlock(&sendqueue_lock);
	return -1;
}
