if (!(p1 = (t_UBSEC_ubsec_bytes_to_bits *)
          DSO_bind_func(ubsec_dso, UBSEC_F1))
        || !(p2 = (t_UBSEC_ubsec_bits_to_bytes *)
             DSO_bind_func(ubsec_dso, UBSEC_F2))
        || !(p3 = (t_UBSEC_ubsec_open *)
             DSO_bind_func(ubsec_dso, UBSEC_F3))
        || !(p4 = (t_UBSEC_ubsec_close *)
             DSO_bind_func(ubsec_dso, UBSEC_F4))
#  ifndef OPENSSL_NO_DH
        || !(p5 = (t_UBSEC_diffie_hellman_generate_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F5))
        || !(p6 = (t_UBSEC_diffie_hellman_agree_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F6))
#  endif
/* #ifndef OPENSSL_NO_RSA */
        || !(p7 = (t_UBSEC_rsa_mod_exp_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F7))
        || !(p8 = (t_UBSEC_rsa_mod_exp_crt_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F8))
/* #endif */
#  ifndef OPENSSL_NO_DSA
        || !(p9 = (t_UBSEC_dsa_sign_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F9))
        || !(p10 = (t_UBSEC_dsa_verify_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F10))
#  endif
        || !(p11 = (t_UBSEC_math_accelerate_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F11))
        || !(p12 = (t_UBSEC_rng_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F12))
        || !(p13 = (t_UBSEC_max_key_len_ioctl *)
             DSO_bind_func(ubsec_dso, UBSEC_F13))) {
        UBSECerr(UBSEC_F_UBSEC_INIT, UBSEC_R_DSO_FAILURE);
        goto err;
    }
