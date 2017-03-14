/*
 * gemu-glib-util.c
 * This file is contains auxiliary-functions for the development of glib-apps
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

#include "gemu-glib-util.h"

GList *gemu_glib_util_connect_to_all_signals (
  GObject *object,
  GSignalEmissionHook emission_hook,
  gpointer data,
  GDestroyNotify data_destroy)
{
  guint *list_of_signal_ids;
  guint no_of_signal_ids;
  guint i;
  GList *return_list = NULL;
  GType parent_type = G_TYPE_FROM_INSTANCE (object);

  /* Iterating over all parent-types */
  do {
    GList *local_connector_ids = NULL;

    list_of_signal_ids =
      g_signal_list_ids (parent_type, &no_of_signal_ids);

    /* Iterating over type-specific signals */
    for (i = 0; i < no_of_signal_ids; i++)
    {
      gulong *conn_id = g_malloc(sizeof (gulong));

      /* Any checks for G_SIGNALO_NO_HOOKS-flag are itentionally excluded */
      *conn_id =
        g_signal_add_emission_hook (list_of_signal_ids[i],
          0,
          emission_hook,
          data,
          data_destroy);

      local_connector_ids = g_list_append (local_connector_ids, conn_id);
    }

    return_list = g_list_concat (return_list, local_connector_ids);
  }
  while (parent_type = g_type_parent(parent_type));

  return return_list;
}


gboolean
gemu_glib_util_show_details (
  GSignalInvocationHint *ihint,
  guint n_param_values,
  const GValue *param_values,
  gpointer data)
{
  GObject *object_on_emit = g_value_get_object (param_values);

  g_print ("%s::%s::%s (%p) emitted\n",
    g_type_name (G_TYPE_FROM_INSTANCE(object_on_emit)),
    g_signal_name (ihint->signal_id),
    g_intern_static_string(ihint->detail),
    object_on_emit);
}


