/*(C) 2010 Gayam Pradeepkumar <deepu.aprjc@gmail.com>		*/

#include "id.h"

int main() {
	int time1 = 0;
	while(1) {
		time1 = idletime();
		printf("Idle time is :%i\n", time1);
		sleep(1);
	}

	return 1;
}
