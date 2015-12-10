#if (EMULATE_AXIM_X30 == 0)
if( _tcsncmp(oemstr, L"Dell Axim X30", 13) == 0 )
#endif
		{
			GXDeviceInfo gxInfo = {0};
			HDC hdc = GetDC(NULL);
			int result;

			gxInfo.Version = 100;
			result = ExtEscape(hdc, GETGXINFO, 0, NULL, sizeof(gxInfo), (char *)&gxInfo);
			if( result > 0 )
			{
				this->hidden->useGXOpenDisplay = 0;
				this->hidden->videoMem = gxInfo.pvFrameBuffer;
				this->hidden->needUpdate = 0;
				this->hidden->gxProperties.cbxPitch = 2;
				this->hidden->gxProperties.cbyPitch = 480;
				this->hidden->gxProperties.cxWidth = gxInfo.cxWidth;
				this->hidden->gxProperties.cyHeight = gxInfo.cyHeight;
				this->hidden->gxProperties.ffFormat = gxInfo.ffFormat;
			}
		}
