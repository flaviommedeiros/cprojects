switch (buffer_hash)
   {
#ifdef ANDROID
      case ANDROID_ARCH_ARMV7:
         return FRONTEND_ARCH_ARM;
      case ANDROID_ARCH_ARM:
         return FRONTEND_ARCH_ARM;
#endif
      case LINUX_ARCH_X86_64:
         return FRONTEND_ARCH_X86_64;
      case LINUX_ARCH_X86:
         return FRONTEND_ARCH_X86;
      case LINUX_ARCH_ARM:
         return FRONTEND_ARCH_ARM;
      case LINUX_ARCH_PPC64:
         return FRONTEND_ARCH_PPC;
      case LINUX_ARCH_MIPS:
         return FRONTEND_ARCH_MIPS;
      case LINUX_ARCH_TILE:
         return FRONTEND_ARCH_TILE;
   }
