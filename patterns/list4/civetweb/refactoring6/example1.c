if (0
#if !defined(NO_CGI)
		    || match_prefix(conn->ctx->config[CGI_EXTENSIONS],
		                    strlen(conn->ctx->config[CGI_EXTENSIONS]),
		                    filename) > 0
#endif
#if defined(USE_LUA)
		    || match_prefix(conn->ctx->config[LUA_SCRIPT_EXTENSIONS],
		                    strlen(conn->ctx->config[LUA_SCRIPT_EXTENSIONS]),
		                    filename) > 0
#endif
#if defined(USE_DUKTAPE)
		    || match_prefix(conn->ctx->config[DUKTAPE_SCRIPT_EXTENSIONS],
		                    strlen(
		                        conn->ctx->config[DUKTAPE_SCRIPT_EXTENSIONS]),
		                    filename) > 0
#endif
		    ) {
			/* The request addresses a CGI script or a Lua script. The URI
			 * corresponds to the script itself (like /path/script.cgi),
			 * and there is no additional resource path
			 * (like /path/script.cgi/something).
			 * Requests that modify (replace or delete) a resource, like
			 * PUT and DELETE requests, should replace/delete the script
			 * file.
			 * Requests that read or write from/to a resource, like GET and
			 * POST requests, should call the script and return the
			 * generated response. */
			*is_script_resource = !*is_put_or_delete_request;
		}
