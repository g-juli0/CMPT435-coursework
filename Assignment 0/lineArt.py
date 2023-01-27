################################
# Gianna Julio
# Period 7-8 HCP
# Line Art Program
# Purpose: draws line art based on user's input
################################

import pygame, sys, math, random

#initialize game engine
pygame.init()

#open and set window size
w = 800
h = 800
size = (w,h)
surface = pygame.display.set_mode(size)

#set title bar
pygame.display.set_caption("Line Art!")

#color constants
BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
RED =   (255,   0,   0)
GREEN = (  0, 255,   0)
BLUE =  (  0,   0, 255)
YELLOW= (255, 255, 0  )

#---------------------Functions:

def randomColor():
    r = random.randint(0, 256)
    g = random.randint(0, 256)
    b = random.randint(0, 256)
    COLOR = (r, g, b)
    return COLOR

def drawLines(xAnchor, yAnchor, COLOR, numSegments, quadrant):
    gap = w/numSegments
    
    for i in range(numSegments):
        pygame.draw.line(surface, COLOR, xAnchor, yAnchor, 1)
        
        if quadrant == 1:
            xAnchor[0] += gap
            yAnchor[1] += gap
        elif quadrant == 2:
            xAnchor[0] -= gap
            yAnchor[1] += gap
        elif quadrant == 3:
            xAnchor[0] -= gap
            yAnchor[1] -= gap
        elif quadrant == 4:
            xAnchor[0] += gap
            yAnchor[1] -= gap
    
def getIntBetween(message, low, high):
    num = low - 1
    
    while(num > high or num < low):     # continue while number is out of range
        try:
            num = int(input(message + " between " + str(low) + " and "+ str(high) + ": "))
            if num > high or num < low:
                print("Error - number out of range. Try again.")
            
        except ValueError:
            print("Error - invalid number. Try again.")
            
    return num

#---------------------Main Program Loop:

def main():
    
    numSegments = getIntBetween("Enter a number", 10, 100)
    COLOR1 = randomColor()
    COLOR2 = randomColor()
    COLOR3 = randomColor()
    COLOR4 = randomColor()
    
    while(True):
        for event in pygame.event.get():
            if (event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE)):
                pygame.quit()
                sys.exit()
                
                #game logic:

        #set background color
        surface.fill(BLACK)
        
        #drawing code:
        drawLines([0, h], [0, 0], COLOR1, numSegments, 1)
        drawLines([w, h], [w, 0], COLOR2, numSegments, 2)
        drawLines([w, 0], [w, h], COLOR3, numSegments, 3)
        drawLines([0, 0], [0, h], COLOR4, numSegments, 4)
        
        #last line - update screen
        pygame.display.update()

main()