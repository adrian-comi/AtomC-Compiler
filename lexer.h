#pragma once

enum
{
	ID
	// keywords
	,
	TYPE_CHAR,
	TYPE_DOUBLE,
	TYPE_INT,
	ELSE,
	IF,
	RETURN,
	STRUCT,
	VOID,
	WHILE
	// delimiters
	,
	COMMA,
	END,
	SEMICOLON,
	LPAR,
	RPAR,
	LBRACKET,
	RBRACKET,
	LACC,
	RACC
	// operators
	,
	ASSIGN,
	EQUAL,
	DIVIDE,
	ADD,
	MUL,
	DOT,
	AND,
	OR,
	NOT,
	NOTEQ,
	LESS,
	LESSEQ,
	GREATER,
	GREATEREQ,
	SUB

	//constants
	,
	INT,
	DOUBLE,
	CHAR,
	STRING

};

typedef struct Token
{
	int code; // ID, TYPE_CHAR, ...
	int line; // the line from the input file
	union
	{
		char *text; // the chars for ID, STRING (dynamically allocated)
		int i;		// the value for INT
		char c;		// the value for CHAR
		double d;	// the value for DOUBLE
	};
	struct Token *next; // next token in a simple linked list
} Token;

Token *tokenize(const char *pch);
void showTokens(const Token *tokens);
