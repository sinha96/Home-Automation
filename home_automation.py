import RPi.GPIO as gpio
import time
import credentials
from datetime import datetime
gpio.setmode(gpio.BCM)
gpio.setwarnings(False)

#Gardening system
gpio.setup(21,gpio.IN)#Soil moisture sensor
gpio.setup(17,gpio.OUT)#Water pump
gpio.setup(20,gpio.IN)#moisture feedback



#living room laod
gpio.setup(9,gpio.OUT)#light
gpio.setup(11,gpio.OUT)#study lamp
gpio.setup(5,gpio.OUT)#fan
gpio.setup(6,gpio.IN)#LM35


#bedroom load
gpio.setup(13,gpio.OUT)#light
gpio.setup(26,gpio.OUT)#study lamp
gpio.setup(19,gpio.OUT)#fan
gpio.setup(14,gpio.IN)#LM35

#master bedroom load
gpio.setup(24,gpio.OUT)#light
gpio.setup(18,gpio.OUT)#study lamp
gpio.setup(23,gpio.OUT)#fan
gpio.setup(15,gpio.IN)#LM35

#bathroom load
gpio.setup(25,gpio.OUT)#light

#kitchen Load
gpio.setup(7,gpio.OUT)#light


print("Home Automation System")


############################################# SMTP service ######################################################
import smtplib
def mail(msg):
    server = smtplib.SMTP('smtp.gmail.com:587')
    server.starttls()
    server.login(credentials.user_name,credentials.password)
    server.sendmail('sinhapriyanshushekhar@gmail.com','sslabs@outlook.com',msg)
    server.quit()
    print('mail sent for {}'.format(msg))

while True:
    
    ############################################# Gardening System ######################################################
    
    if gpio.input(21) == 1 and gpio.input(17) == 0:
        mail("{} - Pump is turned on".format(datetime.now().strftime("%c")))
        gpio.output(17,gpio.HIGH)
        mail("Pump is turned on")
        f = open('home_log.txt','a')
        f.write('{} - Pump is turned on'.format(datetime.now().strftime("%c")))
        f.close()
    elif gpio.input(21) == 0 and gpio.input(17) == 1:
        mail("{} - Pump is turned off".format(datetime.now().strftime("%c")))
        gpio.output(17,gpio.LOW)
        f = open('home_log.txt','a')
        f.write('{} - Pump is turned off'.format(datetime.now().strftime("%c")))
        f.close()
        
        
        
    if gpio.input(20) == 1 and gpio.inpt(17) == 1:
        gpio.setup(17,gpio.LOW)\
        mail("{} - Pump is turned off due to overflowing of water and its time to change soil moisture".format(datetime.now().strftime("%c")))
        f = open('home_log.txt','a')
        f.write("{} - Pump is turned off due to overflowing of water and its time to change soil moisture".format(datetime.now().strftime("%c")))
        f.close()

    
    ############################################# Living Room ######################################################
        
    if datetime.now().time().strftime("%I:%M%p") >= '05:00PM':
        gpio.output(9,gpio.HIGH)
        gpio.output(11,gpio.HIGH)
        f = open('home_log.txt','a')
        f.write("{} - Master's Lights Turned off".format(datetime.now().strftime("%c")))
        f.close()
    if datetime.now().time().strftime("%I:%M%p") >= '06:30AM':
        gpio.output(9,gpio.LOW)
        gpio.output(11,gpio.LOW)
        f = open('home_log.txt','a')
        f.write("{} - Master's Lights Turned off".format(datetime.now().strftime("%c")))
        f.close()


    ############################################# BedRoom ##########################################################

    if datetime.now().time().strftime("%I:%M%p") >= '05:00PM':
        gpio.output(18,gpio.HIGH)
        gpio.output(24,gpio.HIGH)
        f = open('home_log.txt','a')
        f.write("{} - Bedroom's Lights Turned off".format(datetime.now().strftime("%c")))
        f.close()
    if datetime.now().time().strftime("%I:%M%p") >= '06:30AM':
        gpio.output(18,gpio.LOW)
        gpio.output(24,gpio.LOW)
        f = open('home_log.txt','a')
        f.write("{} - Bedroom's Lights Turned off".format(datetime.now().strftime("%c")))
        f.close()

    ############################################# Master BedRoom ##########################################################

    if datetime.now().time().strftime("%I:%M%p") >= '05:00PM':
        gpio.output(13,gpio.HIGH)
        gpio.output(26,gpio.HIGH)
        f = open('home_log.txt','a')
        f.write("{} - Master bedroom's Lights Turned off".format(datetime.now().strftime("%c")))
        f.close()
    if gpio.input(13) is false:
        gpio.output(13,gpio.LOW)
        gpio.output(26,gpio.LOW)
        f = open('home_log.txt','a')
        f.write("{} - Master bedroom's Lights Turned off".format(datetime.now().strftime("%c")))
        f.close()
    

    ############################################# Bathroom Room ##########################################################

    if gpio.input(7):
        f = open('home_log.txt','a')
        f.write("{} - Bathroom's Lights Turned On".format(datetime.now().strftime("%c")))
        f.close()
    

    ############################################# Kitchen Room ##########################################################

    if gpio.input(25):
        f = open('home_log.txt','a')
        f.write("{} - Kitchen's Lights Turned On".format(datetime.now().strftime("%c")))
        f.close()

    
    


        
    
    
    
    



