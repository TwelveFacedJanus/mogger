#include <stdio.h>
#include <stdlib.h>
#include <mogger.h>
#include <stdint.h>

uint32_t __test_allocate_memory_for_mc()
{
	MoggerCore* mc = init_mogger("./mental_logs.mg");
	if (mc == NULL) {
		destroy_mogger(mc);
		printf("[TEST allocate_memory_for_mc]: Failed to allocate memory.\n");
		return -1;
	}
	printf("[TEST allocate_memory_for_mc]: Memory has benn allocated.");
	return 0;
}

uint32_t __test_file_exists()
{
	MoggerCore* mc = init_mogger("./mental_test.mct");
	if (mc == NULL) {
		destroy_mogger(mc);
		printf("[TEST file exists]: Failed to allocate memory for mc\n");
		return -1;
	}
	if (mc->file != NULL) {
		printf("[TEST file exists]: File exists.\n");
		destroy_mogger(mc);
		return 0;
	}
	printf("[TEST file exists]: File doesnt exists.\n");
	return -1;
}


void run_tests()
{
	uint32_t tests_count = 2;

	uint32_t (*operations[2])() = { __test_allocate_memory_for_mc, __test_file_exists };
	uint32_t error_count = 0;
	uint32_t success_count = 0;
	for (uint32_t i = 0; i < tests_count; i++) {
		if (operations[i]() == 0) {
			success_count++;
		} else {
			error_count++;
		}
		printf("\n");
	}
	printf("TESTS RESULT: %d PASSED, %d WARN\n", success_count, error_count);
	
}

int main() {
	run_tests();
}
