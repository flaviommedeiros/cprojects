#ifdef WEBSERVER
if(strstr(buffer, " HTTP/")) {
			client_webserver_parse_code(i, buffer);
			socket_close(sd);
		} else if(json_validate(buffer) == true) {
#else
		if(json_validate(buffer) == true) {
#endif
			json = json_decode(buffer);
			if((json_find_string(json, "action", &action)) == 0) {
				tmp_clients = clients;
				while(tmp_clients) {
					if(tmp_clients->id == sd) {
						exists = 1;
						client = tmp_clients;
						break;
					}
					tmp_clients = tmp_clients->next;
				}
				if(strcmp(action, "identify") == 0) {
					/* Check if client doesn't already exist */
					if(exists == 0) {
						if((client = MALLOC(sizeof(struct clients_t))) == NULL) {
							fprintf(stderr, "out of memory\n");
							exit(EXIT_FAILURE);
						}
						client->core = 0;
						client->config = 0;
						client->receiver = 0;
						client->forward = 0;
						client->stats = 0;
						client->cpu = 0;
						client->ram = 0;
						strcpy(client->media, "all");
						client->next = NULL;
						client->id = sd;
						memset(client->uuid, '\0', sizeof(client->uuid));
					}
					if(json_find_string(json, "media", &media) == 0) {
						if(strcmp(media, "all") == 0 || strcmp(media, "mobile") == 0 ||
						   strcmp(media, "desktop") == 0 || strcmp(media, "web") == 0) {
								strcpy(client->media, media);
							 }
					} else {
						strcpy(client->media, "all");
					}
					char *t = NULL;
					if(json_find_string(json, "uuid", &t) == 0) {
						strcpy(client->uuid, t);
					}
					if((options = json_find_member(json, "options")) != NULL) {
						struct JsonNode *childs = json_first_child(options);
						while(childs) {
							if(strcmp(childs->key, "core") == 0 &&
							   childs->tag == JSON_NUMBER) {
								if((int)childs->number_ == 1) {
									client->core = 1;
								} else {
									client->core = 0;
								}
							} else if(strcmp(childs->key, "stats") == 0 &&
							   childs->tag == JSON_NUMBER) {
								if((int)childs->number_ == 1) {
									client->stats = 1;
								} else {
									client->stats = 0;
								}
							} else if(strcmp(childs->key, "receiver") == 0 &&
							   childs->tag == JSON_NUMBER) {
								if((int)childs->number_ == 1) {
									client->receiver = 1;
								} else {
									client->receiver = 0;
								}
							} else if(strcmp(childs->key, "config") == 0 &&
							   childs->tag == JSON_NUMBER) {
								if((int)childs->number_ == 1) {
									client->config = 1;
								} else {
									client->config = 0;
								}
							} else if(strcmp(childs->key, "forward") == 0 &&
							   childs->tag == JSON_NUMBER) {
								if((int)childs->number_ == 1) {
									client->forward = 1;
								} else {
									client->forward = 0;
								}
							} else {
							   error = 1;
							   break;
							}
							childs = childs->next;
						}
					}
					if(exists == 0) {
						if(error == 1) {
							FREE(client);
						} else {
							tmp_clients = clients;
							if(tmp_clients) {
								while(tmp_clients->next != NULL) {
									tmp_clients = tmp_clients->next;
								}
								tmp_clients->next = client;
							} else {
								client->next = clients;
								clients = client;
							}
						}
					}
					socket_write(sd, "{\"status\":\"success\"}");
				} else if(strcmp(action, "send") == 0) {
					if(send_queue(json, SENDER) == 0) {
						socket_write(sd, "{\"status\":\"success\"}");
					} else {
						socket_write(sd, "{\"status\":\"failed\"}");
					}
				} else if(strcmp(action, "control") == 0) {
					struct JsonNode *code = NULL;
					struct devices_t *dev = NULL;
					char *device = NULL;
					if((code = json_find_member(json, "code")) == NULL || code->tag != JSON_OBJECT) {
						logprintf(LOG_ERR, "client did not send any codes");
					} else {
						/* Check if a location and device are given */
						if(json_find_string(code, "device", &device) != 0) {
							logprintf(LOG_ERR, "client did not send a device");
						/* Check if the device and location exists in the config file */
						} else if(devices_get(device, &dev) == 0) {
							char *state = NULL;
							struct JsonNode *values = NULL;

							json_find_string(code, "state", &state);
							if((values = json_find_member(code, "values")) != NULL) {
								values = json_first_child(values);
							}

							if(control_device(dev, state, values, SENDER) == 0) {
								socket_write(sd, "{\"status\":\"success\"}");
							} else {
								socket_write(sd, "{\"status\":\"failed\"}");
							}
						} else {
							logprintf(LOG_ERR, "the device \"%s\" does not exist", device);
						}
					}
				} else if(strcmp(action, "registry") == 0) {
					struct JsonNode *value = NULL;
					char *type = NULL;
					char *key = NULL;
					char *sval = NULL;
					double nval = 0.0;
					int dec = 0;
					if(json_find_string(json, "type", &type) != 0) {
						logprintf(LOG_ERR, "client did not send a type of action");
					} else {
						if(strcmp(type, "set") == 0) {
							if(json_find_string(json, "key", &key) != 0) {
								logprintf(LOG_ERR, "client did not send a registry key");
								socket_write(sd, "{\"status\":\"failed\"}");
							} else if((value = json_find_member(json, "value")) == NULL) {
								logprintf(LOG_ERR, "client did not send a registry value");
								socket_write(sd, "{\"status\":\"failed\"}");
							} else {
								if(value->tag == JSON_NUMBER) {
									if(registry_set_number(key, value->number_, value->decimals_) == 0) {
										socket_write(sd, "{\"status\":\"success\"}");
									} else {
										socket_write(sd, "{\"status\":\"failed\"}");
									}
								} else if(value->tag == JSON_STRING) {
									if(registry_set_string(key, value->string_) == 0) {
										socket_write(sd, "{\"status\":\"success\"}");
									} else {
										socket_write(sd, "{\"status\":\"failed\"}");
									}
								} else {
									logprintf(LOG_ERR, "registry value can only be a string or number");
									socket_write(sd, "{\"status\":\"failed\"}");
								}
							}
						} else if(strcmp(type, "remove") == 0) {
							if(json_find_string(json, "key", &key) != 0) {
								logprintf(LOG_ERR, "client did not send a registry key");
								socket_write(sd, "{\"status\":\"failed\"}");
							} else {
								if(registry_remove_value(key) == 0) {
									socket_write(sd, "{\"status\":\"success\"}");
								} else {
									socket_write(sd, "{\"status\":\"failed\"}");
								}
							}
						} else if(strcmp(type, "get") == 0) {
							if(json_find_string(json, "key", &key) != 0) {
								logprintf(LOG_ERR, "client did not send a registry key");
								socket_write(sd, "{\"status\":\"failed\"}");
							} else {
								if(registry_get_number(key, &nval, &dec) == 0) {
									struct JsonNode *jsend = json_mkobject();
									json_append_member(jsend, "message", json_mkstring("registry"));
									json_append_member(jsend, "value", json_mknumber(nval, dec));
									json_append_member(jsend, "key", json_mkstring(key));
									char *output = json_stringify(jsend, NULL);
									socket_write(sd, output);
									json_free(output);
									json_delete(jsend);
								} else if(registry_get_string(key, &sval) == 0) {
									struct JsonNode *jsend = json_mkobject();
									json_append_member(jsend, "message", json_mkstring("registry"));
									json_append_member(jsend, "value", json_mkstring(sval));
									json_append_member(jsend, "key", json_mkstring(key));
									char *output = json_stringify(jsend, NULL);
									socket_write(sd, output);
									json_free(output);
									json_delete(jsend);
								} else {
									logprintf(LOG_ERR, "registry key '%s' doesn't exists", key);
									socket_write(sd, "{\"status\":\"failed\"}");
								}
							}
						}
					}
				} else if(strcmp(action, "request config") == 0) {
					struct JsonNode *jsend = json_mkobject();
					struct JsonNode *jconfig = NULL;
					if(client->forward == 1) {
						jconfig = config_print(CONFIG_FORWARD, client->media);
					} else {
						jconfig = config_print(CONFIG_INTERNAL, client->media);
					}
					json_append_member(jsend, "message", json_mkstring("config"));
					json_append_member(jsend, "config", jconfig);
					char *output = json_stringify(jsend, NULL);
					str_replace("%", "%%", &output);
					socket_write(sd, output);
					json_free(output);
					json_delete(jsend);
				} else if(strcmp(action, "request values") == 0) {
					struct JsonNode *jsend = json_mkobject();
					struct JsonNode *jvalues = devices_values(client->media);
					json_append_member(jsend, "message", json_mkstring("values"));
					json_append_member(jsend, "values", jvalues);
					char *output = json_stringify(jsend, NULL);
					socket_write(sd, output);
					json_free(output);
					json_delete(jsend);
				/*
				 * Parse received codes from nodes
				 */
				} else if(strcmp(action, "update") == 0) {
					struct JsonNode *jvalues = NULL;
					char *pname = NULL;
					if((jvalues = json_find_member(json, "values")) != NULL) {
						exists = 0;
						tmp_clients = clients;
						while(tmp_clients) {
							if(tmp_clients->id == sd) {
								exists = 1;
								client = tmp_clients;
								break;
							}
							tmp_clients = tmp_clients->next;
						}
						if(exists) {
							json_find_number(jvalues, "ram", &client->ram);
							json_find_number(jvalues, "cpu", &client->cpu);
						}
					}
					if(json_find_string(json, "protocol", &pname) == 0) {
						broadcast_queue(pname, json, MASTER);
					}
				} else {
					error = 1;
				}
			} else if((json_find_string(json, "status", &status)) == 0) {
				tmp_clients = clients;
				while(tmp_clients) {
					if(tmp_clients->id == sd) {
						exists = 1;
						client = tmp_clients;
						break;
					}
					tmp_clients = tmp_clients->next;
				}
				if(strcmp(status, "success") == 0) {
					logprintf(LOG_DEBUG, "client \"%s\" successfully executed our latest request", client->uuid);
				} else if(strcmp(status, "failed") == 0) {
					logprintf(LOG_DEBUG, "client \"%s\" failed executing our latest request", client->uuid);
				}
			} else {
				error = 1;
			}
			json_delete(json);
		}
	}
