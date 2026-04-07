import pygame
import random

# 游戏窗口大小
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

# 网格大小和蛇的初始长度
GRID_SIZE = 20
INITIAL_LENGTH = 4

# 颜色
GRAY = (128, 128, 128)
RED = (255, 0, 0)
YELLOW = (255, 255, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

# 游戏状态
GAME_OVER = 0
PLAYING = 1
WIN = 2

class SnakeGame:
    def __init__(self):
        pygame.init()
        self.window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        pygame.display.set_caption("Snake Game")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont(None, 30)

        self.snake = [(WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2)]
        self.direction = "right"
        self.speed = 5
        self.score = 0
        self.state = PLAYING

        self.food = self.generate_food()
        self.obstacles = self.generate_obstacles()

    def generate_food(self):
        x = random.randint(0, WINDOW_WIDTH // GRID_SIZE - 1) * GRID_SIZE
        y = random.randint(0, WINDOW_HEIGHT // GRID_SIZE - 1) * GRID_SIZE
        type = random.choice(['yellow', 'green', 'blue'])
        return (x, y, type)

    def generate_obstacles(self):
        obstacles = []
        for _ in range(3):
            x = random.randint(0, WINDOW_WIDTH // GRID_SIZE - 1) * GRID_SIZE
            y = random.randint(0, WINDOW_HEIGHT // GRID_SIZE - 1) * GRID_SIZE
            obstacles.append((x, y))
        return obstacles

    def draw_grid(self):
        for x in range(0, WINDOW_WIDTH, GRID_SIZE):
            pygame.draw.line(self.window, GRAY, (x, 0), (x, WINDOW_HEIGHT))
        for y in range(0, WINDOW_HEIGHT, GRID_SIZE):
            pygame.draw.line(self.window, GRAY, (0, y), (WINDOW_WIDTH, y))

    def draw_snake(self):
        for segment in self.snake:
            pygame.draw.rect(self.window, GRAY, (segment[0], segment[1], GRID_SIZE, GRID_SIZE))

    def draw_food(self):
        x, y, type = self.food
        if type == "yellow":
            color = YELLOW
        elif type == "green":
            color = GREEN
        elif type == "blue":
            color = BLUE
        pygame.draw.rect(self.window, color, (x, y, GRID_SIZE, GRID_SIZE))

    def draw_obstacles(self):
        for obstacle in self.obstacles:
            pygame.draw.rect(self.window, RED, (obstacle[0], obstacle[1], GRID_SIZE, GRID_SIZE))

    def draw_score(self):
        score_text = self.font.render("Score: " + str(self.score), True, GRAY)
        self.window.blit(score_text, (10, 10))

    def draw_speed(self):
        speed_text = self.font.render("Speed: " + str(self.speed), True, GRAY)
        self.window.blit(speed_text, (10, 40))

    def game_over(self):
        self.state = GAME_OVER
        game_over_text = self.font.render("GAME OVER", True, RED)
        self.window.blit(game_over_text, (WINDOW_WIDTH // 2 - 70, WINDOW_HEIGHT // 2 - 20))

    def win(self):
        self.state = WIN
        win_text = self.font.render("YOU WIN", True, GREEN)
        self.window.blit(win_text, (WINDOW_WIDTH // 2 - 50, WINDOW_HEIGHT // 2 - 20))

    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    return

            if self.state == PLAYING:
                self.window.fill(pygame.Color("black"))

                keys = pygame.key.get_pressed()
                if keys[pygame.K_UP] or keys[pygame.K_w]:
                    if self.direction != "down":
                        self.direction = "up"
                elif keys[pygame.K_DOWN] or keys[pygame.K_s]:
                    if self.direction != "up":
                        self.direction = "down"
                elif keys[pygame.K_LEFT] or keys[pygame.K_a]:
                    if self.direction != "right":
                        self.direction = "left"
                elif keys[pygame.K_RIGHT] or keys[pygame.K_d]:
                    if self.direction != "left":
                        self.direction = "right"

                head = self.snake[0]
                if self.direction == "up":
                    new_head = (head[0], head[1] - GRID_SIZE)
                elif self.direction == "down":
                    new_head = (head[0], head[1] + GRID_SIZE)
                elif self.direction == "left":
                    new_head = (head[0] - GRID_SIZE, head[1])
                elif self.direction == "right":
                    new_head = (head[0] + GRID_SIZE, head[1])

                self.snake.insert(0, new_head)

                if len(self.snake) > INITIAL_LENGTH:
                    self.snake.pop()

                if new_head == self.food[:2]:
                    if(self.food[2]=='yellow'):
                        self.score += 10
                    elif(self.food[2]=='green'):
                        self.score += 20
                    elif(self.food[2]=='blue'):
                        self.score += 30
                    self.speed = 5 + self.score // 100
                    self.food = self.generate_food()
                    self.snake.append((0, 0))  # 新增一个网格长度

                if new_head in self.obstacles or new_head[0] < 0 or new_head[0] >= WINDOW_WIDTH or new_head[1] < 0 or new_head[1] >= WINDOW_HEIGHT:
                    self.game_over()

                if self.score >= 1000:
                    self.win()

                self.draw_grid()
                self.draw_snake()
                self.draw_food()
                self.draw_obstacles()
                self.draw_score()
                self.draw_speed()

                pygame.display.update()
                self.clock.tick(self.speed)
            elif self.state == GAME_OVER:
                self.window.fill(pygame.Color("black"))
                self.game_over()
                pygame.display.update()
            elif self.state == WIN:
                self.window.fill(pygame.Color("black"))
                self.win()
                pygame.display.update()

if __name__ == "__main__":
    game = SnakeGame()
    game.run()
