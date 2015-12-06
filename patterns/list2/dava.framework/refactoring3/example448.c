switch (Renderer)
	{
		#ifdef ILUT_USE_OPENGL
		case ILUT_OPENGL:
			return ilutGLInit();
		#endif

		#ifdef ILUT_USE_WIN32
		case ILUT_WIN32:
			return ilutWin32Init();
		#endif

		#ifdef ILUT_USE_DIRECTX8
		case ILUT_DIRECT3D8:
			return ilutD3D8Init();
		#endif

		#ifdef ILUT_USE_DIRECTX9
        case ILUT_DIRECT3D9:
        	return ilutD3D9Init();
        #endif
		
		#ifdef ILUT_USE_DIRECTX10
        case ILUT_DIRECT3D10:
        	return ilutD3D10Init();
        #endif

		default:
			ilSetError(ILUT_NOT_SUPPORTED);
	}
