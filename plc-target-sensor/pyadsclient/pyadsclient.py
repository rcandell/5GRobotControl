"""
author: Rick Candell

"""
import pyads
import winsound


# for linux only
# create some constants for connection
#CLIENT_NETID = "10.10.0.100.1.1"
#CLIENT_IP = "10.10.0.100"
#TARGET_IP = "10.10.0.9"
#TARGET_USERNAME = "Administrator"
#TARGET_PASSWORD = "1"
#ROUTE_NAME = "route-to-my-plc"

#pyads.add_route_to_plc(
#    CLIENT_NETID, CLIENT_IP, TARGET_IP, TARGET_USERNAME, TARGET_PASSWORD,
#    route_name=ROUTE_NAME
#)

TARGET_NETID = '5.53.143.24.1.1'
plc = pyads.Connection(TARGET_NETID, pyads.PORT_TC3PLC1)
plc.open()
print("OPENED")

plc.read_state()
print("READ")

bVal = plc.read_by_name('GVL_input.sensor[2]')
print("Bool value = " + str(bVal))
if bVal:
    frequency = 2500    # Set Frequency To 2500 Hertz
    duration = 1000     # Set Duration To 1000 ms == 1 second
    winsound.Beep(frequency, duration)    
