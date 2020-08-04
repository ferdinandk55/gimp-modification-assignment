/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimptextlayer_pdb.h
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

#ifndef __GIMP_TEXT_LAYER_PDB_H__
#define __GIMP_TEXT_LAYER_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


GimpLayer*            gimp_text_layer_new                (GimpImage             *image,
                                                          const gchar           *text,
                                                          const gchar           *fontname,
                                                          gdouble                size,
                                                          GimpUnit               unit);
gchar*                gimp_text_layer_get_text           (GimpLayer             *layer);
gboolean              gimp_text_layer_set_text           (GimpLayer             *layer,
                                                          const gchar           *text);
gchar*                gimp_text_layer_get_markup         (GimpLayer             *layer);
gchar*                gimp_text_layer_get_font           (GimpLayer             *layer);
gboolean              gimp_text_layer_set_font           (GimpLayer             *layer,
                                                          const gchar           *font);
gdouble               gimp_text_layer_get_font_size      (GimpLayer             *layer,
                                                          GimpUnit              *unit);
gboolean              gimp_text_layer_set_font_size      (GimpLayer             *layer,
                                                          gdouble                font_size,
                                                          GimpUnit               unit);
gboolean              gimp_text_layer_get_antialias      (GimpLayer             *layer);
gboolean              gimp_text_layer_set_antialias      (GimpLayer             *layer,
                                                          gboolean               antialias);
GimpTextHintStyle     gimp_text_layer_get_hint_style     (GimpLayer             *layer);
gboolean              gimp_text_layer_set_hint_style     (GimpLayer             *layer,
                                                          GimpTextHintStyle      style);
gboolean              gimp_text_layer_get_kerning        (GimpLayer             *layer);
gboolean              gimp_text_layer_set_kerning        (GimpLayer             *layer,
                                                          gboolean               kerning);
gchar*                gimp_text_layer_get_language       (GimpLayer             *layer);
gboolean              gimp_text_layer_set_language       (GimpLayer             *layer,
                                                          const gchar           *language);
GimpTextDirection     gimp_text_layer_get_base_direction (GimpLayer             *layer);
gboolean              gimp_text_layer_set_base_direction (GimpLayer             *layer,
                                                          GimpTextDirection      direction);
GimpTextJustification gimp_text_layer_get_justification  (GimpLayer             *layer);
gboolean              gimp_text_layer_set_justification  (GimpLayer             *layer,
                                                          GimpTextJustification  justify);
gboolean              gimp_text_layer_get_color          (GimpLayer             *layer,
                                                          GimpRGB               *color);
gboolean              gimp_text_layer_set_color          (GimpLayer             *layer,
                                                          const GimpRGB         *color);
gdouble               gimp_text_layer_get_indent         (GimpLayer             *layer);
gboolean              gimp_text_layer_set_indent         (GimpLayer             *layer,
                                                          gdouble                indent);
gdouble               gimp_text_layer_get_line_spacing   (GimpLayer             *layer);
gboolean              gimp_text_layer_set_line_spacing   (GimpLayer             *layer,
                                                          gdouble                line_spacing);
gdouble               gimp_text_layer_get_letter_spacing (GimpLayer             *layer);
gboolean              gimp_text_layer_set_letter_spacing (GimpLayer             *layer,
                                                          gdouble                letter_spacing);
gboolean              gimp_text_layer_resize             (GimpLayer             *layer,
                                                          gdouble                width,
                                                          gdouble                height);


G_END_DECLS

#endif /* __GIMP_TEXT_LAYER_PDB_H__ */