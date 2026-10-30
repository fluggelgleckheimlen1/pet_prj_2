// === include ===
// system path directory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <wincrypt.h>

// nested folder
#include "include/common.h"
#include "include/functions.h"

// === defines ===
#if !defined CALG_SHA_256
#define CALG_SHA_256 0x0000800c
#endif
#if !defined CALG_SHA_384
#define CALG_SHA_384 0x0000800d
#endif
#if !defined CALG_SHA_512
#define CALG_SHA_512 0x0000800e
#endif

#define	DEF_CONSOLE_TITLE	"Hash calc"


/* declaration */
/* */	const TYPE_BYTE	*hash_alg_names[] = {
/* */										"",
/* */										"MD5",
/* */										"SHA1",
/* */										"SHA256",
/* */										"SHA384",
/* */										"SHA512"
/* */	};
/* END declaration */


int main(void) {
/***************/
/* declaration */
/* */
/* */	size_t				idx = 0;
/* */	const TYPE_BYTE		*alg_name;
/* */	TYPE_BYTE			pressed_key = 0;
/* */	TYPE_SINT			marked_menu_item = 0;
/* */	TYPE_BYTE			user_choice = 1;
/* */
/* */	const size_t		menu_item_qntt = sizeof(hash_alg_names) / sizeof (hash_alg_names[0]);
/* */
/* */	TYPE_BYTE			arr_input[1024] = {0};
/* */	size_t				input_lenght = 0;
/* */
/* */	TYPE_BYTE			arr_result[64] = {0};	//	MD5=16 / SHA1=20 / SHA256=32 / SHA512=64
/* */	size_t				arr_result_size = sizeof(arr_result);
/* */	size_t				result_lenght = arr_result_size;
/* */
/* */	HCRYPTPROV			handle_crypt_provider = 0;
/* */	HCRYPTHASH			handle_crypt_hash = 0;
/* */	DWORD				crypt_provider_type = 0;
/* */	TYPE_UDINT			hash_alg_ID = 0;
/* */
/* END declaration */
/*******************/

// === code ===
fct_con_set_size(DEF_CON_COLS, DEF_CON_LINES);
SetConsoleTitleA(DEF_CONSOLE_TITLE);
fct_con_cursor_hide();

while (TRUE) {
	fct_draw_menu(marked_menu_item, menu_item_qntt);

	pressed_key = fct_get_pressed_key();
	if (pressed_key != 0) {
		if (pressed_key == DEF_KEY_ARROW_UP) {
			marked_menu_item = marked_menu_item - 1;
			if (marked_menu_item < 1) {
				marked_menu_item = (menu_item_qntt - 1);
			}
		} else if (pressed_key == DEF_KEY_ARROW_DOWN) {
			marked_menu_item = marked_menu_item + 1;
			if (marked_menu_item > (menu_item_qntt - 1)) {
				marked_menu_item = 1;
			}
		} else if (pressed_key == DEF_KEY_ENTER) {
			if (marked_menu_item > 0) {
				user_choice = marked_menu_item;
				break;
			}
		} else if (pressed_key == DEF_KEY_ESC) {
			return 0;
		}
	}
}

switch (user_choice) {
	case 1:
		alg_name = hash_alg_names[1];
		printf("%s hash selected\n", alg_name);
		hash_alg_ID = CALG_MD5;
		crypt_provider_type = PROV_RSA_FULL;
		break;

	case 2:
		alg_name = hash_alg_names[2];
		printf("%s hash selected\n", alg_name);
		hash_alg_ID = CALG_SHA1;
		crypt_provider_type = PROV_RSA_FULL;
		break;

	case 3:
		alg_name = hash_alg_names[3];
		printf("%s hash selected\n", alg_name);
		hash_alg_ID = CALG_SHA_256;
		crypt_provider_type = PROV_RSA_AES;
		break;

	case 4:
		alg_name = hash_alg_names[4];
		printf("%s hash selected\n", alg_name);
		hash_alg_ID = CALG_SHA_384;
		crypt_provider_type = PROV_RSA_AES;
		break;

	case 5:
		alg_name = hash_alg_names[5];
		printf("%s hash selected\n", alg_name);
		hash_alg_ID = CALG_SHA_512;
		crypt_provider_type = PROV_RSA_AES;
		break;

	default:
		printf("ERROR: unknown selection\n");
		return 2;
}

printf("Enter text for %s calculation:\n", alg_name);
fct_con_cursor_show();
//	считываем строку ввода
if (fgets(arr_input, sizeof(arr_input), stdin) != NULL) {
	//	убираем символ перевода строки (\n), если он попал во ввод
	arr_input[strcspn(arr_input, "\n")] = 0;
	//	получаем итоговую длину введённой строки
	input_lenght = strlen(arr_input);

	printf("You entered:\n%s\n", arr_input);
	printf("Text length: %u byte(s)\n", input_lenght);

	//	получаем дескриптор криптографического провайдера
	if (!CryptAcquireContext(&handle_crypt_provider, NULL, NULL, crypt_provider_type, CRYPT_VERIFYCONTEXT)) {
		printf("Error CryptAcquireContext\n");
		return 11;
	}

	//	создаем хэш-объект
	if (!CryptCreateHash(handle_crypt_provider, hash_alg_ID, 0, 0, &handle_crypt_hash)) {
		printf("Error CryptCreateHash\n");
		CryptReleaseContext(handle_crypt_provider, 0);
		return 12;
	}

	//	передаем текст для хэширования
	if (!CryptHashData(handle_crypt_hash, arr_input, input_lenght, 0)) {
		printf("Error CryptHashData\n");
		CryptDestroyHash(handle_crypt_hash);
		CryptReleaseContext(handle_crypt_provider, 0);
		return 13;
	}

	//	получаем результаты хэша в байтах
	if (CryptGetHashParam(handle_crypt_hash, HP_HASHVAL, arr_result, (DWORD *)&result_lenght, 0)) {
		printf("Result:\n");
		for (idx = 0; (idx < result_lenght) && (idx < arr_result_size); idx =  idx + 1) {
			printf("%02x", arr_result[idx]);
		}

		printf("\n\n");
	} else {
		printf("Error CryptGetHashParam\n");
	}

	//	освобождаем ресурсы
	CryptDestroyHash(handle_crypt_hash);
	CryptReleaseContext(handle_crypt_provider, 0);
}

fct_clean_stdin();
printf("Press ESC to exit...\n");
while (TRUE) {
	pressed_key = fct_get_pressed_key();
	if (pressed_key != 0) {
		if (pressed_key == DEF_KEY_ESC) {
			return 0;
		}
	}
}

}	// main()

