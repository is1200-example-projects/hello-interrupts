#include <proc/p32mx320f128h.h>

void _nmi_handler() {
	ODCE = 0;
	TRISECLR = 0xFF;
	for(;;);
}

void _on_bootstrap() {
	
}

void _on_reset() {
	
}
