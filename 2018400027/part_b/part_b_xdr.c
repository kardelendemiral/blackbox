/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "part_b.h"

bool_t
xdr_arguments (XDR *xdrs, arguments *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->num1))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->num2))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->path, 256,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}