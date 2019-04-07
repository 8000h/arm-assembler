/* The grammar is quite simple:
 *
 * line  -> label
 *       -> label instr
 *       -> instr
 *
 * label -> STR ':'
 *
 * instr -> STR ops
 *
 * ops   -> STR ',' ops
 *       -> STR
 *       -> epsilon
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
	ARG_REG,
	ARG_LIT,
	ARG_SYM
} arg_type;

typedef struct
{
	arg_type type;
	char     val[16];
} argument;

typedef struct
{
	char label[16];
	char instr[16];

	bool label_defined;

	int      argc;    /* The amount of arguments the instruction is using */
	argument args[3];
} parsed_line;


typedef enum
{
	TOK_STR,
	TOK_COMMA,
	TOK_COLON,
	TOK_EOL,
	TOK_UNDEFINED
} token;


/* The interface to the parser */
static bool parse_line(char *line, parsed_line *info);

/* Parser functions */
static bool accept(token tok);
static bool expect(token tok);

/* Non-terminal functions */
static bool grammar_line(void);
static bool grammar_label(void);
static bool grammar_instr(void);
static bool grammar_ops(void);

/* Lexer functions */
static void skip_whitespace(void);
static void next_token(void);




/* "Evil" globals */
static parsed_line *current_line_info;
char               *current_line;
char                val[16]; /* the token value read from lexer */
token               sym;     /* last read symbol from lexer */
int                 pos;
int                 length;


int main(int argc, char *argv[])
{
	char line[128];

	while (feof(stdin) == 0)
	{
		parsed_line line_info;

		fgets(line, 128, stdin);
		if (parse_line(line, &line_info))
		{
			printf("Label defined:   %d\n", line_info.label_defined);
			printf("Instruction:     %s\n", line_info.instr);
			printf("Arguments found: %d\n", line_info.argc);
			printf("\n");
		}

	}

	return EXIT_SUCCESS;
}

static bool parse_line(char *line, parsed_line *info)
{
	info->label_defined = false;
	current_line        = line;
	pos                 = 0;
	length              = strlen(line);
	current_line_info   = info;
	current_line_info->argc = 0;

	printf("Parsing line: %s\n", current_line);

	next_token();

	if (grammar_line())
	{	
		// memcpy(&current_line_info, info, sizeof(parsed_line));
		return true;
	}

	/* TODO: add proper error handling */
	printf("Well, something fucked up... :(\n");
	return false;
}

static bool accept(token tok)
{
	if (sym == tok)
	{
		next_token();
		return true;
	}

	return false;
}

static bool expect(token tok)
{
	return accept(tok);
}

static bool grammar_line(void)
{
	bool status = false;

	if (grammar_label())
	{
		current_line_info->label_defined = true;
		status = true;
	}

	status |= grammar_instr();

	return status;
}

static bool grammar_label(void)
{
	if (!accept(TOK_STR))
		return false;	

	strncpy(current_line_info->label, val, 16);

	if (expect(TOK_COLON))
		return true;

	return false;
}

static bool grammar_instr(void)
{
	if (!accept(TOK_STR))
		return false;

	strncpy(current_line_info->instr, val, 16);

	if (!grammar_ops())
		return false;

	return true;
}

static bool grammar_ops(void)
{
	printf("grammar_ops()\n");

	if (accept(TOK_STR))
	{
		parsed_line *cur = current_line_info;
		argument *arg    = &cur->args[cur->argc];
		cur->argc++;

		strncpy(arg->val, val, 16);
		arg->type = ARG_REG;

		if (expect(TOK_COMMA))
			grammar_ops();

		return true;

	} 

	if (accept(TOK_EOL))
		return true;

	return false;

}

static void skip_whitespace(void)
{
	while (pos < length && isspace(current_line[pos]))
		pos++;
}

static void next_token(void)
{
	sym = TOK_UNDEFINED;

	skip_whitespace();

	if (pos == length)
	{
		sym = TOK_EOL;
		return;	
	}

	char c = current_line[pos];

	/* If the character is a terminal character */
	switch (c)
	{
		case ':':
			sym = TOK_COLON;
			pos++;
			break;

		case ',':
			sym = TOK_COMMA;
			pos++;
			break;

		case '\n':
			sym = TOK_EOL;
			pos++;
			break;
	}

	/* If sym is stull undefined then
	 * the token is either STR or
	 * UNDEFINED (still) */
	if (sym == TOK_UNDEFINED && (isalpha(c) || isdigit(c)))
	{
		sym = TOK_STR;

		int idx = 0;
		for (; pos < length && (isalpha(c) || isdigit(c)); idx++, c = current_line[pos])
		{
			/* Prevent from writing outside the buffer */
			if (idx == 16)
				break;

			val[idx] = c;
			pos++;
		}

		/* Add null terminator */
		val[idx] = '\0';
	}

	printf("next_token(): sym: %d\n", sym);
	printf("next_token(): val: %s\n\n", val);

}
