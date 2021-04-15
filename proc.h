#pragma once
#include "type.h"
#include <memory.h>     // for movb etc. replacements

#define nestedProc  static
void toCstr(char *cstr, byte *pstr);
void co_write(byte *buf, word len);
void set_ci_mode(byte mode);
word ci_read(byte *buf);
#ifdef MSDOS
void ms_sleep(unsigned int milliseconds);
#endif

void Aedit();

/* note needs more work to define paramater types */
/*****     CCTRAP.PLM     *****/
void Cc_trap(int);

/*****     AEDPLM.PLM     *****/
void Position_in_text();
pointer Unfold(pointer line_p, pointer image_p);
pointer Next_line(pointer ptr);
pointer Prior_line(pointer ptr);

/*****     BLOCK.PLM     *****/
void B_cmnd();
void G_cmnd();


/*****     CALC.PLM     *****/
pointer Get_n_var(byte radix, boolean add_minus);
pointer Get_s_var();
void C_cmnd();

/*****     CMNDS.PLM     *****/
byte Dispatched(byte command, dispatch_t *table_p);

static void Reset_column();
void Set_dirty();
void Dont_scroll();
void Test_crlf();
void Insert_a_char(byte ch);
void Insert_crlf();
void Jump_start();
void Cr_cmnd();

void Tab_cmnd();
void Delete_cmnd();
void Delete_line_cmnd();
void Delete_left_cmnd();
void Delete_right_cmnd();
byte Move_cmnd(byte ch);
void Rubout_cmnd();
void Undo_cmnd();
byte Hex_value(byte _char);
static boolean Convert_string_to_hex();
// Convert_string_to_hex(pointer source_p, pointer target_p);
void H_cmnd();
void I_cmnd();
void J_cmnd();
void T_cmnd();
void X_cmnd();
void V_cmnd();


/*****     COMAND.PLM     *****/
void Print_input_line();
byte Cmd_ci();
byte Upper(byte ch);
byte Is_illegal(byte ch);
byte Not_cursor_movement(byte cmd);
void Add_str_special(pointer str_p);
byte Input_line(pointer prompt, pointer prev_string_p);
byte Input_filename(pointer prompt, pointer prev_string_p);
byte Input_yes_no(char *prompt, byte y_type);
byte Input_yes_no_from_console(char *prompt, byte y_type, boolean in_replace);
byte Input_command(pointer prompt);
byte Input_fr();
byte Hit_space();
byte Get_hexin(boolean *err_p);

/*****     CONF.PLM     *****/
void Insert_long_config(pointer new_str_p, entry_t *entry_p);
void VT100_setup();
void ANSI_setup();
void Reset_config();
void Setup_terminal();
void Check_minimal_codes_set();
static void Update_config_table(pointer table_p, word table_len, word entry_size, pointer new_data_p);
void Restore_system_config();
void Close_ioc();

/*****     CONSOL.PLM     *****/

void AeditBeep();
byte Printable(byte ch);
void Text_co(byte ch);
void Print_line(pointer line);
static void Print_message_and_stay(pointer line);
void Print_count_message();
void Print_message(pointer line);
void Error(pointer msg_p);
void Early_error(pointer msg);
void Illegal_command();
void Kill_message();
void Clear_message();
void Clear_count_message();
void Gone_prompt();
void Kill_prompt_and_message();
void Init_prompt_and_message();
void Print_prompt(pointer line);
void Print_prompt_and_repos(pointer line);
void Print_last_prompt_and_msg(boolean small_prompt);
void Rebuild_screen();

/*****    FIND.PLM    *****/
void Fr_cmnd();

/*****     IO.PLM     *****/
void Set_input_expected(byte ch);
void Print_unconditionally_p(pointer string);
void Print_unconditionally(char *string);
void Print_unconditionally_crlf();
void Handle_controlc();
void Co_flush();
void Print_string(pointer string);
void Print_update(byte cur_column, byte len, pointer string, boolean rev_vid);
void Check_for_keys();
byte Ci();
void Echeck();
void Echeck_no_file();
void Openi(byte fnum, byte nbuf);
byte Test_file_existence(byte fnum);
void Openo(byte fnum, byte mode, byte nbuf);
void Open_cico();
void Detach(byte fnum);
void Detach_input();
word Read(byte fnum);
static void Rewind(byte fnum);
static void Expand_window();
void Check_window(word plusplus);
word Macro_file_read();
byte Can_backup_file();
byte Backup_file();
byte Can_forward_file();
byte Forward_file();
void Write(byte nfile, pointer buf, word len);
void Write_block_file(byte do_delete);
void Write_util_file();
void Read_util_file();
void Read_block_file();
byte Have_controlc();
void Working();

/*****     MACROF.PLM     *****/
void Macro_file_error(pointer string);
byte Macro_byte();
static byte Macro_not_blank();
boolean Add_macro_char(byte ch);
static byte Find_macro();
byte Find_index(byte ch, pointer ch_list_p);
void Macro_file_process();
void Stop_macro();
static void Macro_add_level();
logical Single_char_macro(byte ch);
void Exec_init_macro();
void Handle_macro_exec_code();
byte In_macro_exec();
byte Supply_macro_char();
void E_cmnd();
void M_cmnd();

/*****     SCREEN.PLM     *****/
void Put_home();
void Put_left();
void Put_erase_screen();
void Put_erase_entire_screen();
void Put_erase_line();
void Put_erase_entire_line();
void Put_normal_video();
void Adjust_for_column_80();
void Put_reverse_video();
void Put_re_col(byte new_col);
void Put_goto(byte goto_col, byte goto_row);
void Put_normal_video_end();
void Put_start_row(byte new_row);
void Put_clear_all();
void Put_clear_all_text();
void Put_insert_line(word num);
void Put_delete_line(byte num);
void Put_scroll(byte num_lines);
void Put_reverse_scroll();
void Put_scroll_region(byte first_row, byte last_row);
void Reset_scroll_region();

/*****     SETCMD.PLM     *****/
void S_cmnd();
byte Set_from_macro();

/*****     START.PLM     *****/

/*! Size of blocks in work-files. */
void Add_eof();
void Subtract_eof();
void Build_banner();
void Print_banner();
static void Clear_text();
byte Debug_option(byte ch);
void Alter_init();
void Flip_pointers();
void O_cmnd();
void Q_cmnd();
void Quit_exit(byte status);

/*****     TAGS.PLM     *****/
static void Delete_blocks(byte wk1_or_wk2, word ndelete);
void Set_tag(byte tagn, pointer in_mem);
void Set_tagi_at_lowe();
void Jump_tag(byte tagn);
void Jump_tagi();
void Clean_tags();
void Delete_to_tag(byte tagn);

/*****    TMPMAN.PLM    *****/

void Tmpman_init();

  /* initializes pointers for the 286 */

void Reinit_temp(byte file_num);

/*!
   Frees all the blocks associated with that file, and resets
   associated variables. If the mode is not viewonly, the physical
   file is rewineded. */

void Set_temp_viewonly(byte file_num, byte mode, connection conn);
/*!
   Sets the mode of a workfile to view_only_wk1 (or wk2),
   and passes to it the connection of the input file to
   allow the special mechanism of view_only. */

void Read_temp(byte file_num, pointer buf_addr);
/*!
   Read the current block of virtual_files(file_num) and moves it to
   buf_addr. first reads are taken from memory, then it starts to
   read from the disk file if it was necessary to have spilled it to
   disk. The read blocks are not removed from the file.
   The current block's successor becomes the current block.
   No need to OPEN_IF_NECESSARY, because rewind does the job. */

logical Read_previous_block(byte file_num, pointer buf_addr, logical keep);
/*!
   Read the current block of virtual_files(file_num) and moves it to
   buf_addr. first reads are taken from memory, then it starts to
   read from the disk file if it was necessary to have spilled it to
   disk. If keep is false, the read blocks are removed from the file.
   The current block's predecessor becomes the current block. */

void Backup_temp(byte file_num);
/*!
   Remove the last block of the file. */

void Skip_to_end(byte file_num);
/*!
   Set the pointers such that we are at the end of the file.
   No need to OPEN_IF_NECESSARY, because read_previous_block does the job. */

void Rewind_temp(byte file_num);
/*!
   Set the pointers such that we are at the beginning of the file. */

void Restore_temp_state(byte file_num);
/*!
  The  procedure copy_wk1 causes vf.cur_block_ptr to be NIL.  In this
  situation  it is the caller's responsibility to recover the current
  setting, using this procedure. */

void Write_temp(byte file_num, pointer buf_addr);
/*!
   Write to the given file the data at buf_addr. Try to put in free
   memory first, otherwise, spill the oldest written data to disk,
   keeping the newer data in memory if possible. If there are no
   blocks in memory at all, spill the new block to disk. */


/*****     UTIL.PLM     *****/

#define Min(a,b) ((a) < (b) ? (a) : (b))
#define Max(a,b) ((a) > (b) ? (a) : (b))

word Size_of_text_in_memory();
void Move_name(pointer fromp, pointer top);
byte Cmp_name(pointer fromp, pointer top);
pointer Print_number(dword d_number, byte b_width, byte base);
void Init_str(pointer str_p, int max_len);
void Reuse_str(pointer str_p, int max_len);
void Add_str_char(byte ch);
void Add_str(char *s);      // C string variant of Add_str_str
void Add_str_str(pointer str_p);
void Add_str_num(dword num, byte base);
void Init_scan(pointer str_p);
boolean Skip_char(byte ch);
word Num_in(boolean *err_p);

/*****     VIEW.PLM     *****/

void Movmem(pointer from_word, pointer to_word, word len);
void Re_window();
void Rebuild(byte r_row, pointer newp, pointer oldp);
void Save_line(byte s_row);
static pointer Unsave_line(byte u_row);
void Forward_char(word num_chars, byte delete_flag);
void Forward_line(word num_lines);
void Backup_char(word num_chars, byte delete_flag);
pointer Backup_line(int num_lines,pointer start, byte do_move);
pointer Print_text_line(pointer line);
void Re_write(pointer start);
void Re_view();

/*****     wordS.PLM     *****/
void P_cmnd();
void W_cmnd();
void K_cmnd();

/*****   AEDDUM.PLM   *****/

void Cocom(byte ch);             /* AEDASM */
void Codat(byte ch);             /* AEDASM */
byte Cidat();                    /* AEDASM */
void Send_block(pointer string);        /* AEDASM */
void Enable_ioc_io();            /* AEDASM */
void Disable_ioc_io();           /* AEDASM */
void Port_co(byte ch);           /* AEDASM */
byte Port_ci();                  /* AEDASM */
byte Port_csts();                /* AEDASM */
pointer Unfold_to_screen(pointer line); /* IOCASM */

/*****   XNXSYS.PLM   *****/
char *Getenv(pointer symbol_p);


byte Cli_command();
void Co(byte byt);
void Construct_point(pointer buff_ptr, pointer point_ptr);
void Dealias_cmd(word index);
void Display_output(pointer buff_ptr);
void Excep_handler(word condition_code, word param_code, word reserved, word npx_status);
logical Find();
pointer Find_alias(pointer alias_str_ptr);
void Find_term_type(pointer buf_ptr);
void Get_access_rights(pointer path_p);
boolean Look_ahead(byte num);
void Put_access_rights(pointer path_p);
void Restore_input_line_state();
void Rq_c_delete_command_connection(word command_conn, wpointer except_ptr);
void Save_input_line_state();
void Swb();

void Term_config_process();
void To_upper(pointer src_ptr, pointer dest_ptr, word count);

/** UDI ***/
selector dq_allocate(word size, wpointer excep_p);
connection dq_attach(pointer path, wpointer excep_p);
void dq_change_access(pointer path_p, byte class, byte access, wpointer excep_p);
void dq_change_extension(pointer path_p, pointer extension_p, wpointer excep_p);
void dq_close(connection conn, wpointer excep_p);
connection dq_create(pointer path_p, wpointer excep_p);
void dq_decode_exception(word excep_code, pointer message_p, word maxLen);
void dq_decode_time(dt_t *dt_p, wpointer execpp);
void dq_delete(pointer path_p, wpointer excep_p);
void dq_detach(connection conn, wpointer excep_p);
void dq_file_info(word conn, byte mode, file_info_t *file_info_p,  wpointer excep_p);
void dq_free(selector mem_token, wpointer excep_p);
byte dq_get_argument(pointer argument_p, wpointer excep_p);
void dq_get_exception_handler(exception_handler_t *handler_p, wpointer excep_p);
word dq_get_size(selector mem_token, wpointer excep_p);
void dq_get_system_id(pointer id_p, wpointer excep_p);       // id_p -> byte buf[21]
void dq_get_time(old_dt_t *dt_p,  wpointer excep_p);         // obsolete
void dq_open(connection conn, byte mode, byte num_buf, wpointer excep_p);
void dq_overlay(pointer name_p, wpointer execp_p);
word dq_read(connection conn, pointer buf_p, word count, wpointer excep_p);
void dq_rename(pointer old_p, pointer new_p, wpointer excep_p);
void dq_reserve_io_memory(word number_files, word number_buffers, wpointer excep_p);
void dq_seek(connection conn, byte mode, dword offset, wpointer excep_p);
void dq_special(byte type, void *ptr_p, wpointer excepp);
word dq_switch_buffer(pointer buffer_p, wpointer excep_p);
void dq_trap_cc(void (* cc_procedure_p)(), wpointer excepp);
void dq_truncate(connection conn, wpointer excep_p);
void dq_write(connection conn,pointer buf_p, word count, wpointer excep_p);


#define length(var) (sizeof(var)/sizeof(*var))
#define last(var)   (sizeof(var)/sizeof(*var) - 1)

word low(word val);
word high(word val);

#define highw(n)    (((n) >> 16) & 0xffff)
#define loww(n)     ((n) & 0xffff)



void movrb(pointer s, pointer t, word cnt);
word cmpb(pointer s, pointer t, byte cnt);
word cmpw(pointer s, pointer t, word cnt);

word findb(byte *str, byte ch, word cnt);
word findrb(byte *str, byte ch, word cnt);
word findp(pointer src[], pointer p, word cnt);
word skipb(byte *str, byte ch, word cnt);
word skiprb(byte *str, byte ch, word cnt);

void move(byte cnt, pointer s, pointer t);
