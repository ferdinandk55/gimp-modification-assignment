/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimageconvert_pdb.h
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl */

#if !defined (__GIMP_H_INSIDE__) && !defined (GIMP_COMPILATION)
#error "Only <libgimp/gimp.h> can be included directly."
#endif

#ifndef __GIMP_IMAGE_CONVERT_PDB_H__
#define __GIMP_IMAGE_CONVERT_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gboolean gimp_image_convert_rgb               (GimpImage              *image);
gboolean gimp_image_convert_grayscale         (GimpImage              *image);
gboolean gimp_image_convert_indexed           (GimpImage              *image,
                                               GimpConvertDitherType   dither_type,
                                               GimpConvertPaletteType  palette_type,
                                               gint                    num_cols,
                                               gboolean                alpha_dither,
                                               gboolean                remove_unused,
                                               const gchar            *palette);
gboolean gimp_image_convert_set_dither_matrix (gint                    width,
                                               gint                    height,
                                               gint                    matrix_length,
                                               const guint8           *matrix);
gboolean gimp_image_convert_precision         (GimpImage              *image,
                                               GimpPrecision           precision);


G_END_DECLS

#endif /* __GIMP_IMAGE_CONVERT_PDB_H__ */
