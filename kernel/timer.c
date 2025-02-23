#include "types.h"
#include "sys.h"
#include "vga.h"
#include "interrupt_requests.h"
#include "timer.h"

uint64 timer_ticks = 0;

/*count the number of times the clock interrupt timer has fired*/
/*it fires 18.222 times (...) a second*/

void timer_handler(struct regs *r) {
	timer_ticks++;

	if (timer_ticks % 18 == 0) {
		vga_print("one second has passed \n");
	}
}

void timer_counter_install() {
	irq_install_handler(0, timer_handler);
}
