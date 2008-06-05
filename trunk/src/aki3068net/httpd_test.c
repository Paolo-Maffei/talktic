#include <lwip/api.h>
#include "jsint.h"
#include "base64.h"

#define CHAR_BUFFER_SIZE 1024

const static char html[] = "HTTP-1.0 200 OK\r\nContent-type: text/html\r\n\r\n<h1>hogehoge!</h1>";

static void httpd_init() {
	struct netconn *conn, *client_conn;
	struct netbuf *buf;
	char *data;
	char char_buf[CHAR_BUFFER_SIZE];
	char bytecode[CHAR_BUFFER_SIZE];
	u16_t current_char_buf_pos;
	u16_t len, i;

	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, 0, 80);
	netconn_listen(conn);
	printf("start listen...\n");
	while(1) {
		client_conn = netconn_accept(conn);
		if(client_conn) {
			printf("accept!\n");
			current_char_buf_pos = 0;
			while(buf = netconn_recv(client_conn)) {
				do {
					netbuf_data(buf, (void**)&data, &len);
					for(i=0; i<len; i++) {
						putchar(*(data+i));
						char_buf[current_char_buf_pos++] = *(data+i);
						if(current_char_buf_pos > CHAR_BUFFER_SIZE) {
							netbuf_delete(buf);
							goto bye;
						}
						if(current_char_buf_pos>4) {
							if(char_buf[current_char_buf_pos-4] == '\r'
								&& char_buf[current_char_buf_pos-3] == '\n'
								&& char_buf[current_char_buf_pos-2] == '\r'
								&& char_buf[current_char_buf_pos-1] == '\n') {
								netbuf_delete(buf);
								goto bye;
							}
						}
					}
				} while (netbuf_next(buf) >= 0);
				printf("next!\n");
				netbuf_delete(buf);
			}
bye:
			netconn_write(client_conn, (void *)html, sizeof(html), NETCONN_COPY);
			printf("bye...");
			netconn_close(client_conn);
			netconn_delete(client_conn);
			cyg_thread_delay(10);
			printf("!\n");

			if(current_char_buf_pos>5) {
				if(char_buf[0] == 'G' && char_buf[1] == 'E' && char_buf[2] == 'T' &&
					char_buf[3] == ' ' && char_buf[4] == '/') {
					for(i = 5; i<current_char_buf_pos; i++) {
						if(char_buf[i] == ' ') {
							len = i - 5;
							char_buf[i] = '\0';
							printf("%s\n", char_buf+5);
							len = base64_decode(char_buf+5, bytecode, sizeof(bytecode));
							bytecode[len] = '\0';
							printf("%s\n", bytecode);
							break;
						}
					}
				}
			}
		}
	}
}

void init_httpd() {
	lwip_init();

	printf("wait...\n");
	while (1) {
		u32_t a = netif_default->ip_addr.addr;
		if (a) {
			printf("ip_addr %d.%d.%d.%d\n",
				   ((a >> 24) & 0xff), ((a >> 16) & 0xff), ((a >> 8) & 0xff), (a & 0xff));
			break;
		}
	}

	sys_thread_new(httpd_init, (void *)0, 7);
}
