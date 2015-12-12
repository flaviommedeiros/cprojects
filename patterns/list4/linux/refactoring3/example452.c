switch (nb) {
	case 1:
		err = __get_user(x, (unsigned char __user *) ea);
		break;
	case 2:
		err = __get_user(x, (unsigned short __user *) ea);
		break;
	case 4:
		err = __get_user(x, (unsigned int __user *) ea);
		break;
#ifdef __powerpc64__
	case 8:
		err = __get_user(x, (unsigned long __user *) ea);
		break;
#endif
	}
