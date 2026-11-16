import random
import time

def sensoroutput (x) :
    if x == "soil_moisture":
        return random.randint (0, 100)
    elif x == "humidity": 
        return random.randint (0, 100)
    elif x == "temp":
        return round(random.uniform(10.0, 40.0), 1)
    elif x == "light":
        return round(random.uniform(0.0, 100000.0), 1)
    elif x == "night_time":
        return random.choice([True, False])

def run_greenhouse_automation () :
    sensors = ["soil_moisture","humidity", "temp","light","night_time"]
    data = {s: sensoroutput (s) for s in sensors}

    #soil moisture
    moisture = data["soil_moisture"]
    print(f"soil_moisture = {moisture}%")
    if moisture <= 20:
        print("soil is very dry.\nwater pump: on for 15 min")
    elif moisture <= 50:
        print("soil is dry.\nwater pump: on for 8 min")
    else:
        print("water pump: off")

    #temperature
    temp = data["temp"]
    print(f"Temperature = {temp} cel")
    if temp>24:
        print("cooling fan: on")
    elif temp<18:
        print("turn on heater")
    else:
        print("temperature :normal")

    #humidity
    humidity = data["humidity"]
    print(f"humidity: {humidity}%")
    if humidity>=50:
        print("sufficient humidity")
    else:
        print("Misting system on")

    #light and night
    light = data["light"]
    night_time = data["night_time"]
    print(f"light intensity: {light} lux")
    if night_time:
            print("action: turn off lights")
    else:
        if light<10000:
            print("action: turn on lights")
        elif light>20000:
            print("action: dim lights")
        else:
            print("action: ideal light condition")

    print("\n\n")

try: 
    while True:
        run_greenhouse_automation ()
        time.sleep(2)
except KeyboardInterrupt:
    print("\n Automation stopped by user")