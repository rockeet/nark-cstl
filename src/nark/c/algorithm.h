#ifndef __nark_c_algorithm_h__
#define __nark_c_algorithm_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
# pragma warning(disable: 4127)
#endif

#include "config.h"
#include <stdarg.h>
#include <stddef.h>

#include "field_type.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

typedef void (*void_handler)();

typedef void (*array_handler)(char* _First, ptrdiff_t count, ptrdiff_t field_offset);

typedef void (*array_handler_v)(char* _First, ptrdiff_t count, ptrdiff_t field_offset, va_list val);

typedef ptrdiff_t  (*array_handler_r1k)(const char* _First, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, va_list key);
typedef ptrdiff_t  (*array_handler_r2k)(const char* _First, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, ptrdiff_t* res, va_list key);

//! when _First[_IdxUpdated] was updated, call this function to keep heap form
typedef void (*array_update_heap)(char* _First, ptrdiff_t _IdxUpdated, ptrdiff_t _Bottom, ptrdiff_t field_offset);

typedef struct nark_arraycb
{
	array_handler sort;

	array_handler sort_heap;
	array_handler make_heap;
	array_handler push_heap;
	array_handler  pop_heap;
	array_update_heap update_heap;

	array_handler_r1k binary_search;
	array_handler_r1k lower_bound;
	array_handler_r1k upper_bound;
	array_handler_r2k equal_range;

	const char*  type_str;
	ptrdiff_t    elem_size;
	ptrdiff_t    field_offset;
	int          is_byptr;
	field_type_t field_type;
	field_type_t field_type_idx;
} nark_arraycb;

void FEBIRD_DLL_EXPORT nark_arraycb_init(nark_arraycb* self, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type, int is_byptr);

#define nark_offsetp(ptr, field_name) ((char*)&((ptr)->field_name) - (char*)(ptr))

#define nark_arraycb_init_m(self, first, field_type) \
		nark_arraycb_init(self, sizeof(*(first)), nark_offsetp(first, field_name), field_type, false)

#define nark_arraycb_init_t(self, elem_type, field_type) \
		nark_arraycb_init(self, sizeof(elem_type), (ptrdiff_t)&((elem_type*)0)->field_name, field_type, false)

#define nark_arraycb_handle(acb, fun, first, count) (acb).fun(first, count, (acb).field_offset)

#define nark_acb_sort(     acb, first, count) nark_arraycb_handle(acb, sort     , first, count)
#define nark_acb_sort_heap(acb, first, count) nark_arraycb_handle(acb, sort_heap, first, count)
#define nark_acb_make_heap(acb, first, count) nark_arraycb_handle(acb, make_heap, first, count)
#define nark_acb_push_heap(acb, first, count) nark_arraycb_handle(acb, push_heap, first, count)
#define nark_acb_pop_heap( acb, first, count) nark_arraycb_handle(acb,  pop_heap, first, count)

//! @{
//! va_arg ... is Key
ptrdiff_t FEBIRD_DLL_EXPORT nark_acb_binary_search(const nark_arraycb* acb, const void* first, ptrdiff_t count, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_acb_lower_bound(const nark_arraycb* acb, const void* first, ptrdiff_t count, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_acb_upper_bound(const nark_arraycb* acb, const void* first, ptrdiff_t count, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_acb_equal_range(const nark_arraycb* acb, const void* first, ptrdiff_t count, ptrdiff_t* upp, ...);
//@}

//////////////////////////////////////////////////////////////////////////


void FEBIRD_DLL_EXPORT nark_sort(void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type);

void FEBIRD_DLL_EXPORT nark_pop_heap(void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type);
void FEBIRD_DLL_EXPORT nark_push_heap(void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type);
void FEBIRD_DLL_EXPORT nark_make_heap(void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type);
void FEBIRD_DLL_EXPORT nark_sort_heap(void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type);

ptrdiff_t FEBIRD_DLL_EXPORT nark_lower_bound(const void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_upper_bound(const void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_equal_range(const void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type, ptrdiff_t* upper, ...);

void FEBIRD_DLL_EXPORT nark_sort_p(void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type);

void FEBIRD_DLL_EXPORT nark_pop_heap_p(void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type);
void FEBIRD_DLL_EXPORT nark_push_heap_p(void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type);
void FEBIRD_DLL_EXPORT nark_make_heap_p(void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type);
void FEBIRD_DLL_EXPORT nark_sort_heap_p(void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type);

ptrdiff_t FEBIRD_DLL_EXPORT nark_lower_bound_p(const void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_upper_bound_p(const void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type, ...);
ptrdiff_t FEBIRD_DLL_EXPORT nark_equal_range_p(const void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type, ptrdiff_t* upper, ...);


//---------------------------------------------------------------------------------------
#define nark_sort_field_c(first, count, field_name, field_type) \
	nark_sort(first, count, sizeof(*(first)),	nark_offsetp(first, field_name), field_type)

#define nark_sort_value_c(first, count, field_type) \
	nark_sort(first, count, sizeof(*(first)), 0, field_type)

//---------------------------------------------------------------------------------------
#define nark_sort_field_pc(first, count, field_name, field_type) \
	nark_sort_p(first, count, nark_offsetp(*first, field_name), field_type)

#define nark_sort_value_pc(first, count, field_type) nark_sort_p(first, count, 0, field_type)

//---------------------------------------------------------------------------------------
#define nark_push_heap_field_c(first, count, field_name, field_type) \
	nark_push_heap(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type)

#define nark_push_heap_value_c(first, count, field_type) \
	nark_push_heap(first, count, sizeof(*(first)), 0, field_type)

//---------------------------------------------------------------------------------------
#define nark_pop_heap_field_c(first, count, field_name, field_type) \
	nark_pop_heap(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type)

#define nark_pop_heap_value_c(first, count, field_type) \
	nark_pop_heap(first, count, sizeof(*(first)), 0, field_type)

//---------------------------------------------------------------------------------------
#define nark_make_heap_field_c(first, count, field_name, field_type) \
	nark_make_heap(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type)

#define nark_make_heap_value_c(first, count, field_type) \
	nark_make_heap(first, count, sizeof(*(first)), 0, field_type)

//---------------------------------------------------------------------------------------
#define nark_sort_heap_field_c(first, count, field_name, field_type) \
	nark_sort_heap(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type)

#define nark_sort_heap_value_c(first, count, field_type) \
	nark_sort_heap(first, count, sizeof(*(first)), 0, field_type)

//---------------------------------------------------------------------------------------
#define nark_lower_bound_field_c(first, count, field_name, field_type, key) \
	nark_lower_bound(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type, key)

#define nark_lower_bound_value_c(first, count, field_type, key) \
	nark_lower_bound(first, count, sizeof(*(first)), 0, field_type, key)

//---------------------------------------------------------------------------------------
#define nark_upper_bound_field_c(first, count, field_name, field_type, key) \
	nark_upper_bound(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type, key)

#define nark_upper_bound_value_c(first, count, field_type, key) \
	nark_upper_bound(first, count, sizeof(*(first)), 0, field_type, key)

//---------------------------------------------------------------------------------------
#define nark_equal_range_field_c(first, count, field_name, field_type, upper, key) \
	nark_equal_range(first, count, sizeof(*(first)), nark_offsetp(first, field_name), field_type, upper, key)

#define nark_equal_range_value_c(first, count, field_type, upper, key) \
	nark_equal_range(first, count, sizeof(*(first)), 0, field_type, upper, key)

#ifdef __cplusplus
} // extern "C"

//---------------------------------------------------------------------------------------------
#define nark_sort_field(first, count, field_name) \
	nark_sort_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name))

#define nark_sort_value(first, count) \
	nark_sort(first, count, sizeof(*(first)), 0, nark_get_field_type(first))

#define nark_sort_field_p(first, count, field_name) \
	nark_sort_field_pc(first, count, field_name, nark_get_field_type(&(*(first))->field_name))

#define nark_sort_value_p(first, count) \
	nark_sort_p(first, count, 0, nark_get_field_type(*(first)))

//---------------------------------------------------------------------------------------------
#define nark_push_heap_field(first, count, field_name) \
	nark_push_heap_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name))

#define nark_push_heap_value(first, count) \
	nark_push_heap(first, count, sizeof(*(first)), 0, nark_get_field_type(first))

//---------------------------------------------------------------------------------------------
#define nark_pop_heap_field(first, count, field_name) \
	nark_pop_heap_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name))

#define nark_pop_heap_value(first, count) \
	nark_pop_heap(first, count, sizeof(*(first)), 0, nark_get_field_type(first))

//---------------------------------------------------------------------------------------------
#define nark_make_heap_field(first, count, field_name) \
	nark_make_heap_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name))

#define nark_make_heap_value(first, count) \
	nark_make_heap(first, count, sizeof(*(first)), 0, nark_get_field_type(first))

//---------------------------------------------------------------------------------------------
#define nark_sort_heap_field(first, count, field_name) \
	nark_sort_heap_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name))

#define nark_sort_heap_value(first, count) \
	nark_sort_heap(first, count, sizeof(*(first)), 0, nark_get_field_type(first))

//---------------------------------------------------------------------------------------------
#define nark_lower_bound_field(first, count, field_name, key) \
	nark_lower_bound_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name), key)

#define nark_lower_bound_value(first, count, key) \
	nark_lower_bound(first, count, sizeof(*(first)), 0, nark_get_field_type(first), &key)

//---------------------------------------------------------------------------------------------
#define nark_upper_bound_field(first, count, field_name, key) \
	nark_upper_bound_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name), key)

#define nark_upper_bound_value(first, count, key) \
	nark_upper_bound(first, count, sizeof(*(first)), 0, nark_get_field_type(first), &key)

//---------------------------------------------------------------------------------------------
#define nark_equal_range_field(first, count, field_name, upper, key) \
	nark_equal_range_field_c(first, count, field_name, nark_get_field_type(&(first)->field_name), upper, key)

#define nark_equal_range_value(first, count, upper, key) \
	nark_equal_range(first, count, sizeof(*(first)), 0, nark_get_field_type(first), upper, key)



#endif // __cplusplus

#endif // __nark_c_algorithm_h__


