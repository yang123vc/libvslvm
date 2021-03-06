/*
 * Python object definition of the logical volumes sequence and iterator
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_logical_volumes.h"
#include "pyvslvm_python.h"
#include "pyvslvm_volume_group.h"

PySequenceMethods pyvslvm_logical_volumes_sequence_methods = {
	/* sq_length */
	(lenfunc) pyvslvm_logical_volumes_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyvslvm_logical_volumes_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyvslvm_logical_volumes_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm._logical_volumes",
	/* tp_basicsize */
	sizeof( pyvslvm_logical_volumes_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_logical_volumes_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	&pyvslvm_logical_volumes_sequence_methods,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pyvslvm logical volumes sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyvslvm_logical_volumes_iter,
	/* tp_iternext */
	(iternextfunc) pyvslvm_logical_volumes_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyvslvm_logical_volumes_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new logical volumes object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volumes_new(
           pyvslvm_volume_group_t *volume_group_object,
           PyObject* (*get_logical_volume_by_index)(
                        pyvslvm_volume_group_t *volume_group_object,
                        int logical_volume_index ),
           int number_of_logical_volumes )
{
	pyvslvm_logical_volumes_t *pyvslvm_logical_volumes = NULL;
	static char *function                              = "pyvslvm_logical_volumes_new";

	if( volume_group_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume group object.",
		 function );

		return( NULL );
	}
	if( get_logical_volume_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get logical volume by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the logical volumes values are initialized
	 */
	pyvslvm_logical_volumes = PyObject_New(
	                           struct pyvslvm_logical_volumes,
	                           &pyvslvm_logical_volumes_type_object );

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize logical volumes.",
		 function );

		goto on_error;
	}
	if( pyvslvm_logical_volumes_init(
	     pyvslvm_logical_volumes ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize logical volumes.",
		 function );

		goto on_error;
	}
	pyvslvm_logical_volumes->volume_group_object         = volume_group_object;
	pyvslvm_logical_volumes->get_logical_volume_by_index = get_logical_volume_by_index;
	pyvslvm_logical_volumes->number_of_logical_volumes   = number_of_logical_volumes;

	Py_IncRef(
	 (PyObject *) pyvslvm_logical_volumes->volume_group_object );

	return( (PyObject *) pyvslvm_logical_volumes );

on_error:
	if( pyvslvm_logical_volumes != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_logical_volumes );
	}
	return( NULL );
}

/* Intializes a logical volumes object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_logical_volumes_init(
     pyvslvm_logical_volumes_t *pyvslvm_logical_volumes )
{
	static char *function = "pyvslvm_logical_volumes_init";

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes.",
		 function );

		return( -1 );
	}
	/* Make sure the logical volumes values are initialized
	 */
	pyvslvm_logical_volumes->volume_group_object         = NULL;
	pyvslvm_logical_volumes->get_logical_volume_by_index = NULL;
	pyvslvm_logical_volumes->logical_volume_index        = 0;
	pyvslvm_logical_volumes->number_of_logical_volumes   = 0;

	return( 0 );
}

/* Frees a logical volumes object
 */
void pyvslvm_logical_volumes_free(
      pyvslvm_logical_volumes_t *pyvslvm_logical_volumes )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_logical_volumes_free";

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_logical_volumes );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyvslvm_logical_volumes->volume_group_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_logical_volumes->volume_group_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_logical_volumes );
}

/* The logical volumes len() function
 */
Py_ssize_t pyvslvm_logical_volumes_len(
            pyvslvm_logical_volumes_t *pyvslvm_logical_volumes )
{
	static char *function = "pyvslvm_logical_volumes_len";

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyvslvm_logical_volumes->number_of_logical_volumes );
}

/* The logical volumes getitem() function
 */
PyObject *pyvslvm_logical_volumes_getitem(
           pyvslvm_logical_volumes_t *pyvslvm_logical_volumes,
           Py_ssize_t item_index )
{
	PyObject *logical_volume_object = NULL;
	static char *function           = "pyvslvm_logical_volumes_getitem";

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes.",
		 function );

		return( NULL );
	}
	if( pyvslvm_logical_volumes->get_logical_volume_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes - missing get logical volume by index function.",
		 function );

		return( NULL );
	}
	if( pyvslvm_logical_volumes->number_of_logical_volumes < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes - invalid number of logical volumes.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyvslvm_logical_volumes->number_of_logical_volumes ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	logical_volume_object = pyvslvm_logical_volumes->get_logical_volume_by_index(
	                         pyvslvm_logical_volumes->volume_group_object,
	                         (int) item_index );

	return( logical_volume_object );
}

/* The logical volumes iter() function
 */
PyObject *pyvslvm_logical_volumes_iter(
           pyvslvm_logical_volumes_t *pyvslvm_logical_volumes )
{
	static char *function = "pyvslvm_logical_volumes_iter";

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyvslvm_logical_volumes );

	return( (PyObject *) pyvslvm_logical_volumes );
}

/* The logical volumes iternext() function
 */
PyObject *pyvslvm_logical_volumes_iternext(
           pyvslvm_logical_volumes_t *pyvslvm_logical_volumes )
{
	PyObject *logical_volume_object = NULL;
	static char *function           = "pyvslvm_logical_volumes_iternext";

	if( pyvslvm_logical_volumes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes.",
		 function );

		return( NULL );
	}
	if( pyvslvm_logical_volumes->get_logical_volume_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes - missing get logical volume by index function.",
		 function );

		return( NULL );
	}
	if( pyvslvm_logical_volumes->logical_volume_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes - invalid logical volume index.",
		 function );

		return( NULL );
	}
	if( pyvslvm_logical_volumes->number_of_logical_volumes < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes - invalid number of logical volumes.",
		 function );

		return( NULL );
	}
	if( pyvslvm_logical_volumes->logical_volume_index >= pyvslvm_logical_volumes->number_of_logical_volumes )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	logical_volume_object = pyvslvm_logical_volumes->get_logical_volume_by_index(
	                         pyvslvm_logical_volumes->volume_group_object,
	                         pyvslvm_logical_volumes->logical_volume_index );

	if( logical_volume_object != NULL )
	{
		pyvslvm_logical_volumes->logical_volume_index++;
	}
	return( logical_volume_object );
}

