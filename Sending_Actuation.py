import requests
from enum import Enum
import time


host = 'https://api-demo.wolkabout.com/api/'
signIn = 'emailSignIn'
getPoints = "points/"


pointId = -1
actuatorId = -1
actuatorReference = "RVR"
deviceName = "Rover Demo"
credentials = {"username": "mlupurovic@execom.eu", "password": "Execom123"}

resp = requests.post(host+signIn, json=credentials)

if(resp.status_code == 200):
    token = resp.json()["accessList"][0]["accessToken"]
else:
    print("ERROR: Status Code " + resp.status_code)
    exit()

resp = requests.get(host+getPoints, headers={'Authorization': 'Bearer '+token})

print(resp.status_code)

if(resp.status_code == 200):
    for item in resp.json():
        if item['name'] == deviceName:
            pointId = item['id']
            for actuator in item['actuators']:
                if actuator['reference'] == actuatorReference:
                    actuatorId = actuator['id']

else:
    print("ERROR: Status Code " + resp.status_code)
    exit()


print("Actuator id: " + str(actuatorId))
print("Point id: " + str(pointId))
actuation = "points/"+str(pointId)+"/actuators/"+str(actuatorId)+"/actuations"

resp = requests.post(host+actuation,  headers={'Authorization': 'Bearer '+token}, data='stop')
