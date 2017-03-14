/*
 * gemu-gtk-util.c
 * This file contains auxiliary-functions for the development of gtk+-apps
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gemu-gtk-util.h"
#include "gemu-glib-util.h"

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
  GDestroyNotify data_destroy)
{
  GList *children =
    gtk_container_get_children (container);
  GList *children_start = children;
  GList *return_list = NULL;

  return_list =
    gemu_glib_util_connect_to_all_signals (
      G_OBJECT (container), emission_hook, data, data_destroy);

  while (children)
  {
    if (GTK_IS_CONTAINER (children->data))
    {
  GList *local_list = NULL;

  local_list =
    gemu_gtk_util_signal_connect_to_widget_children (
      GTK_CONTAINER (children->data), emission_hook, data, data_destroy);

  return_list = g_list_concat (return_list, local_list);

    }

    children = children->next;
  }
  g_list_free (children);

  return return_list;
}


