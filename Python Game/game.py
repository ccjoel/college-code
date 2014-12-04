import pygame
import pygame.key
import random
import pygame.mixer

# ------ Global Constants -----
FPS = 15
DOWN = 0
UP = 1
LEFT = 2
RIGHT = 3
white = (255,255,255)
black = (0,0,0)
screen_width=700
screen_height=700
SPEED = 12
LINK_SIZE = 70
# ------ Global Constants -----

# ---------- Player -----------
class Player():
	direction = DOWN
	moving = False
	change = 1

	def __init__(self ):
		self.image = pygame.image.load("links.gif")
		self.image.convert()
		self.rect = self.image.get_rect()	
		self.imageNum = [1 for x in range(0,4)]
		self.links = [[] for x in range(4)] 
		self.setup_images()
	
	def setup_images(self):
		self.links[LEFT] = []
		for nbr in range(1,7):
			alink = self.image.subsurface((24*(nbr-1),28,23,26))
			alink = alink.convert_alpha()
			alink.set_colorkey(black)
			alink = pygame.transform.scale(alink,(LINK_SIZE,LINK_SIZE))
			self.links[LEFT].append(alink)
		
		self.links[RIGHT] = []
		for nbr in range(7,13):
			newValue=24*(nbr-1)
			to=23
			if nbr == 12:
				to = to - 1
				newValue = newValue-1
			alink = self.image.subsurface(newValue,28,to,26)
			alink = alink.convert_alpha()
			alink.set_colorkey(black)
			alink = pygame.transform.scale(alink,(LINK_SIZE,LINK_SIZE))
			self.links[RIGHT].append(alink)
	
		self.links[UP] = []
		coordinates = [(282,28,20,26), (305,28,20,26),
					   (327,28,20,26), (348,28,20,26),
					   (370,28,20,26), (391,28,20,26),
					   (414,28,20,26), (437,28,20,26)]

		for i in coordinates:
			alink=self.image.subsurface(i)
			alink = alink.convert_alpha()
			alink = pygame.transform.scale(alink,(LINK_SIZE-18,LINK_SIZE))
			self.links[UP].append(alink)


		self.links[DOWN] = []
		coordinates = []
		for i in range(143, 291, 21):
			coordinates.append((i,0,25,24))

		for i in coordinates:
				alink=self.image.subsurface(i)
				alink = alink.convert_alpha()
				alink = pygame.transform.scale(alink,(LINK_SIZE,LINK_SIZE))
				self.links[DOWN].append(alink)
		
		
	def move(self, direction):
		self.direction = direction
		self.moving = True
		if direction == DOWN:
			self.rect.y+=SPEED
		if direction == UP:
			self.rect.y-=SPEED
		if direction == RIGHT:
			self.rect.x+=SPEED
		if direction == LEFT:
			self.rect.x-=SPEED
		return
			
	def getImage(self):
		if self.moving == False:
			return self.links[self.direction][3] #3
		else:
			returned = self.links[self.direction][self.imageNum[self.direction]]
			self.imageNum[self.direction] += self.change
			if self.imageNum[self.direction] == len(self.links[self.direction]):
				self.imageNum[self.direction]=0
			return returned
# ---------- Player -----------
		

class Game():
	def __init__(self):
		pygame.init()                                 					  # Initialize Pygame
		self.screen=pygame.display.set_mode([screen_width,screen_height]) # Set the height and width of the screen
		self.player = Player()					   						  # Define player and set random location
		self.player.rect.x = 200
		self.player.rect.y = 200
		
		self.cycletime = 0 
		self.interval = 150
		self.done=False 							  					 # Loop until the user clicks the close button.
		self.clock=pygame.time.Clock()				  					 # Used to manage how fast the screen updates
 
		self.mypicture = self.player.getImage()
		
		#MUSIC!
		pygame.mixer.music.load('dark.mp3')
		pygame.mixer.music.play(-1)
 
		# -------- Main Game Loop -----------
		while self.done==False:
			self.getKeyboardEvents()
			self.screen.fill(black)
			self.milliseconds = self.clock.tick(FPS)   # milliseconds since last frame
			self.cycletime += self.milliseconds
			
			self.mypicture = self.player.getImage()
				
			self.screen.blit(self.mypicture, (self.player.rect.x,self.player.rect.y))
	
			for event in pygame.event.get():           # User did something
				if event.type == pygame.QUIT:          # If user clicked close
					done=True                          # Flag that we are done so we exit this loop
	
			pygame.display.flip()
		# -------- Main Game Loop -----------
			
			
	def getKeyboardEvents(self):
		self.player.moving = False
		if pygame.key.get_pressed()[pygame.K_DOWN]:
			self.player.move(DOWN)
		if pygame.key.get_pressed()[pygame.K_UP]:
			self.player.move(UP)
		if pygame.key.get_pressed()[pygame.K_RIGHT]:
			self.player.move(RIGHT)
		if pygame.key.get_pressed()[pygame.K_LEFT]:
			self.player.move(LEFT)
				
	pygame.quit()
#Call Game:
Game()