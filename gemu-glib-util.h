/*
 * gemu-glib-util.h
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

#ifndef GEMU_GLIB_UTIL_H_INCLUDED
#define GEMU_GLIB_UTIL_H_INCLUDED

#include <stdlib.h>
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/*
 *
 * Example:
 *  You have an App-Instance with the name my_app. If you want to see all the
 *  signals emitted on this app just add
 *
 *  gemu_glib_util_connect_to_all_signals (
 *   G_OBJECT (my_app),
 *   gemu_glib_util_show_details,
 *   NULL,
 *   NULL);
 *
 *  right before g_application_run.
 */


/* Public Functions. */

/**
 * gemu_glib_util_connect_to_all_signals:
 * @object: a #GObject
 * @emission_hook: a #GSignalEmissionHook
 * @data: user-data
 * @data_destroy: a #GDestroyNotify for @data
 *
 * Connects the @callback on all signals emited on the @object.
 *
 * Returns: (transfer full) (element-type gulong):
 *     a newly allocated #GList of hook ids
 */
GList *gemu_glib_util_connect_to_all_signals (
  GObject *object,
  GSignalEmissionHook emission_hook,
  gpointer data,
  GDestroyNotify data_destroy);


/**
 * gemu_glib_util_show_details:
 * @ihint: Signal invocation hint, see #GSignalInvocationHint .
 * @n_param_values: the number of parameters to the function, including the 
 *    instance on which the signal was emitted.
 * @param_values: the instance on which the signal was emitted, followed by the 
 *    parameters of the emission.
 * @data: user data associated with the hook.
 *
 * This is just an example emission-hook to show the functionality.
 *
 */
gboolean
gemu_glib_util_show_details (
   GSignalInvocationHint *ihint,
   guint n_param_values,
   const GValue *param_values,
   gpointer data);

G_END_DECLS

#endif // GEMU_GLIB_UTIL_H_INCLUDED

