#include <stdio.h>
#include <string.h>
#include "minishell.h"

void test_string_blocks() {
	char *test_cases[22] = {
		"echo hello | cat",
		"echo 'hello | world' | cat",
		"echo \"hello | world\" | cat",
		"echo hello | cat | grep",
		"echo 'hello | world' | cat | grep",
		"echo \"hello | world\" | cat | grep",
		"echo hello | cat | grep | wc",
		"echo 'hello | world' | cat | grep | wc",
		"echo \"hello | world\" | cat | grep | wc",
		"echo hello | cat | grep | wc | sort",
		"echo 'hello | world' | cat | grep | wc | sort",
		"echo \"hello | world\" | cat | grep | wc | sort",
		"echo hello | cat | grep | wc | sort | uniq",
		"echo 'hello | world' | cat | grep | wc | sort | uniq",
		"echo \"hello | world\" | cat | grep | wc | sort | uniq",
		"echo hello | cat | grep | wc | sort | uniq | head",
		"echo 'hello | world' | cat | grep | wc | sort | uniq | head",
		"echo \"hello | world\" | cat | grep | wc | sort | uniq | head",
		"echo hello | cat | grep | wc | sort | uniq | head | tail",
		"echo 'hello | world' | cat | grep | wc | sort | uniq | head | tail",
		"echo \"hello | world\" | cat | grep | wc | sort | uniq | head | tail",
		NULL
	};

	char *expected_results[22][9] = {
		{"echo hello ", " cat", NULL},
		{"echo 'hello | world' ", " cat", NULL},
		{"echo \"hello | world\" ", " cat", NULL},
		{"echo hello ", " cat ", " grep", NULL},
		{"echo 'hello | world' ", " cat ", " grep", NULL},
		{"echo \"hello | world\" ", " cat ", " grep", NULL},
		{"echo hello ", " cat ", " grep ", " wc", NULL},
		{"echo 'hello | world' ", " cat ", " grep ", " wc", NULL},
		{"echo \"hello | world\" ", " cat ", " grep ", " wc", NULL},
		{"echo hello ", " cat ", " grep ", " wc ", " sort", NULL},
		{"echo 'hello | world' ", " cat ", " grep ", " wc ", " sort", NULL},
		{"echo \"hello | world\" ", " cat ", " grep ", " wc ", " sort", NULL},
		{"echo hello ", " cat ", " grep ", " wc ", " sort ", " uniq", NULL},
		{"echo 'hello | world' ", " cat ", " grep ", " wc ", " sort ", " uniq", NULL},
		{"echo \"hello | world\" ", " cat ", " grep ", " wc ", " sort ", " uniq", NULL},
		{"echo hello ", " cat ", " grep ", " wc ", " sort ", " uniq ", " head", NULL},
		{"echo 'hello | world' ", " cat ", " grep ", " wc ", " sort ", " uniq ", " head", NULL},
		{"echo \"hello | world\" ", " cat ", " grep ", " wc ", " sort ", " uniq ", " head", NULL},
		{"echo hello ", " cat ", " grep ", " wc ", " sort ", " uniq ", " head ", " tail", NULL},
		{"echo 'hello | world' ", " cat ", " grep ", " wc ", " sort ", " uniq ", " head ", " tail", NULL},
		{"echo \"hello | world\" ", " cat ", " grep ", " wc ", " sort ", " uniq ", " head ", " tail", NULL},
		{NULL}
	};

	for (int i = 0; test_cases[i] != NULL; i++) {
		char **result = string_blocks(test_cases[i]);
		for (int j = 0; expected_results[i][j] != NULL; j++) {
			if (strcmp(result[j], expected_results[i][j]) != 0) {
				printf("Test case %d failed: expected '%s', got '%s'\n", i, expected_results[i][j], result[j]);
				return;
			}
		}
		printf("Test case %d passed\n", i);
	}
}

int main() {
	test_string_blocks();
	return 0;
}
