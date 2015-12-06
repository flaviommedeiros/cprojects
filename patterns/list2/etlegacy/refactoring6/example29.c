if (!FS_IsExt(filename, ".cfg", len) &&      // for config files
			    !FS_IsExt(filename, ".menu", len) &&    // menu files
			    !FS_IsExt(filename, ".game", len) &&    // menu files
			    !FS_IsExt(filename, ".dat", len) &&     // for journal files
			    !FS_IsExt(filename, ".bin", len) &&     // glsl shader binary
#ifdef LEGACY_DEBUG
			    !FS_IsExt(filename, ".glsl", len) &&
#endif
			    !FS_IsDemoExt(filename, len))           // demos
			{
				*file = 0;
				return -1;
			}
