#if !defined(USE_TCP_LOOPBACK)
if (stat(cliaddr.sun_path, &sb) < 0)
					LogMsg("%3d: read_msg: stat failed â%sâ errno %d (%s)", req->sd, cliaddr.sun_path, dnssd_errno, dnssd_strerror(dnssd_errno));
				else
					LogMsg("%3d: read_msg: file â%sâ mode %o (octal) uid %d gid %d", req->sd, cliaddr.sun_path, sb.st_mode, sb.st_uid, sb.st_gid);
