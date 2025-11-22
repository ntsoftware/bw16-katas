#!/usr/bin/env python3

import socket

remote_ip = "10.42.0.39"
remote_port = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print(f"socket: {sock}")

request = "Hello, World!"
sock.sendto(request.encode("utf-8"), (remote_ip, remote_port))

response, remote_addr = sock.recvfrom(1024)
response = response.decode("utf-8")
print(f"received '{response}' from {remote_addr}")

