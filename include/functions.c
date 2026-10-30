// === include ===
// system path directory
#include <stdio.h>
#include <conio.h>

#include <windows.h>

// current folder
#include "functions.h"
#include "common.h"

// === defines ===
#define	DEF_COLOR_MARKED	0x70U
#define	DEF_COLOR_REGULAR	0x07U


void	fct_draw_menu(const TYPE_SINT marked_menu_item, const size_t menu_item_qntt) {
	// === declaration ===
	size_t		idx = 0;
	TYPE_BYTE	tmp_arr[DEF_CON_COLS] = {0};
	HANDLE		handle_con;

	// === code ===
	fct_con_clear_screen();

	//	форматируем вывод под ширину окна: верхний левый угол + набитая горизонтальными символами строка
	//	с оконечным нулем-терминатором, на место которого кладем верхний правый угол
	fct_format_str_with_padd(tmp_arr, sizeof(tmp_arr) - 1, "", DEF_frame_h);
	printf("%c%s%c", DEF_frame_7, tmp_arr, DEF_frame_9);
	printf("%c %-126s %c", DEF_frame_v, "Select hash algorithm:", DEF_frame_v);
	fct_format_str_with_padd(tmp_arr, sizeof(tmp_arr) - 1, "", DEF_frame_h);
	printf("%c%s%c", DEF_frame_4, tmp_arr, DEF_frame_6);

	handle_con = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle_con == INVALID_HANDLE_VALUE) {
		return;
	}

	for (idx = 1; idx < menu_item_qntt; idx = idx + 1) {
		printf("%c ", DEF_frame_v);

		if (marked_menu_item == idx) {
			SetConsoleTextAttribute(handle_con, DEF_COLOR_MARKED);
		}
		printf("%-126s", hash_alg_names[idx]);
		SetConsoleTextAttribute(handle_con, DEF_COLOR_REGULAR);

		printf(" %c", DEF_frame_v);
	}

	fct_format_str_with_padd(tmp_arr, sizeof(tmp_arr) - 1, "", DEF_frame_h);
	printf("%c%s%c\n", DEF_frame_1, tmp_arr, DEF_frame_3);

	return;
}


void	fct_format_str_with_padd(TYPE_BYTE * const str_OUT, const size_t str_OUT_len, const TYPE_BYTE * const str_IN, const TYPE_BYTE padding_symbol) {
	//	получаем выходную строку, длину выходной строки, входную строку для помещения в выходную и символ,
	//	которым требуется заполнить выходную строку до указанной длины; в конец выходной строки записываем ноль-терминатор
	// === declaration ===
	size_t	idx = 0;

	// === code ===
	while (str_IN[idx] != '\0' && idx < str_OUT_len - 1) {
		str_OUT[idx] = str_IN[idx];
		idx = idx + 1;
	}

	while (idx < str_OUT_len - 1) {
		str_OUT[idx] = padding_symbol;
		idx = idx + 1;
	}

	str_OUT[str_OUT_len - 1] = '\0';

	return;
}


void	fct_clean_stdin(void) {
	//	вычитываем всё из буфера, пока не встретим перенос строки или конец потока
	// === declaration ===
	TYPE_INT	get_char;

	// === code ===
	if (_kbhit()) {
		do {
			get_char = getchar();
		} while (get_char != '\n' && get_char != EOF);
	}

	return;
}


TYPE_BYTE	fct_get_pressed_key(void) {
	// === declaration ===
	TYPE_INT	pressed_key;

	// === code ===
	pressed_key = _getch();
	if (pressed_key == DEF_KEYS_SPECIAL) {
		pressed_key = _getch();
		if ((pressed_key == DEF_KEY_ARROW_UP) || (pressed_key == DEF_KEY_ARROW_DOWN)) {
			return pressed_key;
		} else {
			return 0;
		}
	} else if ((pressed_key == DEF_KEY_ENTER) || (pressed_key == DEF_KEY_ESC)) {
		return pressed_key;
	} else {
		return 0;
	}
}


void	fct_con_cursor_hide(void) {
	// === declaration ===
	HANDLE				handle_con;
	CONSOLE_CURSOR_INFO	con_cursor_info;

	// === code ===
	handle_con = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle_con == INVALID_HANDLE_VALUE) {
		return;
	}
	GetConsoleCursorInfo(handle_con, &con_cursor_info);
	con_cursor_info.bVisible = FALSE;
	SetConsoleCursorInfo(handle_con, &con_cursor_info);

	return;
}


void	fct_con_cursor_show(void) {
	// === declaration ===
	HANDLE				handle_con;
	CONSOLE_CURSOR_INFO	con_cursor_info;

	// === code ===
	handle_con = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle_con == INVALID_HANDLE_VALUE) {
		return;
	}
	GetConsoleCursorInfo(handle_con, &con_cursor_info);
	con_cursor_info.bVisible = TRUE;
	SetConsoleCursorInfo(handle_con, &con_cursor_info);

	return;
}


void	fct_con_clear_screen(void) {
	// === declaration ===
	HANDLE						handle_con;
	CONSOLE_SCREEN_BUFFER_INFO	con_scr_buffer_info;
	COORD						home_coordinates = {0, 0};
	DWORD						cell_qntt;
	DWORD						cell_written;

	// === code ===
	handle_con = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle_con == INVALID_HANDLE_VALUE) {
		return;
	}

	//	получаем информацию о текущем размере буфера консоли
	if (!GetConsoleScreenBufferInfo(handle_con, &con_scr_buffer_info)) {
		return;
	}
	cell_qntt = (DWORD)(con_scr_buffer_info.dwSize.X * con_scr_buffer_info.dwSize.Y);

	//	заполняем весь буфер экрана пробелами
	FillConsoleOutputCharacter(handle_con, (TCHAR)' ', cell_qntt, home_coordinates, &cell_written);

	//	возвращаем курсор в левый верхний угол (координаты 0, 0)
	SetConsoleCursorPosition(handle_con, home_coordinates);

	return;
}


void	fct_con_set_size(const TYPE_UINT con_cols, const TYPE_UINT con_lines) {
	// === declaration ===
	HANDLE		handle_con;
	COORD		con_buffer_size;
	SMALL_RECT	con_window_size;

	// === code ===
	handle_con = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle_con == INVALID_HANDLE_VALUE) {
		return;
	}

	//	перед заданием размера окна задаем размер буфера не менее размера окна
	con_buffer_size.X = (SHORT)con_cols;
	con_buffer_size.Y = (SHORT)con_lines;
	SetConsoleScreenBufferSize(handle_con, con_buffer_size);

	//	задаем размер видимого окна (координаты от 0,0 до cols-1, lines-1)
	con_window_size.Left  = 0;
	con_window_size.Top   = 0;
	con_window_size.Right = (SHORT)(con_cols - 1);
	con_window_size.Bottom = (SHORT)(con_lines - 1);
	SetConsoleWindowInfo(handle_con, TRUE, &con_window_size);

	return;
}

