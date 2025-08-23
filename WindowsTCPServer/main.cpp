#include <QCoreApplication>
#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WSADATA win_sock_data;
    int wsa_startup;
    int wsa_cleanUp;

    SOCKET tcp_server_socket;
    int socket_close_state;
    struct sockaddr_in add_tcp_server;
    struct sockaddr_in add_tcp_client;
    int add_tcp_client_state = sizeof(add_tcp_client);
    int socket_bind;
    int socket_listen;
    SOCKET accept_socket;

    int send_state;
    char sender_buffer_data[] = {'e', 's', 'e', 'n', 'e', 'y',
                                 'r', 'i', 'b', 'a', 's'};
    int sender_buffer_length = 11;

    int recv_state;
    char recv_buffer_data[16];
    int recv_buffer_length = 16;

    wsa_startup = WSAStartup(MAKEWORD(2,2), &win_sock_data);
    if (wsa_startup != 0)
        printf("WSAStartup Failed.\n");
    printf("WSAStartup Success.\n");

    add_tcp_server.sin_family = AF_INET;
    add_tcp_server.sin_addr.s_addr = inet_addr("192.168.1.145");
    add_tcp_server.sin_port = htons(5120);

    tcp_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcp_server_socket == INVALID_SOCKET)
        printf("TCP Server Socket Creation Failed.\n");
    printf("TCP Server Socket Creation Success.\n");

    socket_bind = bind(tcp_server_socket, (SOCKADDR*)&add_tcp_server,
                       sizeof(add_tcp_server));
    if (socket_bind == SOCKET_ERROR)
        printf("Binding Failed & Error No-> %s\n", WSAGetLastError());
    printf("Binding Success.\n");

    socket_listen = listen(tcp_server_socket, 2);
    if (socket_listen == SOCKET_ERROR)
        printf("Listen Failed & Error No-> %s\n", WSAGetLastError());
    printf("Listen Success.\n");

    accept_socket = accept(tcp_server_socket, (SOCKADDR*)&add_tcp_client,
                           &add_tcp_client_state);
    if (accept_socket == INVALID_SOCKET)
        printf("Accept Failed & Error No-> %s\n", WSAGetLastError());
    printf("Connection Accepted.\n");
    sleep(5);

    send_state = send(accept_socket, sender_buffer_data,
                      sender_buffer_length, 0);
    if (send_state == SOCKET_ERROR)
        printf("Sending Failed % Error No-> %s\n", WSAGetLastError());
    printf("Data Sending Success.\n");

    recv_state = recv(accept_socket, recv_buffer_data,
                      recv_buffer_length, 0);
    if (recv_state == SOCKET_ERROR)
        printf("Receive Data Failed & Error No -> %s\n", WSAGetLastError());
    printf("Data Received Data: %s\n", recv_buffer_data);

    socket_close_state = closesocket(tcp_server_socket);
    if (socket_close_state == SOCKET_ERROR)
        printf("Closing Socket Failed & Error No -> %s\n", WSAGetLastError());
    printf("Closing Socket Success.\n");

    wsa_startup = WSACleanup();
    if (wsa_startup == SOCKET_ERROR)
        printf("CleanUp Failed & Error No -> %s.\n", WSAGetLastError());
    printf("CleanUp FunSuccess.\n");

    return a.exec();
}
