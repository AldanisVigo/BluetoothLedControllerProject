int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

void uart_init(uint16_t ubrr);

/* http://www.ermicro.com/blog/?p=325 */

extern FILE uart_tx;
extern FILE uart_rx;

unsigned char receiveWord(const uint16_t length,unsigned char * response);