#include "monty.h"

/**
 * add - adds the top two elements of the stack
 *
 * @stack: pointer to the head of the stack
 * @line_number: line number of the opcode
 *
 * Return: void
 */

void add(stack_t **stack, unsigned int line_number)
{
	if (*stack && (*stack)->next)
	{
		int sum = (*stack)->n + (*stack)->next->n;

		pop(stack, line_number);
		(*stack)->n = sum;
	} else
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}

/**
 * nop - doesn't do anything
 *
 * @stack: pointer to the head of the stack
 * @line_number: line number of the opcode
 *
 * Return: void
 */

void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
