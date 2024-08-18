#ifndef _VA_ARGS_HXX_
#define _VA_ARGS_HXX_

typedef char * va_list;
#define va_start( ap, v ) ap = (char *)&v + sizeof( v )
#define va_arg( ap, t ) ( (t *) ( ap += sizeof( t ) )[-1]
#define va_end( ap ) ap = NULL

#endif
