// #SMALL
/*********************************************************************
*         INTEL CORPORATION PROPRIETARY INFORMATION                  *
*   This software is supplied under the terms of a license agreement *
*   or nondisclosure agreement with Intel Corporation and may not be *
*   copied or disclosed except in accordance with the terms of that  *
*   agreement.                                                       *
*********************************************************************/

#include <stdbool.h>
#include <memory.h>
#include "lit.h"
#include "type.h"
#include "data.h"
#include "proc.h"
#include "oscompat.h"

/*   CONFIGURATION PROCEDURES AND VARIABLES. */



byte config = UNKNOWN;  /* system configuration */




byte wrapper;      /* TRUE IF WRAPPING TERMINAL */

byte first_coordinate = row_first;
/* X-Y ADDRESSING: row first, column first, or ANSI standard ? */

byte visible_attributes = _TRUE;
/* screen attributes take up one space on the screen */
byte character_attributes = _FALSE;
/* attributes apply to the following characters rather than a field */

#define ESCSTR  "\x1b"
#define LEAD	ESC, '['
#define LEADSTR ESCSTR "["
  /* leading sequence for VT100 and ANSI */

#ifdef MSDOS
byte first_32_chars[32] = { "?????????\t\n?? ??????????????????" };
#else
byte first_32_chars[32] = { "?????????\t\n?????????????????????" };
#endif



/*    CHARACTER CLASSIFICATION TABLES    */
/*    PRINT_AS     THE OUTPUT TRANSLATION TABLE - EXPECTS HIGH BIT MASKED OFF */
/*    THIS TABLE IS FOR SERIES IV WHICH CAN DISPLAY MOST FUNNY CHARACTERS */
/*    START WILL PATCH THE TABLE FOR SERIES III's WHICH GENERALLY CANNOT  */
/*    DISPLAY THE CONTROL CHARACTERS. */

byte print_as[256] = {
#ifdef MSDOS
        "?????????\t\n?? ??????????????????"
#else
        "?????????\t\n?????????????????????"

#endif
        " !\"#$%&'()*+,-./0123456789:;<=>?@"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
        "abcdefghijklmnopqrstuvwxyz{|}~?"   /* tilde is funny on 1510 */
        "????????????????????????????????"
        "????????????????????????????????"
        "????????????????????????????????"
        "????????????????????????????????" };


/*    NAMES OF THE INPUT CODES    */
word input_code_names[17] = {
    CHAR2('C','U'), CHAR2('C','D'), CHAR2('C','L'), CHAR2('C','R'), CHAR2('C','H'),
    CHAR2('X','F'), CHAR2('B','R'), CHAR2('X','Z'), CHAR2('X','X'), CHAR2('X','A'),
    CHAR2('X','U'), CHAR2('R','B'), CHAR2('X','E'), CHAR2('X','S'), CHAR2('X','N'),
    CHAR2('X','H'), CHAR2('I','G') };

word output_code_names[17] = {
    CHAR2('M','U'), CHAR2('M','D'), CHAR2('M','L'), CHAR2('M','R'), CHAR2('M','H'),
    CHAR2('M','B'), CHAR2('E','R'), CHAR2('E','S'), CHAR2('E','L'), CHAR2('E','K'),
    CHAR2('I','L'), CHAR2('A','C'), CHAR2('A','O'), CHAR2('D','L'), CHAR2('R','V'),
    CHAR2('N','V'), CHAR2('B','K') };

code_t input_codes[17];

code_t output_codes[17];

byte VT100_input_codes[] = {
    3, LEAD, 0x41,   /* UP */
    3, LEAD, 0x42,   /* DOWN */
    3, LEAD, 0x44,   /* LEFT */
    3, LEAD, 0x43,   /* RIGHT */
    3, ESC, 0x4f, 0x50, /* HOME */      // PF1
    1, 0x6,        /* CONTROL F IS DELETE */
    3, ESC, 0x4f, 0x53, /* ESC */       // PF4
    1, 0x1a,        /* CONTROL Z IS DELETE LINE */
    1, 0x18,        /* CONTROL X IS DELETE LEFT */
    1, 0x1,        /* CONTROL A IS DELETE RIGHT */
    1, 0x15,        /* CONTROL U IS UNDO */
    1, 0x8,        /* RUBOUT */
    1, 0x5,        /* CONTROL-E IS DEFAULT */
    1, 0x16,        /* CONTROL-V IS STRING VARIABLE */
    1, 0xe,        /* CONTROL-N IS NUMERIC VARIABLE */
    1, 0x12,        /* CONTROL-R IS HEX IN CODE */
    0 };           /* IGNORE_CODE ; NOTHING IS IGNORED */

byte VT100_output_codes[] = {
    3, LEAD, 'A',         /* UP */
    3, LEAD, 'B',         /* DOWN */
    3, LEAD, 'D',         /* LEFT */
    3, LEAD, 'C',         /* RIGHT */
    3, LEAD, 'H',         /* HOME */
    1, CR,               /* BACK */
    3, LEAD, 'J',         /* ERASE REST OF SCREEN */
    4, LEAD, '2', 'J',     /* ERASE ENTIRE SCREEN */
    3, LEAD, 'K',         /* ERASE REST OF LINE */
    4, LEAD, '2', 'K',     /* ERASE ENTIRE LINE */
    0,                  /* REVERSE SCROLL */
    2, LEAD,             /* LEAD IN FOR ADDRESS CURSOR */
    1, 0,                /* OFFSET FOR ADDRESS CURSOR */
    0,                  /* DELETE LINE CODE */
    4, LEAD, '7', 'm',     /* REVERSE VIDEO CODE */
    4, LEAD, '0', 'm' ,     /* NORMAL VIDEO CODE */
    1, 0x20 };        /* DEFAULT BLANKOUT CODE */






byte default_input_codes[] = {
    0,            /* UP */
    0,            /* DOWN */
    0,            /* LEFT */
    0,            /* RIGHT */
    0,            /* HOME */
    1, 0x6,        /* CONTROL F IS DELETE */
    1, ESC,        /* ESC */
    1, 0x1a,        /* CONTROL Z IS DELETE LINE */
    1, 0x18,        /* CONTROL X IS DELETE LEFT */
    1, 0x1,        /* CONTROL A IS DELETE RIGHT */
    1, 0x15,        /* CONTROL U IS UNDO */
    1, 0x7f,        /* RUBOUT */
    1, 0x5,        /* CONTROL-E IS DEFAULT */
    1, 0x16,        /* CONTROL-V IS STRING VARIABLE */
    1, 0xe,        /* CONTROL-N IS NUMERIC VARIABLE */
    1, 0x12,        /* CONTROL-R IS HEX IN CODE */
    0 };           /* IGNORE_CODE ; NOTHING IS IGNORED */

byte default_output_codes[] = {
    0,             /* UP */
    0,             /* DOWN */
    0,             /* LEFT */
    0,             /* RIGHT */
    0,             /* HOME */
    1, CR,          /* BACK */
    0,             /* ERASE REST OF SCREEN */
    0,             /* ERASE ENTIRE SCREEN */
    0,             /* ERASE REST OF LINE */
    0,             /* ERASE ENTIRE LINE */
    0,             /* REVERSE SCROLL */
    0,             /* LEAD IN FOR ADDRESS CURSOR */
    1, 0x20,         /* OFFSET FOR ADDRESS CURSOR */
    0,             /* DELETE LINE CODE */
    0,             /* REVERSE VIDEO CODE */
    0,             /* NORMAL VIDEO CODE */
    1, 0x20 };        /* DEFAULT BLANKOUT CODE */




/*    THE Default delay times follow */

word delay_times[17] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


byte long_conf_buf[100];
pointer next_long_conf = long_conf_buf;



void Insert_long_config(pointer new_str_p, entry_t *entry_p) {

    pointer old_str_p;


    if (entry_p->len == 0xff) { /* already indirect */
        /* try to insert the new string at the same place */
        old_str_p = entry_p->p;
        if (old_str_p[0] >= new_str_p[0]) { /* check if there is enough room */
            Move_name(new_str_p, old_str_p);
            return;
        }
    }
    if (next_long_conf + new_str_p[0] + 1 < long_conf_buf + sizeof(long_conf_buf)) {
        entry_p->len = 0xff;
        entry_p->p = next_long_conf;  /* allocate space for the new string */
        Move_name(new_str_p, entry_p->p);
        next_long_conf = next_long_conf + new_str_p[0];
    }
    else {
        entry_p->len = 0;
        Macro_file_error("\x1d" "too many long config commands");
    }

} /* insert_long_config */





static void Update_config_table(pointer table_p, word table_len, word entry_size, pointer new_data_p) {
    byte i;

    memset(table_p, 0, (size_t)table_len * entry_size);
    for (i = 0; i <= table_len - 1; i++) {
        memcpy(table_p, new_data_p, (size_t)new_data_p[0] + 1);
        table_p += entry_size;
        new_data_p += (size_t)new_data_p[0] + 1;
    }

} /* update_config_table */




void Close_ioc() {

    Co_flush();
    config = UNKNOWN;

} /* close_ioc */






void Check_minimal_codes_set() {

    byte insuf_config[] = { "\x23" "insufficient configuration commands" };

    if (batch_mode) return;
    if (output_codes[up_out_code].code[0] == 0 ||
        output_codes[down_out_code].code[0] == 0 ||
        output_codes[left_out_code].code[0] == 0 ||
        output_codes[right_out_code].code[0] == 0 ||
        output_codes[back_out_code].code[0] == 0 ||
        (output_codes[home_out_code].code[0] == 0 &&
            output_codes[goto_out_code].code[0] == 0) ||
        prompt_line == 0) {
        Early_error(insuf_config);
    }

} /* check_minimal_codes_set */






void Reset_config() {

    config = UNKNOWN;

    /* Insert defaults into the config tables. */
    Update_config_table((pointer)input_codes, length(input_codes),
        sizeof(input_codes[0]), default_input_codes);
    Update_config_table((pointer)output_codes, length(output_codes),
        sizeof(output_codes[0]), default_output_codes);

    memcpy(print_as, first_32_chars, 32);

    /* AV=24; */
    if (!window_present) {
        window.prompt_line = prompt_line = 23;
        window.message_line = message_line = 22;
        window.last_text_line = last_text_line = 21;
    }

    wrapper = _TRUE;

    visible_attributes = _TRUE;
    /* AI=F;  screen attributes take up one space on the screen */
    character_attributes = _FALSE;
    /* AC=F;  attributes apply to a field */

    first_coordinate = row_first;

} /* reset_config */


boolean dos_system = { _FALSE };

void VT100_setup() {

    Close_ioc();

    config = VT100;

    /* Insert defaults into the config tables. */
    Update_config_table((pointer)input_codes, length(input_codes),
        sizeof(input_codes[0]), VT100_input_codes);
    Update_config_table((pointer)output_codes, length(output_codes),
        sizeof(output_codes[0]), VT100_output_codes);

    memcpy(print_as, first_32_chars, 32);

    /* AV=24; */
    if (!window_present) {
        window.prompt_line = prompt_line = 23;
        window.message_line = message_line = 22;
        window.last_text_line = last_text_line = 21;
    }

    wrapper = _FALSE;  /* AW=F;  The terminal doesn't wrap lines. */

    visible_attributes = _FALSE;
    /* AI=T;  screen attributes do not take space on the screen */
    character_attributes = _TRUE;
    /* AC=T;  attributes apply to a field */

    first_coordinate = ANSI_RC;

} /* VT100_setup */

void ANSI_setup() {

    VT100_setup();

    config = ANSI;

//    memcpy(input_codes[home_code - first_code].code, "\x1\xc\0\0\0", 5);
//    memcpy(input_codes[esc_code - first_code].code, "\x1\x4\0\0\0", 5);
   memcpy(output_codes[reverse_scroll_out_code].code, "\x3" LEADSTR "L\0", 5); /* REVERSE SCROLL */
   memcpy(output_codes[delete_out_code].code, "\x4" LEADSTR "1M\0", 5); /* DELETE LINE CODE */

} /* ANSI_setup */

void Setup_terminal() {

    dq_get_system_id(tmp_str, &excep);
    if (cmpb(&tmp_str[1], "WIN", 3) == 0xffff) {
        ANSI_setup();
        dos_system = _TRUE;
    }
    else if (cmpb(&tmp_str[1], "UNIX", 4) == 0xffff) {
        ANSI_setup();
#ifdef UNIX
        setup_stdin();
#endif
    }
    else
        Reset_config();


} /* setup_terminal */





byte exit_config_list[41] = { 0 };


void Restore_system_config() {

    if (!batch_mode) {
        Print_unconditionally_p(exit_config_list);
        Co_flush();
#ifdef UNIX
        restore_stdin();
#endif
    }
} /* restore_system_config */


