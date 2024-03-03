#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"
#include "utils.h"

Token *tokens; // single linked list of tokens
Token *lastTk; // the last token in list

int line = 1; // the current line in the input file

// adds a token to the end of the tokens list and returns it
// sets its code and line
Token *addTk(int code)
{
	Token *tk = safeAlloc(sizeof(Token));
	tk->code = code;
	tk->line = line;
	tk->next = NULL;
	if (lastTk)
	{
		lastTk->next = tk;
	}
	else
	{
		tokens = tk;
	}
	lastTk = tk;
	return tk;
}

char *extract(const char *begin, const char *end)
{
	if (begin == NULL || end == NULL || begin >= end)
	{
		err("invalid pointers");
		return NULL;
	}

	size_t length = end - begin;

	char *extracted_text = (char *)safeAlloc((size_t)length + 1);

	size_t i = 0;
	for (i = 0; i < length; i++)
	{
		extracted_text[i] = begin[i];
	}

	extracted_text[length] = '\0';

	return extracted_text;
}

Token *tokenize(const char *pch)
{
	const char *start;
	Token *tk;
	for (;;)
	{
		switch (*pch)
		{
		case ' ':
		case '\t':
			pch++;
			break;
		case '\r': // handles different kinds of newlines (Windows: \r\n, Linux: \n, MacOS, OS X: \r or \n)
			if (pch[1] == '\n')
				pch++;
			// fallthrough to \n
		case '\n':
			line++;
			pch++;
			break;
		case '\0':
			addTk(END);
			return tokens;
		case ',':
			addTk(COMMA);
			pch++;
			break;
		case ';':
			addTk(SEMICOLON);
			pch++;
			break;
		case '(':
			addTk(LPAR);
			pch++;
			break;
		case ')':
			addTk(RPAR);
			pch++;
			break;
		case '{':
			addTk(LACC);
			pch++;
			break;
		case '}':
			addTk(RACC);
			pch++;
			break;
		case '[':
			addTk(LBRACKET);
			pch++;
			break;
		case ']':
			addTk(RBRACKET);
			pch++;
			break;
		case '+':
			addTk(ADD);
			pch++;
			break;
		case '-':
			addTk(SUB);
			pch++;
			break;
		case '*':
			addTk(MUL);
			pch++;
			break;
		case '/':
			if (pch[1] == '/')
			{
				pch++;
				for (start = pch++; *pch != '\n'; pch++)
				{
				}
				break;
			}
			else
			{
				addTk(DIVIDE);
				pch++;
				break;
			}
		case '.':
			if (isdigit(pch[1] == 0))
			{
				addTk(DOT);
				pch++;
			}
			break;

		case '=':
			if (pch[1] == '=')
			{
				addTk(EQUAL);
				pch += 2;
			}
			else
			{
				addTk(ASSIGN);
				pch++;
			}
			break;
		case '!':
			if (pch[1] == '=')
			{
				addTk(NOTEQ);
				pch += 2;
			}
			else
			{
				addTk(NOT);
				pch++;
			}
			break;
		case '<':
			if (pch[1] == '=')
			{
				addTk(LESSEQ);
				pch += 2;
			}
			else
			{
				addTk(LESS);
				pch++;
			}
		break;

		case '>':
			if (pch[1] == '=')
			{
				addTk(GREATEREQ);
				pch += 2;
			}
			else
			{
				addTk(GREATER);
				pch++;
			}
		break;

		case '&':
			if (pch[1] == '&')
			{
				addTk(AND);
				pch+=2;
			}

			else
			{
				err("invalid symbol: %c (%d)",*pch,*pch);
			}
			break;
		case '|':
			if (pch[1] == '|')
			{
				addTk(OR);
				pch+=2;
			}

			else
			{
				err("invalid symbol: %c (%d)",*pch,*pch);
			}
			break;

			 case '\'':
                if(pch[1] != '\'' && pch[2] == '\'')
                {
                    tk=addTk(CHAR);
                    tk->c = pch[1];
                    pch += 3;
                }
                else
                {
                    err("invalid symbol: %c (%d)",*pch,*pch);
                }
                break;
		default:
			if (isalpha(*pch) || *pch == '_')
			{
				for (start = pch++; isalnum(*pch) || *pch == '_'; pch++)
				{
				}
				char *text = extract(start, pch);
				if (strcmp(text, "char") == 0)
					addTk(TYPE_CHAR);

				else if (strcmp(text, "double") == 0)
					addTk(TYPE_DOUBLE);

				else if (strcmp(text, "int") == 0)
					addTk(TYPE_INT);

				else if (strcmp(text, "double") == 0)
					addTk(TYPE_DOUBLE);

				else if (strcmp(text, "else") == 0)
					addTk(ELSE);

				else if (strcmp(text, "if") == 0)
					addTk(IF);

				else if (strcmp(text, "return") == 0)
					addTk(RETURN);

				else if (strcmp(text, "struct") == 0)
					addTk(STRUCT);

				else if (strcmp(text, "void") == 0)
					addTk(VOID);

				else if (strcmp(text, "while") == 0)
					addTk(WHILE);

				else
				{
					tk = addTk(ID);
					tk->text = text;
				}
			}
			else
				err("invalid char: %c (%d)", *pch, *pch);
		}
	}
}

void showTokens(const Token *tokens)
{
	for (const Token *tk = tokens; tk; tk = tk->next)
	{
		printf("%d\n", tk->code);
	}
}
