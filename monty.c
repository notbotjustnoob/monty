#define _GNU_SOURCE
#include "monty.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* Global variable */
stack_t *stack = NULL;

/* Function prototypes */
void execute_opcode(char *opcode, char *arg, unsigned int line_number);
void free_stack(void);

/**
 * main - entry point
 *
 * @argc:  argument count
 * @argv:  list of arguments
 * Return: int
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		char *opcode = strtok(line, " \t\n");
		char *arg = strtok(NULL, " \t\n");

		line_number++;
		if (opcode && opcode[0] != '#')
			execute_opcode(opcode, arg, line_number);
	}

	free_stack();
	free(line);
	fclose(file);
	exit(EXIT_SUCCESS);
}

/**
 * execute_opcode - executes the opcode
 *
 * @opcode: opcode
 * @arg: arguments
 * @line_number: line number of the opcode
 */

void execute_opcode(char *opcode, char *arg, unsigned int line_number)
{
	if (strcmp(opcode, "push") == 0)
	{
		if (arg)
			push(&stack, line_number, atoi(arg));
		else
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			free_stack();
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(opcode, "pall") == 0)
		pall(&stack, line_number);
	else if (strcmp(opcode, "pint") == 0)
		pint(&stack, line_number);
	else if (strcmp(opcode, "pop") == 0)
		pop(&stack, line_number);
	else if (strcmp(opcode, "swap") == 0)
		swap(&stack, line_number);
	else if (strcmp(opcode, "add") == 0)
		add(&stack, line_number);
	else if (strcmp(opcode, "nop") == 0)
		nop(&stack, line_number);
	else
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
		free_stack();
		exit(EXIT_FAILURE);
	}
}

/**
 * free_stack - frees the stack
 *
 * Return: void
 */

void free_stack(void)
{
	stack_t *current = stack;
	stack_t *temp;

	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}
