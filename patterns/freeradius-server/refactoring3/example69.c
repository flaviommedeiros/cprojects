switch (name->type) {
#ifdef GEN_EMAIL
				case GEN_EMAIL:
					ADD_CERT_ATTR(cert_attr_names[FR_TLS_SAN_EMAIL][lookup],
						      (char *) ASN1_STRING_data(name->d.rfc822Name));
					break;
#endif	/* GEN_EMAIL */
#ifdef GEN_DNS
				case GEN_DNS:
					ADD_CERT_ATTR(cert_attr_names[FR_TLS_SAN_DNS][lookup],
						      (char *) ASN1_STRING_data(name->d.dNSName));
					break;
#endif	/* GEN_DNS */
#ifdef GEN_OTHERNAME
				case GEN_OTHERNAME:
					/* look for a MS UPN */
					if (NID_ms_upn != OBJ_obj2nid(name->d.otherName->type_id)) break;

					/* we've got a UPN - Must be ASN1-encoded UTF8 string */
					if (name->d.otherName->value->type == V_ASN1_UTF8STRING) {
						ADD_CERT_ATTR(cert_attr_names[FR_TLS_SAN_UPN][lookup],
							      (char *) name->d.otherName->value->value.utf8string);
						break;
					}

					RWARN("Invalid UPN in Subject Alt Name (should be UTF-8)");
					break;
#endif	/* GEN_OTHERNAME */
				default:
					/* XXX TODO handle other SAN types */
					break;
				}
