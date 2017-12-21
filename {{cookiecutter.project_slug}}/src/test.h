#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define TEST_MAX_ERR 2
#define TEST_STR_SIZE 256

typedef struct assert_err {
	char *name;
	char *msg;
} assert_err_t;

typedef struct assert_err_list {
	assert_err_t *assert_err;
	size_t err_size;
  size_t assertions;
} assert_err_list_t;

assert_err_list_t *assert_err_list_new() {
	assert_err_list_t *assert_err_list = malloc(sizeof(assert_err_list_t));
	assert_err_list->assert_err = malloc(sizeof(assert_err_t)*TEST_MAX_ERR);
	assert_err_list->err_size = 0;
	return assert_err_list;
}

assert_err_t *assert_err_new(const char *name, const char *msg) {
	assert_err_t *assert_err = malloc(sizeof(assert_err_t));
	assert_err->name = malloc(sizeof(char)*TEST_STR_SIZE);
	assert_err->msg = malloc(sizeof(char)*TEST_STR_SIZE);
	strcpy(assert_err->name, name);
	strcpy(assert_err->msg, msg);
	return assert_err;
}

int assert_err_list_append(assert_err_list_t *assert_err_list, assert_err_t assert_err) {
	if (assert_err_list->err_size < TEST_MAX_ERR) {
		assert_err_list->assert_err[assert_err_list->err_size++] = assert_err;
		return 1;
	} else {
		return 0;
	}
}

void assert_err_list_destroy(assert_err_list_t *assert_err_list) {
	for (size_t i = 0; i < assert_err_list->err_size; i++) {
		free(assert_err_list->assert_err[i].name);
		free(assert_err_list->assert_err[i].msg);
	}
	free(assert_err_list->assert_err);
	free(assert_err_list);
}

void assert_err_list_dump(assert_err_list_t *assert_err_list) {
	for (size_t i = 0; i < assert_err_list->err_size; i++) {
		assert_err_t assert_err = assert_err_list->assert_err[i];
		printf("id: %lu\nname: %s\nmessage: %s\n\n", i, assert_err.name, assert_err.msg);
	}
}

void assert_expr(assert_err_list_t *assert_err_list, bool expr, const char *name, const char *msg) {
	if (!expr) {
		assert_err_t *assert_err = assert_err_new(name, msg);
		int success = assert_err_list_append(assert_err_list, *assert_err);
		if (success) {
			return;
		} else {
			printf("Error overflow... dumping failures:\n");
			assert_err_list_dump(assert_err_list);
			exit(1);
		}
	}
}
