/*
 * gemu-gtk-util.h
 * This file is contains auxiliary-functions for the development of gtk+-apps
 *
 * Copyright (C) 2017 - Emanuel Schmidt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GEMU_GTK_UTIL_H_INCLUDED
#define GEMU_GTK_UTIL_H_INCLUDED

#include <stdlib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

/*
 *
 * Example:
 *  You have an App-Window with the name my_window. If you want to see all the
 *  signals emitted on this window and all its children just add
 *
 *  gemu_gtk_util_signal_connect_to_widget_children (
 *   GTK_CONTAINER (my_window),
 *   gemu_glib_util_show_details,
 *   NULL,
 *   NULL);
 *
 *  right during the instance-initialization.
 */

/* Public Functions. */

/**
 * gemu_gtk_util_signal_connect_to_widget_children:
 * @container: a #GtkContainer
 * @emission_hook: a #GSignalEmissionHook
 * @data: user-data
 * @data_destroy: a #GDestroyNotify for @data
 *
 * Adds identifier and informations on all signals emited on the @widget and its
 * children.
 *
 * Returns: (transfer full) (element-type gulong):
 *     a newly allocated #GList of all added handler ids
 */
GList *gemu_gtk_util_signal_connect_to_widget_children (
  GtkContainer *container,
  GSignalEmissionHook emission_hook,
  gpointer data,
  GDestroyNotify data_destroy);

G_END_DECLS

#endif // GEMU_GTK_UTIL_H_INCLUDED

