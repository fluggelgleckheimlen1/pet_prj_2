#if !defined FUNCTIONS_H
#define FUNCTIONS_H

// === include ===
// current folder
#include "common.h"

// === defines ===
#define	ASCII_frame_8	0xc2U
#define	ASCII_frame_5	0xc5U
#define	ASCII_frame_2	0xc1U
#define	ASCII_space		0x20U
#define	ASCII_dot		0x2eU

#define	DEF_frame_7		'\xda'
#define	DEF_frame_9		'\xbf'
#define	DEF_frame_4		'\xc3'
#define	DEF_frame_6		'\xb4'
#define	DEF_frame_1		'\xc0'
#define	DEF_frame_3		'\xd9'
#define	DEF_frame_v		'\xb3'
#define	DEF_frame_h		'\xc4'

// === declaration ===
void		fct_draw_menu(const TYPE_SINT, const size_t);

void		fct_clean_stdin(void);

TYPE_BYTE	fct_get_pressed_key(void);

void		fct_format_str_with_padd(TYPE_BYTE * const, const size_t, const TYPE_BYTE * const, const TYPE_BYTE);

void		fct_con_cursor_hide(void);
void		fct_con_cursor_show(void);
void		fct_con_clear_screen(void);
void		fct_con_set_size(const TYPE_UINT, const TYPE_UINT);

#endif
