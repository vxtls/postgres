/*-------------------------------------------------------------------------
 *
 * Simple list facilities for frontend code
 *
 * Data structures for simple lists of OIDs, strings, and pointers.  The
 * support for these is very primitive compared to the backend's List
 * facilities, but it's all we need in, eg, pg_dump.
 *
 *
 * Portions Copyright (c) 1996-2025, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/fe_utils/simple_list.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

typedef struct SimpleOidListCell
{
	struct SimpleOidListCell *next;
	Oid			val;
} SimpleOidListCell;

typedef struct SimpleOidList
{
	SimpleOidListCell *head;
	SimpleOidListCell *tail;
} SimpleOidList;

typedef struct SimpleStringListCell
{
	struct SimpleStringListCell *next;
	bool		touched;		/* true, when this string was searched and
								 * touched */
	char		val[FLEXIBLE_ARRAY_MEMBER]; /* null-terminated string here */
} SimpleStringListCell;

typedef struct SimpleStringList
{
	SimpleStringListCell *head;
	SimpleStringListCell *tail;
} SimpleStringList;

typedef struct SimplePtrListCell
{
	struct SimplePtrListCell *next;
	void	   *ptr;
} SimplePtrListCell;

typedef struct SimplePtrList
{
	SimplePtrListCell *head;
	SimplePtrListCell *tail;
} SimplePtrList;

typedef struct SimpleOidStringListCell
{
	struct SimpleOidStringListCell *next;
	Oid			oid;
	char		str[FLEXIBLE_ARRAY_MEMBER]; /* null-terminated string here */
}			SimpleOidStringListCell;

typedef struct SimpleOidStringList
{
	SimpleOidStringListCell *head;
	SimpleOidStringListCell *tail;
} SimpleOidStringList;

extern void simple_oid_list_append(SimpleOidList *list, Oid val);
extern bool simple_oid_list_member(SimpleOidList *list, Oid val);
extern void simple_oid_list_destroy(SimpleOidList *list);

extern void simple_string_list_append(SimpleStringList *list, const char *val);
extern bool simple_string_list_member(SimpleStringList *list, const char *val);
extern void simple_string_list_destroy(SimpleStringList *list);

extern const char *simple_string_list_not_touched(SimpleStringList *list);

extern void simple_ptr_list_append(SimplePtrList *list, void *ptr);
extern void simple_ptr_list_destroy(SimplePtrList *list);

extern void simple_oid_string_list_append(SimpleOidStringList *list, Oid oid, const char *str);
extern void simple_oid_string_list_destroy(SimpleOidStringList *list);

#endif							/* SIMPLE_LIST_H */
