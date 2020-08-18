#include <iostream>
#include "App.h"

int main() {
	
	App testBed = App::App(620, 480, "Test Bed");
	bool start_success = testBed.start();
	if (!start_success) {
		return -1;
	}
	return 0;
}