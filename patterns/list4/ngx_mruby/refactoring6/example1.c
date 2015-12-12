if (fprintf(fp,
          "const uint8_t\n"
          "#if defined __GNUC__\n"
          "__attribute__((aligned(%u)))\n"
          "#elif defined _MSC_VER\n"
          "__declspec(align(%u))\n"
          "#endif\n"
          "%s[] = {",
          (uint16_t)MRB_DUMP_ALIGNMENT, (uint16_t)MRB_DUMP_ALIGNMENT, initname) < 0) {
      mrb_free(mrb, bin);
      return MRB_DUMP_WRITE_FAULT;
    }
