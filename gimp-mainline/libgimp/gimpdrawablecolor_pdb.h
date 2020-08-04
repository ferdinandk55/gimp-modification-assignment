/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpdrawablecolor_pdb.h
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

#ifndef __GIMP_DRAWABLE_COLOR_PDB_H__
#define __GIMP_DRAWABLE_COLOR_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gboolean gimp_drawable_brightness_contrast (GimpDrawable         *drawable,
                                            gdouble               brightness,
                                            gdouble               contrast);
gboolean gimp_drawable_color_balance       (GimpDrawable         *drawable,
                                            GimpTransferMode      transfer_mode,
                                            gboolean              preserve_lum,
                                            gdouble               cyan_red,
                                            gdouble               magenta_green,
                                            gdouble               yellow_blue);
gboolean gimp_drawable_colorize_hsl        (GimpDrawable         *drawable,
                                            gdouble               hue,
                                            gdouble               saturation,
                                            gdouble               lightness);
gboolean gimp_drawable_curves_explicit     (GimpDrawable         *drawable,
                                            GimpHistogramChannel  channel,
                                            gint                  num_values,
                                            const gdouble        *values);
gboolean gimp_drawable_curves_spline       (GimpDrawable         *drawable,
                                            GimpHistogramChannel  channel,
                                            gint                  num_points,
                                            const gdouble        *points);
gboolean gimp_drawable_desaturate          (GimpDrawable         *drawable,
                                            GimpDesaturateMode    desaturate_mode);
gboolean gimp_drawable_equalize            (GimpDrawable         *drawable,
                                            gboolean              mask_only);
gboolean gimp_drawable_histogram           (GimpDrawable         *drawable,
                                            GimpHistogramChannel  channel,
                                            gdouble               start_range,
                                            gdouble               end_range,
                                            gdouble              *mean,
                                            gdouble              *std_dev,
                                            gdouble              *median,
                                            gdouble              *pixels,
                                            gdouble              *count,
                                            gdouble              *percentile);
gboolean gimp_drawable_hue_saturation      (GimpDrawable         *drawable,
                                            GimpHueRange          hue_range,
                                            gdouble               hue_offset,
                                            gdouble               lightness,
                                            gdouble               saturation,
                                            gdouble               overlap);
gboolean gimp_drawable_invert              (GimpDrawable         *drawable,
                                            gboolean              linear);
gboolean gimp_drawable_levels              (GimpDrawable         *drawable,
                                            GimpHistogramChannel  channel,
                                            gdouble               low_input,
                                            gdouble               high_input,
                                            gboolean              clamp_input,
                                            gdouble               gamma,
                                            gdouble               low_output,
                                            gdouble               high_output,
                                            gboolean              clamp_output);
gboolean gimp_drawable_levels_stretch      (GimpDrawable         *drawable);
gboolean gimp_drawable_posterize           (GimpDrawable         *drawable,
                                            gint                  levels);
gboolean gimp_drawable_threshold           (GimpDrawable         *drawable,
                                            GimpHistogramChannel  channel,
                                            gdouble               low_threshold,
                                            gdouble               high_threshold);


G_END_DECLS

#endif /* __GIMP_DRAWABLE_COLOR_PDB_H__ */
