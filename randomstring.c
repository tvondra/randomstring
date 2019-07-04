#include "postgres.h"

#include "utils/datum.h"
#include "utils/array.h"
#include "utils/lsyscache.h"

#include "utils/memutils.h"
#include "utils/numeric.h"
#include "utils/builtins.h"
#include "utils/palloc.h"
#include "utils/elog.h"
#include "catalog/pg_type.h"
#include "nodes/execnodes.h"
#include "access/tupmacs.h"
#include "utils/pg_crc.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(random_string);
PG_FUNCTION_INFO_V1(random_bytea);

Datum
random_string(PG_FUNCTION_ARGS)
{
	int				i;
	int32			len = PG_GETARG_INT32(0);
	char		   *str;
	char		   *chars = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+={}[];:'\"\\|/?.>,<~`";
 
	/* some basic sanity checks */
	if (len <= 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("length must be a non-negative integer")));

	str = palloc(len + 1);

	for (i = 0; i < len; i++)
		str[i] = chars[random() % 62];

	str[len] = '\0';

	PG_RETURN_TEXT_P(cstring_to_text(str));
}

Datum
random_bytea(PG_FUNCTION_ARGS)
{
	int				i;
	int32			len = PG_GETARG_INT32(0);
	bytea		   *val;
	unsigned char  *ptr;
 
	/* some basic sanity checks */
	if (len <= 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("length must be a non-negative integer")));

	val = palloc(VARHDRSZ + len);
	SET_VARSIZE(val, VARHDRSZ + len);
	ptr = (unsigned char *) VARDATA(val);

	for (i = 0; i < len; i++)
		ptr[i] = (unsigned char) (random() % 255);

	PG_RETURN_BYTEA_P(val);
}
