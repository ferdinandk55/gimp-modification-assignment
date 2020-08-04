# GIMP - The GNU Image Manipulation Program
# Copyright (C) 1998-2003 Manish Singh <yosh@gimp.org>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

package Gimp::CodeGen::pdb;

%arg_types = (
    int32       => { name            => 'INT32',
		     gtype           => 'G_TYPE_INT',
		     type            => 'gint ',
		     const_type      => 'gint ',
		     init_value      => '0',
		     get_value_func  => '$var = g_value_get_int ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_INT ($value)',
		     set_value_func  => 'g_value_set_int ($value, $var)',
		     take_value_func => 'g_value_set_int ($value, $var)' },

    uchar       => { name            => 'UCHAR',
		     gtype           => 'G_TYPE_UCHAR',
		     type            => 'guchar ',
		     const_type      => 'guchar ',
		     init_value      => '0',
		     get_value_func  => '$var = g_value_get_uchar ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_UVHAR ($value)',
		     set_value_func  => 'g_value_set_uchar ($value, $var)',
		     take_value_func => 'g_value_set_uchar ($value, $var)' },

    float       => { name            => 'FLOAT',
		     gtype           => 'G_TYPE_DOUBLE',
		     type            => 'gdouble ',
		     const_type      => 'gdouble ',
		     init_value      => '0.0',
		     get_value_func  => '$var = g_value_get_double ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_DOUBLE ($value)',
		     set_value_func  => 'g_value_set_double ($value, $var)',
		     take_value_func => 'g_value_set_double ($value, $var)' },

    string      => { name            => 'STRING',
		     gtype           => 'G_TYPE_STRING',
		     type            => 'gchar *',
		     const_type      => 'const gchar *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer full)',
		     get_value_func  => '$var = g_value_get_string ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_STRING ($value)',
		     set_value_func  => 'g_value_set_string ($value, $var)',
		     take_value_func => 'g_value_take_string ($value, $var)' },

    int32array  => { name            => 'INT32ARRAY',
		     gtype           => 'GIMP_TYPE_INT32_ARRAY',
		     type            => 'gint32 *',
		     const_type      => 'const gint32 *',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type gint32)',
		     out_annotate    => '(element-type gint32) (transfer full)',
		     get_value_func  => '$var = gimp_value_get_int32_array ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_INT32_ARRAY ($value)',
		     set_value_func  => 'gimp_value_set_int32_array ($value, $var, $var_len)',
		     take_value_func => 'gimp_value_take_int32_array ($value, $var, $var_len)' },

    int16array  => { name            => 'INT16ARRAY',
		     gtype           => 'GIMP_TYPE_INT16_ARRAY',
		     type            => 'gint16 *',
		     const_type      => 'const gint16 *',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type gint16)',
		     out_annotate    => '(element-type gint16) (transfer full)',
		     get_value_func  => '$var = gimp_value_get_int16_array ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_INT16_ARRAY ($value)',
		     set_value_func  => 'gimp_value_set_int16_array ($value, $var, $var_len)',
		     take_value_func => 'gimp_value_take_int16_array ($value, $var, $var_len)' },

    int8array   => { name            => 'INT8ARRAY',
		     gtype           => 'GIMP_TYPE_UINT8_ARRAY',
		     type            => 'guint8 *',
		     const_type      => 'const guint8 *',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type guint8)',
		     out_annotate    => '(element-type guint8) (transfer full)',
		     get_value_func  => '$var = gimp_value_get_uint8_array ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_UINT8_ARRAY ($value)',
		     set_value_func  => 'gimp_value_set_uint8_array ($value, $var, $var_len)',
		     take_value_func => 'gimp_value_take_uint8_array ($value, $var, $var_len)' },

    floatarray  => { name            => 'FLOATARRAY',
		     gtype           => 'GIMP_TYPE_FLOAT_ARRAY',
		     type            => 'gdouble *',
		     const_type      => 'const gdouble *',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type gdouble)',
		     out_annotate    => '(element-type gdouble) (transfer full)',
		     get_value_func  => '$var = gimp_value_get_float_array ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_FLOAT_ARRAY ($value)',
		     set_value_func  => 'gimp_value_set_float_array ($value, $var, $var_len)',
		     take_value_func => 'gimp_value_take_float_array ($value, $var, $var_len)' },

    stringarray => { name            => 'STRINGARRAY',
		     gtype           => 'GIMP_TYPE_STRING_ARRAY',
		     type            => 'gchar **',
		     const_type      => 'const gchar **',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type gchar*)',
		     out_annotate    => '(element-type gchar*) (transfer full)',
		     get_value_func  => '$var = gimp_value_get_string_array ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_STRING_ARRAY ($value)',
		     set_value_func  => 'gimp_value_set_string_array ($value, $var, $var_len)',
		     take_value_func => 'gimp_value_take_string_array ($value, $var, $var_len)' },

    colorarray  => { name            => 'COLORARRAY',
		     gtype           => 'GIMP_TYPE_RGB_ARRAY',
		     type            => 'GimpRGB *',
		     const_type      => 'const GimpRGB *',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type GimpRGB)',
		     out_annotate    => '(element-type GimpRGB) (transfer full)',
		     get_value_func  => '$var = gimp_value_get_rgb_array ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_RGB_ARRAY ($value)',
		     set_value_func  => 'gimp_value_set_rgb_array ($value, $var, $var_len)',
		     take_value_func => 'gimp_value_take_rgb_array ($value, $var, $var_len)' },

    imagearray  => { name            => 'IMAGEARRAY',
		     gtype           => 'GIMP_TYPE_OBJECT_ARRAY',
		     type            => 'GimpImage **',
		     const_type      => 'const GimpImage **',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type GimpImage)',
		     out_annotate    => '(element-type GimpImage) (transfer container)',
		     get_value_func  => '$var = (const GimpImage **) gimp_value_get_object_array ($value)',
		     dup_value_func  => '{ GimpObjectArray *a = g_value_get_boxed (gimp_value_array_index ($value)); if (a) $var = g_memdup (a->data, a->length * sizeof (gpointer)); }',
		     set_value_func  => 'gimp_value_set_object_array ($value, GIMP_TYPE_IMAGE, (GObject **) $var, $var_len)',
		     take_value_func => 'gimp_value_take_object_array ($value, GIMP_TYPE_IMAGE, (GObject **) $var, $var_len)' },

    itemarray   => { name            => 'ITEMARRAY',
		     gtype           => 'GIMP_TYPE_OBJECT_ARRAY',
		     type            => 'GimpItem **',
		     const_type      => 'const GimpItem **',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type GimpItem)',
		     out_annotate    => '(element-type GimpItem) (transfer container)',
		     get_value_func  => '$var = (const GimpItem **) gimp_value_get_object_array ($value)',
		     dup_value_func  => '{ GimpObjectArray *a = g_value_get_boxed (gimp_value_array_index ($value)); if (a) $var = g_memdup (a->data, a->length * sizeof (gpointer)); }',
		     set_value_func  => 'gimp_value_set_object_array ($value, GIMP_TYPE_ITEM, (GObject **) $var, $var_len)',
		     take_value_func => 'gimp_value_take_object_array ($value, GIMP_TYPE_ITEM, (GObject **) $var, $var_len)' },

    layerarray  => { name            => 'LAYERARRAY',
		     gtype           => 'GIMP_TYPE_OBJECT_ARRAY',
		     type            => 'GimpLayer **',
		     const_type      => 'const GimpLayer **',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type GimpLayer)',
		     out_annotate    => '(element-type GimpLayer) (transfer container)',
		     get_value_func  => '$var = (const GimpLayer **) gimp_value_get_object_array ($value)',
		     dup_value_func  => '{ GimpObjectArray *a = g_value_get_boxed (gimp_value_array_index ($value)); if (a) $var = g_memdup (a->data, a->length * sizeof (gpointer)); }',
		     set_value_func  => 'gimp_value_set_object_array ($value, GIMP_TYPE_LAYER, (GObject **) $var, $var_len)',
		     take_value_func => 'gimp_value_take_object_array ($value, GIMP_TYPE_LAYER, (GObject **) $var, $var_len)' },

    channelarray => { name            => 'CHANNELARRAY',
		     gtype           => 'GIMP_TYPE_OBJECT_ARRAY',
		     type            => 'GimpChannel **',
		     const_type      => 'const GimpChannel **',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type GimpChannel)',
		     out_annotate    => '(element-type GimpChannel) (transfer container)',
		     get_value_func  => '$var = gimp_value_get_object_array ($value)',
		     dup_value_func  => '{ GimpObjectArray *a = g_value_get_boxed (gimp_value_array_index ($value)); if (a) $var = g_memdup (a->data, a->length * sizeof (gpointer)); }',
		     set_value_func  => 'gimp_value_set_object_array ($value, GIMP_TYPE_CHANNEL, (GObject **) $var, $var_len)',
		     take_value_func => 'gimp_value_take_object_array ($value, GIMP_TYPE_CHANNEL, (GObject **) $var, $var_len)' },

    vectorarray => { name            => 'VECTORSARRAY',
		     gtype           => 'GIMP_TYPE_OBJECT_ARRAY',
		     type            => 'GimpVectors **',
		     const_type      => 'const GimpVectors **',
		     array           => 1,
		     init_value      => 'NULL',
		     in_annotate     => '(element-type GimpVectors)',
		     out_annotate    => '(element-type GimpVectors) (transfer container)',
		     get_value_func  => '$var = (const GimpVectors **) gimp_value_get_object_array ($value)',
		     dup_value_func  => '{ GimpObjectArray *a = g_value_get_boxed (gimp_value_array_index ($value)); if (a) $var = g_memdup (a->data, a->length * sizeof (gpointer)); }',
		     set_value_func  => 'gimp_value_set_object_array ($value, GIMP_TYPE_VECTORS, (GObject **) $var, $var_len)',
		     take_value_func => 'gimp_value_take_object_array ($value, GIMP_TYPE_VECTORS, (GObject **) $var, $var_len)' },

    color       => { name            => 'COLOR',
		     gtype           => 'GIMP_TYPE_RGB',
		     type            => 'GimpRGB ',
		     const_type      => 'GimpRGB ',
		     struct          => 1,
		     init_value      => '{ 0.0, 0.0, 0.0, 1.0 }',
		     get_value_func  => 'gimp_value_get_rgb ($value, &$var)',
		     dup_value_func  => 'GIMP_VALUES_GET_RGB ($value, &$var)',
		     set_value_func  => 'gimp_value_set_rgb ($value, $var)',
		     take_value_func => 'gimp_value_set_rgb ($value, &$var)',
		     headers         => [ qw(<cairo.h> "libgimpcolor/gimpcolor.h") ] },

    display     => { name            => 'DISPLAY',
		     gtype           => 'GIMP_TYPE_DISPLAY',
		     type            => 'GimpDisplay *',
		     const_type      => 'GimpDisplay *',
		     app_type        => 'GimpDisplay *',
		     app_const_type  => 'GimpDisplay *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_DISPLAY ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)' },

    image       => { name            => 'IMAGE',
		     gtype           => 'GIMP_TYPE_IMAGE',
		     type            => 'GimpImage *',
		     const_type      => 'GimpImage *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_IMAGE ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimpimage.h") ] },

    item        => { name            => 'ITEM',
		     gtype           => 'GIMP_TYPE_ITEM',
		     type            => 'GimpItem *',
		     const_type      => 'GimpItem *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_ITEM ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimpitem.h") ] },

    layer       => { name            => 'LAYER',
		     gtype           => 'GIMP_TYPE_LAYER',
		     type            => 'GimpLayer *',
		     const_type      => 'GimpLayer *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_LAYER ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimplayer.h") ] },

    channel     => { name            => 'CHANNEL',
		     gtype           => 'GIMP_TYPE_CHANNEL',
		     type            => 'GimpChannel *',
		     const_type      => 'GimpChannel *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_CHANNEL ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimpchannel.h") ] },

    drawable    => { name            => 'DRAWABLE',
		     gtype           => 'GIMP_TYPE_DRAWABLE',
		     type            => 'GimpDrawable *',
		     const_type      => 'GimpDrawable *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_DRAWABLE ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimpdrawable.h") ] },

    selection   => { name            => 'SELECTION',
		     gtype           => 'GIMP_TYPE_SELECTION',
		     type            => 'GimpSelection *',
		     const_type      => 'GimpSelection *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_SELECTION ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimpselection.h") ] },

    layer_mask  => { name            => 'CHANNEL',
		     gtype           => 'GIMP_TYPE_LAYER_MASK',
		     type            => 'GimpLayerMask *',
		     const_type      => 'GimpLayerMask *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_LAYER_MASK ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("core/gimplayermask.h") ] },

    vectors     => { name            => 'VECTORS',
		     gtype           => 'GIMP_TYPE_VECTORS',
		     type            => 'GimpVectors *',
		     const_type      => 'GimpVectors *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_VECTORS ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)',
		     headers         => [ qw("vectors/gimpvectors.h") ] },

    file        => { name            => 'FILE',
		     gtype           => 'G_TYPE_FILE',
		     type            => 'GFile *',
		     const_type      => 'GFile *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer full)',
		     get_value_func  => '$var = g_value_get_object ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_FILE ($value)',
		     set_value_func  => 'g_value_set_object ($value, $var)',
		     take_value_func => 'g_value_set_object ($value, $var)' },

    parasite    => { name            => 'PARASITE',
		     gtype           => 'GIMP_TYPE_PARASITE',
		     type            => 'GimpParasite *',
		     const_type      => 'const GimpParasite *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer full)',
		     get_value_func  => '$var = g_value_get_boxed ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_PARASITE ($value)',
		     set_value_func  => 'g_value_set_boxed ($value, $var)',
		     take_value_func => 'g_value_take_boxed ($value, $var)',
		     headers         => [ qw("libgimpbase/gimpbase.h") ] },

    param       => { name            => 'PARAM',
		     gtype           => 'G_TYPE_PARAM_SPEC',
		     type            => 'GParamSpec *',
		     const_type      => 'GParamSpec *',
		     init_value      => 'NULL',
		     out_annotate    => '(transfer full)',
		     get_value_func  => '$var = g_value_get_param ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_DUP_PARAM ($value)',
		     set_value_func  => 'g_value_set_param ($value, $var)',
		     take_value_func => 'g_value_take_param ($value, $var)' },

    # Special cases
    enum        => { name            => 'ENUM',
		     gtype           => 'G_TYPE_ENUM',
		     type            => 'gint ',
		     const_type      => 'gint ',
		     init_value      => '0',
		     get_value_func  => '$var = g_value_get_enum ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_ENUM ($value)',
		     set_value_func  => 'g_value_set_enum ($value, $var)',
		     take_value_func => 'g_value_set_enum ($value, $var)' },

    boolean     => { name            => 'BOOLEAN',
		     gtype           => 'G_TYPE_BOOLEAN',
		     type            => 'gboolean ',
		     const_type      => 'gboolean ',
		     init_value      => 'FALSE',
		     get_value_func  => '$var = g_value_get_boolean ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_BOOLEAN ($value)',
		     set_value_func  => 'g_value_set_boolean ($value, $var)',
		     take_value_func => 'g_value_set_boolean ($value, $var)' },

    tattoo      => { name            => 'TATTOO',
		     gtype           => 'G_TYPE_UINT',
		     type            => 'guint ',
		     const_type      => 'guint ',
		     init_value      => '0',
		     get_value_func  => '$var = g_value_get_uint ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_UINT ($value)',
		     set_value_func  => 'g_value_set_uint ($value, $var)',
		     take_value_func => 'g_value_set_uint ($value, $var)' },

    guide       => { name            => 'GUIDE',
		     gtype           => 'G_TYPE_UINT',
		     type            => 'guint ',
		     const_type      => 'guint ',
		     init_value      => '0',
		     get_value_func  => '$var = g_value_get_uint ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_UINT ($value)',
		     set_value_func  => 'g_value_set_uint ($value, $var)',
		     take_value_func => 'g_value_set_uint ($value, $var)' },

   sample_point => { name            => 'SAMPLE_POINT',
		     gtype           => 'G_TYPE_UINT',
		     type            => 'guint ',
		     const_type      => 'guint ',
		     init_value      => '0',
		     get_value_func  => '$var = g_value_get_uint ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_UINT ($value)',
		     set_value_func  => 'g_value_set_uint ($value, $var)',
		     take_value_func => 'g_value_set_uint ($value, $var)' },

    unit        => { name            => 'UNIT',
		     gtype           => 'GIMP_TYPE_UNIT',
		     type            => 'GimpUnit ',
		     const_type      => 'GimpUnit ',
		     init_value      => 'GIMP_UNIT_PIXEL',
		     out_annotate    => '(transfer none)',
		     get_value_func  => '$var = g_value_get_int ($value)',
		     dup_value_func  => '$var = GIMP_VALUES_GET_INT ($value)',
		     set_value_func  => 'g_value_set_int ($value, $var)',
		     take_value_func => 'g_value_set_int ($value, $var)' }
);

# Split out the parts of an arg constraint
sub arg_parse {
    my $arg = shift;

    if ($arg =~ /^enum (\w+)(.*)/) {
	my ($name, $remove) = ($1, $2);
	my @retvals = ('enum', $name);

	if ($remove && $remove =~ m@ \(no @) {
	    chop $remove; ($remove = substr($remove, 5)) =~ s/ $//;
	    push @retvals, split(/,\s*/, $remove);
	}

	return @retvals;
    }
    elsif ($arg =~ /^unit(?: \(min (.*?)\))?/) {
	my @retvals = ('unit');
	push @retvals, $1 if $1;
	return @retvals;
    }
    elsif ($arg =~ /^(?:([+-.\dA-Z_][^\s]*) \s* (<=|<))?
		     \s* (\w+) \s*
		     (?:(<=|<) \s* ([+-.\dA-Z_][^\s]*))?
		   /x) {
	return ($3, $1, $2, $5, $4);
    }
}

1;
