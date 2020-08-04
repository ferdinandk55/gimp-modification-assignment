/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpprocedureaction.c
 * Copyright (C) 2004-2016 Michael Natterer <mitch@gimp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <gtk/gtk.h>
#include <gegl.h>

#include "widgets-types.h"

#include "libgimpbase/gimpbase.h"

#include "pdb/gimpprocedure.h"

#include "gimpaction.h"
#include "gimpaction-history.h"
#include "gimpprocedureaction.h"
#include "gimpwidgets-utils.h"


enum
{
  PROP_0,
  PROP_PROCEDURE
};


static void   gimp_procedure_action_finalize      (GObject      *object);
static void   gimp_procedure_action_set_property  (GObject      *object,
                                                   guint         prop_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec);
static void   gimp_procedure_action_get_property  (GObject      *object,
                                                   guint         prop_id,
                                                   GValue       *value,
                                                   GParamSpec   *pspec);

static void   gimp_procedure_action_activate      (GtkAction    *action);
static void   gimp_procedure_action_connect_proxy (GtkAction    *action,
                                                   GtkWidget    *proxy);


G_DEFINE_TYPE (GimpProcedureAction, gimp_procedure_action,
               GIMP_TYPE_ACTION_IMPL)

#define parent_class gimp_procedure_action_parent_class


static void
gimp_procedure_action_class_init (GimpProcedureActionClass *klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkActionClass *action_class = GTK_ACTION_CLASS (klass);

  object_class->finalize      = gimp_procedure_action_finalize;
  object_class->set_property  = gimp_procedure_action_set_property;
  object_class->get_property  = gimp_procedure_action_get_property;

  action_class->activate      = gimp_procedure_action_activate;
  action_class->connect_proxy = gimp_procedure_action_connect_proxy;

  g_object_class_install_property (object_class, PROP_PROCEDURE,
                                   g_param_spec_object ("procedure",
                                                        NULL, NULL,
                                                        GIMP_TYPE_PROCEDURE,
                                                        GIMP_PARAM_READWRITE));
}

static void
gimp_procedure_action_init (GimpProcedureAction *action)
{
}

static void
gimp_procedure_action_finalize (GObject *object)
{
  GimpProcedureAction *action = GIMP_PROCEDURE_ACTION (object);

  g_clear_object (&action->procedure);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gimp_procedure_action_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  GimpProcedureAction *action = GIMP_PROCEDURE_ACTION (object);

  switch (prop_id)
    {
    case PROP_PROCEDURE:
      g_value_set_object (value, action->procedure);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
gimp_procedure_action_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  GimpProcedureAction *action = GIMP_PROCEDURE_ACTION (object);

  switch (prop_id)
    {
    case PROP_PROCEDURE:
      if (action->procedure)
        g_object_unref (action->procedure);
      action->procedure = g_value_dup_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
gimp_procedure_action_activate (GtkAction *action)
{
  GimpProcedureAction *procedure_action = GIMP_PROCEDURE_ACTION (action);

  /* Not all actions have procedures associated with them, for example
   * unused "filters-recent-[N]" actions, so check for NULL before we
   * invoke the action
   */
  if (procedure_action->procedure)
    {
      gsize hack = GPOINTER_TO_SIZE (procedure_action->procedure);

      gimp_action_emit_activate (GIMP_ACTION (action),
                                 g_variant_new_uint64 (hack));

      gimp_action_history_action_activated (GIMP_ACTION (action));
    }
}

static void
gimp_procedure_action_connect_proxy (GtkAction *action,
                                     GtkWidget *proxy)
{
  GimpProcedureAction *procedure_action = GIMP_PROCEDURE_ACTION (action);

  GTK_ACTION_CLASS (parent_class)->connect_proxy (action, proxy);

  if (GTK_IS_MENU_ITEM (proxy) && procedure_action->procedure)
    {
      GdkPixbuf *pixbuf;

      g_object_get (procedure_action->procedure,
                    "icon-pixbuf", &pixbuf,
                    NULL);

      if (pixbuf)
        {
          GtkWidget *image;
          gint       width;
          gint       height;

          gtk_icon_size_lookup (GTK_ICON_SIZE_MENU, &width, &height);

          if (width  != gdk_pixbuf_get_width  (pixbuf) ||
              height != gdk_pixbuf_get_height (pixbuf))
            {
              GdkPixbuf *copy;

              copy = gdk_pixbuf_scale_simple (pixbuf, width, height,
                                              GDK_INTERP_BILINEAR);
              g_object_unref (pixbuf);
              pixbuf = copy;
            }

          image = gtk_image_new_from_pixbuf (pixbuf);
          gimp_menu_item_set_image (GTK_MENU_ITEM (proxy), image);
          g_object_unref (pixbuf);
        }
    }
}


/*  public functions  */

GimpProcedureAction *
gimp_procedure_action_new (const gchar   *name,
                           const gchar   *label,
                           const gchar   *tooltip,
                           const gchar   *icon_name,
                           const gchar   *help_id,
                           GimpProcedure *procedure)
{
  GimpProcedureAction *action;

  action = g_object_new (GIMP_TYPE_PROCEDURE_ACTION,
                         "name",       name,
                         "label",      label,
                         "tooltip",    tooltip,
                         "icon-name",  icon_name,
                         "procedure",  procedure,
                         NULL);

  gimp_action_set_help_id (GIMP_ACTION (action), help_id);

  return action;
}
