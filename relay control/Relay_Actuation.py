import logging
import WolkConnect
import WolkConnect.Sensor as Sensor
import WolkConnect.Actuator as Actuator
import WolkConnect.WolkDevice as WolkDevice
import WolkConnect.Serialization.WolkMQTTSerializer as WolkMQTTSerializer
import time

import paho.mqtt.client as mqtt




def onMessageReceived(message):
    msg = message[0]
    print(msg.value)



logger = logging.getLogger("WolkConnect")
WolkConnect.setupLoggingLevel(logging.INFO)

# Device parameters
serial = "RELAYACTUATOR"
password = "3e2df556-7548-469a-8750-2b390f26ce2f"


relaySwitch = Actuator.RelaySwitch(False)

actuators = [relaySwitch]


try:
    serializer = WolkMQTTSerializer.WolkSerializerType.JSON_MULTI
    device = WolkDevice.WolkDevice(serial, password,
        serializer=serializer, actuators=actuators, responseHandler=onMessageReceived)
    device.connect()
    device.publishAll()
    device.publishAllReadings()



    while True:
        time.sleep(1)


except WolkConnect.WolkMQTT.WolkMQTTClientException as e:
    print("WolkMQTTClientException occured with value: " + e.value)

