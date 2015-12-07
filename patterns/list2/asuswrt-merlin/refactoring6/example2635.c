if (u->scheme == SCHEME_HTTP
#ifdef HAVE_SSL
      || u->scheme == SCHEME_HTTPS
#endif
      || (proxy_url && proxy_url->scheme == SCHEME_HTTP))
    {
      result = http_loop (u, orig_parsed, &mynewloc, &local_file, refurl, dt,
                          proxy_url, iri);
    }
  else if (u->scheme == SCHEME_FTP)
    {
      /* If this is a redirection, temporarily turn off opt.ftp_glob
         and opt.recursive, both being undesirable when following
         redirects.  */
      bool oldrec = recursive, glob = opt.ftp_glob;
      if (redirection_count)
        oldrec = glob = false;

      result = ftp_loop (u, &local_file, dt, proxy_url, recursive, glob);
      recursive = oldrec;

      /* There is a possibility of having HTTP being redirected to
         FTP.  In these cases we must decide whether the text is HTML
         according to the suffix.  The HTML suffixes are `.html',
         `.htm' and a few others, case-insensitive.  */
      if (redirection_count && local_file && u->scheme == SCHEME_FTP)
        {
          if (has_html_suffix_p (local_file))
            *dt |= TEXTHTML;
        }
    }
