
// Created by finagnon on 04/04/2022.
//
//
// Created by finagnon on 04/04/2022.
#include "table.h"
static void test_hash(void** state){

	assert_in_range(hash("machine18"),1,9999999999);
}
static void test_hset(void** state){
	assert_true(h_set("machine38","123.18.123.120"));

}

static void test_getvalue(void** state){
	assert_int_equal(get_value("machine38"),1);

}
static void test_del(void** state){
	assert_true(key_val_delete("machine38"));
}

int main(void){
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_hash),
		cmocka_unit_test(test_hset),
		cmocka_unit_test(test_getvalue),
		cmocka_unit_test(test_del), };
	return cmocka_run_group_tests_name("table",tests,NULL,NULL);
}
