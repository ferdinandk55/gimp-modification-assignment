/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimagecolorprofile_pdb.h
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

#ifndef __GIMP_IMAGE_COLOR_PROFILE_PDB_H__
#define __GIMP_IMAGE_COLOR_PROFILE_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


G_GNUC_INTERNAL guint8*  _gimp_image_get_color_profile              (GimpImage                *image,
                                                                     gint                     *num_bytes);
G_GNUC_INTERNAL guint8*  _gimp_image_get_effective_color_profile    (GimpImage                *image,
                                                                     gint                     *num_bytes);
G_GNUC_INTERNAL gboolean _gimp_image_set_color_profile              (GimpImage                *image,
                                                                     gint                      num_bytes,
                                                                     const guint8             *color_profile);
gboolean                 gimp_image_set_color_profile_from_file     (GimpImage                *image,
                                                                     GFile                    *file);
G_GNUC_INTERNAL gboolean _gimp_image_convert_color_profile          (GimpImage                *image,
                                                                     gint                      num_bytes,
                                                                     const guint8             *color_profile,
                                                                     GimpColorRenderingIntent  intent,
                                                                     gboolean                  bpc);
gboolean                 gimp_image_convert_color_profile_from_file (GimpImage                *image,
                                                                     GFile                    *file,
                                                                     GimpColorRenderingIntent  intent,
                                                                     gboolean                  bpc);


G_END_DECLS

#endif /* __GIMP_IMAGE_COLOR_PROFILE_PDB_H__ */