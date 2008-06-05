//#include <lwip/sys.h>
//#include <lwip/sockets.h>
//#include <lwip/inet.h>
#include <lwip/api.h>

void net_test() {
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

	{
		char httpreq[] = "GET /\r\n\r\n";
		struct netconn *conn;
		struct ip_addr addr;
		struct netbuf *buf;
		void *data;
		u16_t len;
		char char_buf[256];

		conn = netconn_new(NETCONN_TCP);
		IP4_ADDR(&addr, 133, 27, 4, 127);	// www.sfc.keio.ac.jp
		netconn_connect(conn, &addr, 80);
		printf("connect\n");
		netconn_write(conn, httpreq, sizeof(httpreq), NETCONN_COPY);
		printf("write\n");
		while ((buf = netconn_recv(conn)) != NULL) {
			do {
				netbuf_data(buf, &data, &len);
				memcpy(char_buf, data, len < 256 ? len : 256);
				printf(char_buf);
			} while (netbuf_next(buf) >= 0);
		}
		netconn_close(conn);
		printf("close\n");
		netconn_delete(conn);
	}
}
