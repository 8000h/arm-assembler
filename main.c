#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint64_t offset;

typedef enum
{
	DEFINED   = 0x00,
	UNDEFINED = 0x01,
	MTDF      = 0x02  /* multiply-defined symbol */
} symbol_type;

typedef struct
{
	char        name[16];
	offset      addr;
	symbol_type type;	
} symbol;

#define MAX_SYMBOLS 128
typedef struct
{
	int    symbol_count;
	symbol symbols[MAX_SYMBOLS];
} symbol_vector;

typedef enum
{
	TOK_STR    = 0x00,
	TOK_COLON  = 0x01,
	TOK_NUMBER = 0x02,
	TOK_COMMA  = 0x03
} token_type;

static bool     get_next_line(FILE *stream, char *buff, int buff_sz);

/* parser functions */
static void     parse_line(char *line);
static void     accept(token_type t);

static void     

static bool     grammar_line(void);
static bool     grammar_label(void);
static bool     grammar_instr(void);


/* static uint32_t assemble(instruction* inst); */
static void     add_symbol(symbol_vector *vec, symbol *sym);
static void     first_pass(FILE *stream);
/* static void  second_pass(instruction* insts); */


/* "Evil" globals */
symbol_vector symbol_vec;


int main(int argc, char *argv[])
{
	first_pass(stdin);

	return EXIT_SUCCESS;
}

static bool grammar_line(void)
{
	/* line -> label instr
	 *      -> label
	 *      -> instr
	 */

}

static bool grammar_label(void)
{
	/* label -> STR ':'
	 */

	char label_name[16];

	if (accept(TOK_STR) && expect)
}

static bool get_next_line(FILE *stream, char *buff, int buff_sz)
{
	if (feof(stream) != 0)
		return false;

	fgets(buff, buff_sz, stream);
	return true;
}

static void parse_line(char *line)
{
	
}

/* The first pass does all the heavy lifting.
 * It will populate the symbol table and
 * gather instrutions to be assembled in
 * the second pass */
static void first_pass(FILE *stream)
{	
	const int LINE_SZ = 128;

	char line[LINE_SZ];
	int  line_num = 1;
	while (get_next_line(stream, line, LINE_SZ))
	{
		
		line_num++;
	}
}

/*
static void second_pass(instruction* insts)
{}
*/

static void add_symbol(symbol_vector *vec, symbol *sym)
{
	if (vec->symbol_count == MAX_SYMBOLS)
		return; /* TODO: add proper error handling */

	vec->symbols[symbol_count++] = *sym;
}
