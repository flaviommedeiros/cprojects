if ((0
#if !defined(NO_CGI)
			     || match_prefix(conn->ctx->config[CGI_EXTENSIONS],
			                     strlen(conn->ctx->config[CGI_EXTENSIONS]),
			                     filename) > 0
#endif
#if defined(USE_LUA)
			     || match_prefix(conn->ctx->config[LUA_SCRIPT_EXTENSIONS],
			                     strlen(
			                         conn->ctx->config[LUA_SCRIPT_EXTENSIONS]),
			                     filename) > 0
#endif
#if defined(USE_DUKTAPE)
			     || match_prefix(
			            conn->ctx->config[DUKTAPE_SCRIPT_EXTENSIONS],
			            strlen(conn->ctx->config[DUKTAPE_SCRIPT_EXTENSIONS]),
			            filename) > 0
#endif
			     ) && mg_stat(conn, filename, filep)) {
				/* Shift PATH_INFO block one character right, e.g.
				 * "/x.cgi/foo/bar\x00" => "/x.cgi\x00/foo/bar\x00"
				 * conn->path_info is pointing to the local variable "path"
				 * declared in handle_request(), so PATH_INFO is not valid
				 * after handle_request returns. */
				conn->path_info = p + 1;
				memmove(p + 2, p + 1, strlen(p + 1) + 1); /* +1 is for
				                                           * trailing \0 */
				p[1] = '/';
				*is_script_resource = 1;
				break;
			} else {
				*p = '/';
			}
