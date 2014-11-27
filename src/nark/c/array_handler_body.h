// input MACRO params:
//   FEBIRD_FUNC_NAME

static const array_handler CAT_TOKEN2(_S_tab_, FEBIRD_FUNC_NAME)[] =
{
#define MAKE_FUNC_NAME(tev) CAT_TOKEN5(FEBIRD_FUNC_NAME,_,VALUE_SIZE,_,tev)
#include "elem_size_loop.h"
#undef MAKE_FUNC_NAME
	NULL
};

void CAT_TOKEN2(nark_, FEBIRD_FUNC_NAME) // fun name
	(void* first, ptrdiff_t count, ptrdiff_t elem_size, ptrdiff_t field_offset, field_type_t field_type)
{
	array_handler pf;
	check_args(elem_size, field_offset, field_type);
	pf = (array_handler)get_heandler(CAT_TOKEN2(_S_tab_, FEBIRD_FUNC_NAME), elem_size, field_type);
#ifdef FEBIRD_ALGORITHM_DEBUG
	g_first = (char*)first;
	g_last = (char*)first + elem_size * count;
#endif
	(*pf)((char*)first, count, field_offset);
}

static const array_handler CAT_TOKEN2(Ptr_S_tab_, FEBIRD_FUNC_NAME)[] =
{
#define MAKE_FUNC_NAME(tev) CAT_TOKEN4(FEBIRD_FUNC_NAME,_,tev,_byptr)
#include "fun_field_type_tab.h"
#undef MAKE_FUNC_NAME
	NULL
};

void CAT_TOKEN3(nark_, FEBIRD_FUNC_NAME, _p) // fun name
	(void* first, ptrdiff_t count, ptrdiff_t field_offset, field_type_t field_type)
{
	field_type_t ft2 = internal_field_type(field_type);
	array_handler pf = CAT_TOKEN2(Ptr_S_tab_, FEBIRD_FUNC_NAME)[ft2];
#ifdef FEBIRD_ALGORITHM_DEBUG
	g_first = (char*)first;
	g_last = (char*)first + sizeof(void*) * count;
#endif
	(*pf)((char*)first, count, field_offset);
}

#undef FEBIRD_FUNC_NAME


