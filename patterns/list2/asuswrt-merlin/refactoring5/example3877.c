#ifdef CONFIG_NCPFS_NFS_NS
if (server->name_space[volnum]==NW_NS_NFS)
 	{
 		int result;
 
 		result=ncp_obtain_DOS_dir_base(server, volnum, dirent, name, &dirent);
 		if (result) return result;
 		return ncp_DeleteNSEntry(server, 1, volnum, dirent, NULL, NW_NS_DOS, cpu_to_le16(0x8006));
 	}
 	else
#endif	/* CONFIG_NCPFS_NFS_NS */
 		return ncp_DeleteNSEntry(server, 1, volnum, dirent, name, server->name_space[volnum], cpu_to_le16(0x8006));
