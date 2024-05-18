#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include "cws/utils/include/fs.h"
#include "cws/utils/include/hashmap.h"
#include "cws/utils/include/conversion.h"

#define MAX_SIZE 2 * 1024 * 4

HashMap *responses, *client_headers, *client_url_params;
HashMap* handle_request_map(char* r);

void handle_request(SOCKET client_socket, int request_code, HashMap* headers, char* client_headers_text) {

	client_headers = handle_request_map(client_headers_text);
	printf("Headers: \n%s\n", hashmap_to_string(client_headers));
	char* response = calloc(MAX_SIZE, sizeof(char));
	sprintf(response, "HTTP/1.1 %d %s\r\n%s\r\n\r\n%s\r\n", request_code, hashmap_get(responses, convert_int_to_string(request_code)), hashmap_to_string(headers), read_file_fs("C:\\Users\\whisc\\OneDrive\\Documents\\CTests\\static\\index.html"));
	send(client_socket, response, strlen(response), 0);
	closesocket(client_socket);
}

HashMap* handle_request_map(char* r) {
	
	HashMap* h = init_hashmap();
	char* request_type = calloc(128, sizeof(char));
	list_T* l = split((char*)r, "\n");


	for(int i = 0; i < l->used; i++) {
		char* e = (char*)l->items[i];
		if (i == 0) { // Work on getting request type
			for (int j = 0; j < l->used; j++) {
				if (e[j] == ' ') {
					break;
				}
				request_type[j] = e[j];
			}
			hashmap_set(h, "Request-Type", request_type);
			char* url = cutoff_by(strchr(e, '/'), " ");
			char* url_encoded_params = "";
			if (is_char_in_string(url, '?')) url_encoded_params = cutoff_by(strchr(e, '?'), " ");
			client_url_params = convert_params_to_map(url_encoded_params);
			printf("URL Params: \n%s", hashmap_to_string(client_url_params));
			hashmap_set(h, "URL", url);
			hashmap_set(h, "URL Encoded Parameters", url_encoded_params);
			continue;
		}
		
		list_T* key_value = split(e, ": ");
		hashmap_set(h, key_value->items[0], key_value->items[1]);
		
	}
	return h;
}
int main()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	SOCKET s, client_socket;
	responses = init_hashmap();
	hashmap_set(responses, "200", "OK");
	hashmap_set(responses, "201", "Created");
	hashmap_set(responses, "202", "Accepted");
	hashmap_set(responses, "203", "Non-Authoritative Information");
	hashmap_set(responses, "204", "No Content");
	hashmap_set(responses, "300", "Multiple Choices");
	hashmap_set(responses, "400", "Bad Request");
	hashmap_set(responses, "404", "Not Found");
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (!s) {
		fprintf(stderr, "Error creating socket...\n");
		WSACleanup();
		return 1;
	}
	struct sockaddr_in server_addr, client_addr;
	int addr_len = sizeof(client_addr);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8000);
	if(bind(s, (const struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		fprintf(stderr, "Failed to bind socket\n");
		closesocket(s);
		WSACleanup();
	}
	printf("Binded socket successfully!\n");

	if(listen(s, SOMAXCONN) == SOCKET_ERROR) {
		fprintf(stderr, "Failed to listen for incoming connections (terminating!)\n");
		closesocket(s);
		WSACleanup();	
	}
	printf("Server running and listening for clients!\n");
	while (1)
	{
		SOCKET client = accept(s, (struct sockaddr*)&client_addr, &addr_len);
		if (client == INVALID_SOCKET) {
			fprintf(stderr, "Error accepting connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			closesocket(s);
			WSACleanup();
			return 1;
		}
		printf("Recieved connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		char request[MAX_SIZE] = {0};
		recv(client, request, MAX_SIZE, 0);
		HashMap* headers = init_hashmap();
		hashmap_set(headers, "Content-Type", "text/html");
		hashmap_set(headers, "Accept", "*/*");
		handle_request(client, 200, headers, request);
	}
	closesocket(s);
	WSACleanup();
	return 0;
}
