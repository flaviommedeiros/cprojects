if( ( angles[0] || angles[1] || angles[2] ) 
#ifndef CM_ALLOW_ROTATED_BBOXES
		&& !cmodel->builtin
#endif
		)
		rotated = true;
	else
		rotated = false;
