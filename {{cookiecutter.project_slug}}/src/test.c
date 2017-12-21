#include "test.h"

int main(int argc, char **argv) {
	assert_err_list_t *assert_err_list = assert_err_list_new();
	assert_expr(assert_err_list, 1 == 0, "simple test 1", "1 != 0");
	assert_expr(assert_err_list, 0 == 0, "simple test 2", "0 != 0 ???");
	assert_expr(assert_err_list, 2 == 1, "simple test 3", "2 != 1");
	assert_err_list_dump(assert_err_list);
	assert_err_list_destroy(assert_err_list);
}
