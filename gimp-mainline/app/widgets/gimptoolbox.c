/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
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

#include <string.h>

#include <gegl.h>
#include <gtk/gtk.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpwidgets/gimpwidgets.h"

#include "widgets-types.h"

#include "config/gimpguiconfig.h"

#include "core/gimp.h"
#include "core/gimpcontext.h"

#include "file/file-open.h"

#include "gimpcairo-wilber.h"
#include "gimpdevices.h"
#include "gimpdialogfactory.h"
#include "gimpdockwindow.h"
#include "gimphelp-ids.h"
#include "gimppanedbox.h"
#include "gimptoolbox.h"
#include "gimptoolbox-color-area.h"
#include "gimptoolbox-dnd.h"
#include "gimptoolbox-image-area.h"
#include "gimptoolbox-indicator-area.h"
#include "gimptoolpalette.h"
#include "gimpuimanager.h"
#include "gimpwidgets-utils.h"

#include "about.h"

#include "gimp-intl.h"


enum
{
  PROP_0,
  PROP_CONTEXT
};


struct _GimpToolboxPrivate
{
  GimpContext       *context;

  GtkWidget         *vbox;

  GtkWidget         *header;
  GtkWidget         *tool_palette;
  GtkWidget         *area_box;
  GtkWidget         *color_area;
  GtkWidget         *foo_area;
  GtkWidget         *image_area;

  gint               area_rows;
  gint               area_columns;

  GimpPanedBox      *drag_handler;

  gboolean           in_destruction;
};


static void        gimp_toolbox_constructed             (GObject        *object);
static void        gimp_toolbox_dispose                 (GObject        *object);
static void        gimp_toolbox_set_property            (GObject        *object,
                                                         guint           property_id,
                                                         const GValue   *value,
                                                         GParamSpec     *pspec);
static void        gimp_toolbox_get_property            (GObject        *object,
                                                         guint           property_id,
                                                         GValue         *value,
                                                         GParamSpec     *pspec);

static gboolean    gimp_toolbox_button_press_event      (GtkWidget      *widget,
                                                         GdkEventButton *event);
static void        gimp_toolbox_drag_leave              (GtkWidget      *widget,
                                                         GdkDragContext *context,
                                                         guint           time,
                                                         GimpToolbox    *toolbox);
static gboolean    gimp_toolbox_drag_motion             (GtkWidget      *widget,
                                                         GdkDragContext *context,
                                                         gint            x,
                                                         gint            y,
                                                         guint           time,
                                                         GimpToolbox    *toolbox);
static gboolean    gimp_toolbox_drag_drop               (GtkWidget      *widget,
                                                         GdkDragContext *context,
                                                         gint            x,
                                                         gint            y,
                                                         guint           time,
                                                         GimpToolbox    *toolbox);
static gchar     * gimp_toolbox_get_description         (GimpDock       *dock,
                                                         gboolean        complete);
static void        gimp_toolbox_set_host_geometry_hints (GimpDock       *dock,
                                                         GtkWindow      *window);
static void        gimp_toolbox_book_added              (GimpDock       *dock,
                                                         GimpDockbook   *dockbook);
static void        gimp_toolbox_book_removed            (GimpDock       *dock,
                                                         GimpDockbook   *dockbook);
static void        gimp_toolbox_wilber_style_updated    (GtkWidget      *widget,
                                                         GimpToolbox    *toolbox);
static gboolean    gimp_toolbox_draw_wilber             (GtkWidget             *widget,
                                                         cairo_t               *cr);
static GtkWidget * toolbox_create_color_area            (GimpToolbox    *toolbox,
                                                         GimpContext    *context);
static GtkWidget * toolbox_create_foo_area              (GimpToolbox    *toolbox,
                                                         GimpContext    *context);
static GtkWidget * toolbox_create_image_area            (GimpToolbox    *toolbox,
                                                         GimpContext    *context);
static void        toolbox_paste_received               (GtkClipboard   *clipboard,
                                                         const gchar    *text,
                                                         gpointer        data);


G_DEFINE_TYPE_WITH_PRIVATE (GimpToolbox, gimp_toolbox, GIMP_TYPE_DOCK)

#define parent_class gimp_toolbox_parent_class


static void
gimp_toolbox_class_init (GimpToolboxClass *klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  GimpDockClass  *dock_class   = GIMP_DOCK_CLASS (klass);

  object_class->constructed           = gimp_toolbox_constructed;
  object_class->dispose               = gimp_toolbox_dispose;
  object_class->set_property          = gimp_toolbox_set_property;
  object_class->get_property          = gimp_toolbox_get_property;

  widget_class->button_press_event    = gimp_toolbox_button_press_event;

  dock_class->get_description         = gimp_toolbox_get_description;
  dock_class->set_host_geometry_hints = gimp_toolbox_set_host_geometry_hints;
  dock_class->book_added              = gimp_toolbox_book_added;
  dock_class->book_removed            = gimp_toolbox_book_removed;

  g_object_class_install_property (object_class, PROP_CONTEXT,
                                   g_param_spec_object ("context",
                                                        NULL, NULL,
                                                        GIMP_TYPE_CONTEXT,
                                                        GIMP_PARAM_READWRITE |
                                                        G_PARAM_CONSTRUCT));
}

static void
gimp_toolbox_init (GimpToolbox *toolbox)
{
  toolbox->p = gimp_toolbox_get_instance_private (toolbox);

  gimp_help_connect (GTK_WIDGET (toolbox), gimp_standard_help_func,
                     GIMP_HELP_TOOLBOX, NULL, NULL);
}

static void
gimp_toolbox_constructed (GObject *object)
{
  GimpToolbox   *toolbox = GIMP_TOOLBOX (object);
  GimpGuiConfig *config;
  GtkWidget     *main_vbox;

  gimp_assert (GIMP_IS_CONTEXT (toolbox->p->context));

  config = GIMP_GUI_CONFIG (toolbox->p->context->gimp->config);

  main_vbox = gimp_dock_get_main_vbox (GIMP_DOCK (toolbox));

  toolbox->p->vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gtk_box_pack_start (GTK_BOX (main_vbox), toolbox->p->vbox, FALSE, FALSE, 0);
  gtk_box_reorder_child (GTK_BOX (main_vbox), toolbox->p->vbox, 0);
  gtk_widget_show (toolbox->p->vbox);

  /* Use g_signal_connect() also for the toolbox itself so we can pass
   * data and reuse the same function for the vbox
   */
  g_signal_connect (toolbox, "drag-leave",
                    G_CALLBACK (gimp_toolbox_drag_leave),
                    toolbox);
  g_signal_connect (toolbox, "drag-motion",
                    G_CALLBACK (gimp_toolbox_drag_motion),
                    toolbox);
  g_signal_connect (toolbox, "drag-drop",
                    G_CALLBACK (gimp_toolbox_drag_drop),
                    toolbox);
  g_signal_connect (toolbox->p->vbox, "drag-leave",
                    G_CALLBACK (gimp_toolbox_drag_leave),
                    toolbox);
  g_signal_connect (toolbox->p->vbox, "drag-motion",
                    G_CALLBACK (gimp_toolbox_drag_motion),
                    toolbox);
  g_signal_connect (toolbox->p->vbox, "drag-drop",
                    G_CALLBACK (gimp_toolbox_drag_drop),
                    toolbox);

  toolbox->p->header = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (toolbox->p->header), GTK_SHADOW_NONE);
  gtk_box_pack_start (GTK_BOX (toolbox->p->vbox), toolbox->p->header,
                      FALSE, FALSE, 0);

  g_object_bind_property (config,             "toolbox-wilber",
                          toolbox->p->header, "visible",
                          G_BINDING_SYNC_CREATE);

  g_signal_connect (toolbox->p->header, "style-updated",
                    G_CALLBACK (gimp_toolbox_wilber_style_updated),
                    toolbox);
  g_signal_connect (toolbox->p->header, "draw",
                    G_CALLBACK (gimp_toolbox_draw_wilber),
                    toolbox);

  gimp_help_set_help_data (toolbox->p->header,
                           _("Drop image files here to open them"), NULL);

  toolbox->p->tool_palette = gimp_tool_palette_new ();
  gimp_tool_palette_set_toolbox (GIMP_TOOL_PALETTE (toolbox->p->tool_palette),
                                 toolbox);
  gtk_box_pack_start (GTK_BOX (toolbox->p->vbox), toolbox->p->tool_palette,
                      FALSE, FALSE, 0);
  gtk_widget_show (toolbox->p->tool_palette);

  toolbox->p->area_box = gtk_flow_box_new ();
  gtk_flow_box_set_selection_mode (GTK_FLOW_BOX (toolbox->p->area_box),
                                   GTK_SELECTION_NONE);
  gtk_box_pack_start (GTK_BOX (toolbox->p->vbox), toolbox->p->area_box,
                      FALSE, FALSE, 0);
  gtk_widget_show (toolbox->p->area_box);

  gtk_widget_add_events (GTK_WIDGET (toolbox), GDK_POINTER_MOTION_MASK);
  gimp_devices_add_widget (toolbox->p->context->gimp, GTK_WIDGET (toolbox));

  toolbox->p->color_area = toolbox_create_color_area (toolbox,
                                                      toolbox->p->context);
  gtk_flow_box_insert (GTK_FLOW_BOX (toolbox->p->area_box),
                       toolbox->p->color_area, -1);

  g_object_bind_property (config,                 "toolbox-color-area",
                          toolbox->p->color_area, "visible",
                          G_BINDING_SYNC_CREATE);

  toolbox->p->foo_area = toolbox_create_foo_area (toolbox, toolbox->p->context);
  gtk_flow_box_insert (GTK_FLOW_BOX (toolbox->p->area_box),
                       toolbox->p->foo_area, -1);

  g_object_bind_property (config,               "toolbox-foo-area",
                          toolbox->p->foo_area, "visible",
                          G_BINDING_SYNC_CREATE);

  toolbox->p->image_area = toolbox_create_image_area (toolbox,
                                                      toolbox->p->context);
  gtk_flow_box_insert (GTK_FLOW_BOX (toolbox->p->area_box),
                       toolbox->p->image_area, -1);

  g_object_bind_property (config,                 "toolbox-image-area",
                          toolbox->p->image_area, "visible",
                          G_BINDING_SYNC_CREATE);

  gimp_toolbox_dnd_init (GIMP_TOOLBOX (toolbox), toolbox->p->vbox);
}

static void
gimp_toolbox_dispose (GObject *object)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (object);

  toolbox->p->in_destruction = TRUE;

  g_clear_object (&toolbox->p->context);

  G_OBJECT_CLASS (parent_class)->dispose (object);

  toolbox->p->in_destruction = FALSE;
}

static void
gimp_toolbox_set_property (GObject      *object,
                           guint         property_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (object);

  switch (property_id)
    {
    case PROP_CONTEXT:
      toolbox->p->context = g_value_dup_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_toolbox_get_property (GObject    *object,
                           guint       property_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (object);

  switch (property_id)
    {
    case PROP_CONTEXT:
      g_value_set_object (value, toolbox->p->context);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static gboolean
gimp_toolbox_button_press_event (GtkWidget      *widget,
                                 GdkEventButton *event)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (widget);

  if (event->type == GDK_BUTTON_PRESS && event->button == 2)
    {
      GtkClipboard *clipboard;

      clipboard = gtk_widget_get_clipboard (widget, GDK_SELECTION_PRIMARY);
      gtk_clipboard_request_text (clipboard,
                                  toolbox_paste_received,
                                  g_object_ref (toolbox));

      return TRUE;
    }

  return FALSE;
}

static void
gimp_toolbox_drag_leave (GtkWidget      *widget,
                         GdkDragContext *context,
                         guint           time,
                         GimpToolbox    *toolbox)
{
  gimp_highlight_widget (widget, FALSE);
}

static gboolean
gimp_toolbox_drag_motion (GtkWidget      *widget,
                          GdkDragContext *context,
                          gint            x,
                          gint            y,
                          guint           time,
                          GimpToolbox    *toolbox)
{
  gboolean handle;

  if (gimp_paned_box_will_handle_drag (toolbox->p->drag_handler,
                                       widget,
                                       context,
                                       x, y,
                                       time))
    {
      gdk_drag_status (context, 0, time);
      gimp_highlight_widget (widget, FALSE);

      return FALSE;
    }

  handle = (gtk_drag_dest_find_target (widget, context, NULL) != GDK_NONE);

  gdk_drag_status (context, handle ? GDK_ACTION_MOVE : 0, time);
  gimp_highlight_widget (widget, handle);

  /* Return TRUE so drag_leave() is called */
  return TRUE;
}

static gboolean
gimp_toolbox_drag_drop (GtkWidget      *widget,
                        GdkDragContext *context,
                        gint            x,
                        gint            y,
                        guint           time,
                        GimpToolbox    *toolbox)
{
  GdkAtom  target;
  gboolean dropped = FALSE;

  if (gimp_paned_box_will_handle_drag (toolbox->p->drag_handler,
                                       widget,
                                       context,
                                       x, y,
                                       time))
    {
      return FALSE;
    }

  target = gtk_drag_dest_find_target (widget, context, NULL);

  if (target != GDK_NONE)
    {
      /* The URI handlers etc will handle this */
      gtk_drag_get_data (widget, context, target, time);
      dropped = TRUE;
    }

  gtk_drag_finish (context, dropped,
                   gdk_drag_context_get_selected_action (context) ==
                   GDK_ACTION_MOVE,
                   time);

  return TRUE;
}

static gchar *
gimp_toolbox_get_description (GimpDock *dock,
                              gboolean  complete)
{
  GString *desc      = g_string_new (_("Toolbox"));
  gchar   *dock_desc = GIMP_DOCK_CLASS (parent_class)->get_description (dock,
                                                                        complete);

  if (dock_desc && strlen (dock_desc) > 0)
    {
      g_string_append (desc, GIMP_DOCK_BOOK_SEPARATOR);
      g_string_append (desc, dock_desc);
    }

  g_free (dock_desc);

  return g_string_free (desc, FALSE /*free_segment*/);
}

static void
gimp_toolbox_book_added (GimpDock     *dock,
                         GimpDockbook *dockbook)
{
  if (GIMP_DOCK_CLASS (parent_class)->book_added)
    GIMP_DOCK_CLASS (parent_class)->book_added (dock, dockbook);

  if (g_list_length (gimp_dock_get_dockbooks (dock)) == 1)
    {
      gimp_dock_invalidate_geometry (dock);
    }
}

static void
gimp_toolbox_book_removed (GimpDock     *dock,
                           GimpDockbook *dockbook)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (dock);

  if (GIMP_DOCK_CLASS (parent_class)->book_removed)
    GIMP_DOCK_CLASS (parent_class)->book_removed (dock, dockbook);

  if (! gimp_dock_get_dockbooks (dock) &&
      ! toolbox->p->in_destruction)
    {
      gimp_dock_invalidate_geometry (dock);
    }
}

static void
gimp_toolbox_set_host_geometry_hints (GimpDock  *dock,
                                      GtkWindow *window)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (dock);
  gint         button_width;
  gint         button_height;

  if (gimp_tool_palette_get_button_size (GIMP_TOOL_PALETTE (toolbox->p->tool_palette),
                                         &button_width, &button_height))
    {
      GdkGeometry geometry;

      geometry.min_width   = 2 * button_width;
      geometry.min_height  = -1;
      geometry.base_width  = button_width;
      geometry.base_height = 0;
      geometry.width_inc   = button_width;
      geometry.height_inc  = 1;

      gtk_window_set_geometry_hints (window,
                                     NULL,
                                     &geometry,
                                     GDK_HINT_MIN_SIZE   |
                                     GDK_HINT_BASE_SIZE  |
                                     GDK_HINT_RESIZE_INC |
                                     GDK_HINT_USER_POS);

      gimp_dialog_factory_set_has_min_size (window, TRUE);
    }
}

GtkWidget *
gimp_toolbox_new (GimpDialogFactory *factory,
                  GimpContext       *context,
                  GimpUIManager     *ui_manager)
{
  g_return_val_if_fail (GIMP_IS_DIALOG_FACTORY (factory), NULL);
  g_return_val_if_fail (GIMP_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (GIMP_IS_UI_MANAGER (ui_manager), NULL);

  return g_object_new (GIMP_TYPE_TOOLBOX,
                       "context", context,
                       NULL);
}

GimpContext *
gimp_toolbox_get_context (GimpToolbox *toolbox)
{
  g_return_val_if_fail (GIMP_IS_TOOLBOX (toolbox), NULL);

  return toolbox->p->context;
}

void
gimp_toolbox_set_drag_handler (GimpToolbox  *toolbox,
                               GimpPanedBox *drag_handler)
{
  g_return_if_fail (GIMP_IS_TOOLBOX (toolbox));

  toolbox->p->drag_handler = drag_handler;
}


/*  private functions  */

static void
gimp_toolbox_wilber_style_updated (GtkWidget   *widget,
                                   GimpToolbox *toolbox)
{
  gint button_width;
  gint button_height;

  if (gimp_tool_palette_get_button_size (GIMP_TOOL_PALETTE (toolbox->p->tool_palette),
                                         &button_width, &button_height))
    {
      gtk_widget_set_size_request (widget,
                                   button_width  * PANGO_SCALE_SMALL,
                                   button_height * PANGO_SCALE_SMALL);
    }
}

static gboolean
gimp_toolbox_draw_wilber (GtkWidget *widget,
                          cairo_t   *cr)
{
  gimp_cairo_draw_toolbox_wilber (widget, cr);

  return FALSE;
}

static GtkWidget *
toolbox_create_color_area (GimpToolbox *toolbox,
                           GimpContext *context)
{
  GtkWidget *col_area;

  col_area = gimp_toolbox_color_area_create (toolbox, 40, 38);
  g_object_set (col_area,
                "halign",        GTK_ALIGN_CENTER,
                "valign",        GTK_ALIGN_CENTER,
                "margin-left",   2,
                "margin-right",  2,
                "margin-top",    2,
                "margin-bottom", 2,
                NULL);

  return col_area;
}

static GtkWidget *
toolbox_create_foo_area (GimpToolbox *toolbox,
                         GimpContext *context)
{
  GtkWidget *foo_area;

  foo_area = gimp_toolbox_indicator_area_create (toolbox);
  g_object_set (foo_area,
                "halign",        GTK_ALIGN_CENTER,
                "valign",        GTK_ALIGN_CENTER,
                "margin-left",   2,
                "margin-right",  2,
                "margin-top",    2,
                "margin-bottom", 2,
                NULL);

  return foo_area;
}

static GtkWidget *
toolbox_create_image_area (GimpToolbox *toolbox,
                           GimpContext *context)
{
  GtkWidget *image_area;

  image_area = gimp_toolbox_image_area_create (toolbox, 52, 42);
  g_object_set (image_area,
                "halign",        GTK_ALIGN_CENTER,
                "valign",        GTK_ALIGN_CENTER,
                "margin-left",   2,
                "margin-right",  2,
                "margin-top",    2,
                "margin-bottom", 2,
                NULL);

  return image_area;
}

static void
toolbox_paste_received (GtkClipboard *clipboard,
                        const gchar  *text,
                        gpointer      data)
{
  GimpToolbox *toolbox = GIMP_TOOLBOX (data);
  GimpContext *context = toolbox->p->context;

  if (text)
    {
      const gchar *newline = strchr (text, '\n');
      gchar       *copy;
      GFile       *file = NULL;

      if (newline)
        copy = g_strndup (text, newline - text);
      else
        copy = g_strdup (text);

      g_strstrip (copy);

      if (strlen (copy))
        file = g_file_new_for_commandline_arg (copy);

      g_free (copy);

      if (file)
        {
          GtkWidget         *widget = GTK_WIDGET (toolbox);
          GimpImage         *image;
          GimpPDBStatusType  status;
          GError            *error = NULL;

          image = file_open_with_display (context->gimp, context, NULL,
                                          file, FALSE,
                                          G_OBJECT (gimp_widget_get_monitor (widget)),
                                          &status, &error);

          if (! image && status != GIMP_PDB_CANCEL)
            {
              gimp_message (context->gimp, NULL, GIMP_MESSAGE_ERROR,
                            _("Opening '%s' failed:\n\n%s"),
                            gimp_file_get_utf8_name (file), error->message);
              g_clear_error (&error);
            }

          g_object_unref (file);
        }
    }

  g_object_unref (context);
}
