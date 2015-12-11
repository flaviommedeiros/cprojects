#ifndef OPENSSL_NO_EC2M
if (is_char_two) {
        if (!EC_POINT_set_affine_coordinates_GF2m(key->group, point,
                                                  x, y, ctx))
            goto err;
        if (!EC_POINT_get_affine_coordinates_GF2m(key->group, point,
                                                  tx, ty, ctx))
            goto err;
    } else
#endif
    {
        if (!EC_POINT_set_affine_coordinates_GFp(key->group, point,
                                                 x, y, ctx))
            goto err;
        if (!EC_POINT_get_affine_coordinates_GFp(key->group, point,
                                                 tx, ty, ctx))
            goto err;
    }
