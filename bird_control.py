import pygame
import time
import serial


ser = serial.Serial(port='COM4', baudrate=1200, bytesize=8, parity='N', stopbits=1, timeout=2)
time.sleep(2)  # delay for error-free serial communication setting



#This function retrieves and organizes data for the x-axis

def get_read_x_axis_serial_port():
   
    data = list(ser.read(6))
    
   
    if str(data[0]) == str(101) and str(data[1]) == str(101):
        x = str(data[2])
       
        if x <= str(255) and x >= str(190):
            x = int(255-int(x))
            x = int(-1*int(x))
            
        elif x >= str(0) and x <= str(65):
            x = int(x)   
                    
        return x   
    else:  
        
        return 0
    

#This function retrieves and organizes data for the y-axis

def get_read_y_axis_serial_port():
    
    data = list(ser.read(6)) 
    
    if str(data[0]) == str(101) and str(data[1]) == str(101):
        y = str(data[3])
        if y <= str(255) and y >= str(190):
            y = int(255-int(y))
            y = int(-1*int(y))
        elif y >= str(0) and y <= str(65):
            y = int(y) 
        return y     
    else:
         
        return 0
 

       
         
        



pygame.init()

user_window=pygame.display.set_mode((520,520))
img = pygame.image.load("bird.png")
img = pygame.transform.scale(img,(80,80))
starting_img_x = 220
starting_img_y = 220

#This part sends a control value to receive X and Y data regularly
 
x_y_enable = True
while x_y_enable:
    ser.write('1A'.encode('latin_1')) 
    x_y_enable= False

#This loop retrieves the necessary data for the user window and constantly updates it

state= True
while state:

    get_data_x = get_read_x_axis_serial_port()
    get_data_y =get_read_y_axis_serial_port()
    if int(get_data_x) >= -65 and int(get_data_y) >=-65:
        data_x = get_data_x
        data_y = get_data_y
  
    
    user_window.fill((250,0,0))  
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            
         state = False
    
    user_window.blit(img,((starting_img_x+int(data_x)*3),(starting_img_y+int(data_y)*3)))
    pygame.display.update()


pygame.quit()  