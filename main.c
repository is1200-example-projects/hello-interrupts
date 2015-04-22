#include <proc/p32mx320f128h.h>
#include <cp0defs.h>
#include "serial.h"
#include "printf.h"

extern void *__use_isr_install;
extern void _make_syscall();

void isr_test_c() {
	PORTE = 'U';
}

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void dump_mem(unsigned int mem, int n) {
	int i;
	printf("0x%X: ", mem);
	for (i = 0; i < n; i++)
		printf("%x ", *((unsigned char *) ((void *) mem + i)));
	printf("\r\n");
}

int main(void) {
	int i;
	unsigned int ebase, cause, status, random;
	unsigned char tmp;
	delay(10000000);
	ODCE = 0;
	TRISECLR = 0xFF;

	init_serial();

	for (i = 0;; i++) {
		PORTE = i & 0xFF;
		__asm__("mfc0 %0, $15, 1" : "=r"(ebase));
		__asm__("mfc0 %0, $13, 0" : "=r"(cause));
		//__asm__("mfc0 %0, $12, 0" : "=r"(status));
		//status &= (~(1 << 22));
		//__asm__("mtc0 %0, $12, 0" : "=r"(status));
		__asm__("mfc0 %0, $12, 0" : "=r"(status));
		__asm__("mfc0 %0, $1, 0" : "=r"(random));
		
		printf("EBASE:		0x%X\r\n", ebase);
		printf("CAUSE:		0x%X\r\n", cause);
		printf("STATUS:		0x%X\r\n", status);
		printf("INTCON:		0x%X\r\n", INTCON);
		printf("INSTSTAT:	0x%X\r\n", INTSTAT);
		dump_mem(0x9d000200, 16);
		printf("********************\r\n");

		if (i == 0x5A) {
	//		_isr_stub();
/*			__asm__("lui $k0, 62\n"
				"syscall\n"
				"nop\n"
				"j _isr_stub\n"
				"nop\n"
			);*/
			_make_syscall();
		}
	}

	return 0;
}


void printfhex(unsigned int addr) {
	
}
