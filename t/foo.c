#include <stdio.h>
#include <manchicken.h>

int main (void) {
	mutable_string_t foo;
mutable_string_init_with_value(&foo,"foo");
printf("I have value: %s\n", MUTSTR(&foo));
mutable_string_free(&foo);

return 0;
}
