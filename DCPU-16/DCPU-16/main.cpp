#include <cstdio>
#include "bccore.h"

int main(int argc, char* argv[]) {
	BCCore app;
	int i;
	app.setRamValue(0, 0x9401);
	app.setRamValue(1, 0x7801);
	app.setRamValue(2, 70);
	app.step();
	app.step();
	printf("A : %d | B : %d | C : %d\n", app.getRegisterValue(0), app.getRegisterValue(1), app.getRegisterValue(2));
	printf("X : %d | Y : %d | Z : %d\n", app.getRegisterValue(3), app.getRegisterValue(4), app.getRegisterValue(5));
	printf("I : %d | J : %d |\n", app.getRegisterValue(6), app.getRegisterValue(7));

	scanf("%d", &i);
	return 0;
}