import socket
import argparse

def parse_msg_bytes(data):
    msg = data.decode('utf-8').rstrip('\x00')
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
    parser.add_argument('-t', '--timeout', type=float, default=0.1)

    args = parser.parse_args()
    UDP_IP = args.addr
    UDP_PORT = args.port
    UDP_TIMEOUT = args.timeout
    print('Port = ' + str(UDP_PORT))
    print('Addr = ' + UDP_IP)
    print('Timeout = ' + str(UDP_TIMEOUT))

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    sock.settimeout(UDP_TIMEOUT)

    while True:
        print('Waiting for packet')
        try:
            data, from_addr = sock.recvfrom(1024) # buffer size is 1024 bytes
            print("Received from %s the bytes %s" % (from_addr, data))
            msg_parts = parse_msg_bytes(data)
            print(str(msg_parts) + '\n'*3)
            # convert to velocity twist message and pass on to velocity controller

        except socket.timeout:
            print("Timeout occurred")
            # set values to all stop, all zeros


if __name__ == "__main__":
    main()

