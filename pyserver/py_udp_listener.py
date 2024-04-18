import socket
import argparse

def parse_msg_bytes(data):
    msg = data.decode('utf-8').rstrip('\x00')
    print("received message: %s" % msg)
    msg_parts = msg.split();
    return msg_parts

def main():

    UDP_IP = '127.0.0.1'
    UDP_PORT = '17998'

    parser = argparse.ArgumentParser(
        prog='udp listener python',
        description='Receives a velocity command message from an attached client',
        epilog='example provided by Rick :)')

    parser.add_argument('-p', '--port', type=int, default=UDP_PORT) 
    parser.add_argument('-i', '--addr', default=UDP_IP)

    args = parser.parse_args()
    UDP_IP = args.addr
    UDP_PORT = args.port
    print('Port = ' + str(UDP_PORT))
    print('Addr = ' + UDP_IP)

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))

    while True:
        print('Waiting for packet')
        data, from_addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        print("Received from %s the bytes %s" % (from_addr, data))
        msg_parts = parse_msg_bytes(data)
        print(str(msg_parts) + '\n'*3)


if __name__ == "__main__":
    main()

