#include <stdio.h>
#include <stdlib.h>
#include <mogger.h>

int main() {
	MoggerCore* mc = init_mogger("./mental-logs.mg");
	mc->log(mc, "hello!");
	mc->print(mc,"qweqweqwe!!! %s", "hello!!!!");
	destroy_mogger(mc);
}
