/*(C) 2010 Gayam Pradeepkumar <deepu.aprjc@gmail.com>		*/

#include "id.h"

int main() {
	unsigned long time = 0;
	while(1) {
		time = idletime();
		printf("Idle time is :%lu\t", time);
	}

	return 1;
}
