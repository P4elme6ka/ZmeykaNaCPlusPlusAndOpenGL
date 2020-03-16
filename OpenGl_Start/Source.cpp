#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

int code = 0;

int f_dir;
int s_dir;

bool pressed = false;

int width = 700;
int height = 700;
int cell_edge = 10;

double deg2rad(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}

void drawLine(int xt, int yt, int x2t, int y2t) {
	float x = xt * 2;
	float y = yt * 2;
	float x2 = x2t * 2;
	float y2 = y2t * 2;

	glBegin(GL_LINES);
	glVertex2f(x / width - 1, y / height - 1);
	glVertex2f(x2 / width - 1, y2 / height - 1);
	glEnd();
}

void drawRectangle(int xt, int yt, int x2t, int y2t) {
	float x = xt * 2;
	float y = yt * 2;
	float x2 = x2t * 2;
	float y2 = y2t * 2;
	glBegin(GL_QUADS);
	glVertex2f(x / width - 1, y / height - 1);
	glVertex2f(x2 / width - 1, y / height - 1);
	glVertex2f(x2 / width - 1, y2 / height - 1);
	glVertex2f(x / width - 1, y2 / height - 1);
	glEnd();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DOWN && f_dir != 2 && action == GLFW_PRESS) {
		f_dir = 0;
	}
	if (key == GLFW_KEY_UP && f_dir != 0 && action == GLFW_PRESS ) {
		f_dir = 2;
	}
	if (key == GLFW_KEY_RIGHT && f_dir != 3 && action == GLFW_PRESS) {
		f_dir = 1;
	}
	if (key == GLFW_KEY_LEFT && f_dir != 1 && action == GLFW_PRESS) {
		f_dir = 3;
	}

	if (key == GLFW_KEY_S && s_dir != 2 && action == GLFW_PRESS) {
		s_dir = 0;
	}
	if (key == GLFW_KEY_W && s_dir != 0 && action == GLFW_PRESS) {
		s_dir = 2;
	}
	if (key == GLFW_KEY_D && s_dir != 3 && action == GLFW_PRESS) {
		s_dir = 1;
	}
	if (key == GLFW_KEY_A && s_dir != 1 && action == GLFW_PRESS) {
		s_dir = 3;
	}
}


int mainloop(){
	int f_snake_len = 3;
	int s_snake_len = 3;

	std::vector<int> pol;


	int** pole;

	//int f_dir = 0; // 0 - UP; 1 - RIGHT; 2 - DOWN; 3 - LEFT
	//int s_dir = 0;

	pole = new int*[width / cell_edge + 1];
	for (int i = 0; i < width / cell_edge + 1; i++) {
		pole[i] = new int[height / cell_edge + 1];
	}


	for (int i = 0; i < width / cell_edge; i++)
		for (int j = 0; j < height / cell_edge; j++) {
			pole[i][j] = -1;
		}

	int x_p = rand() % width / cell_edge + 1;
	int y_p = rand() % height / cell_edge + 1;

	pole[x_p][y_p] = -2;

	int f_x = width / cell_edge / 4;
	int f_y = height / cell_edge / 4;

	int s_x = width / cell_edge - (width / cell_edge / 4);
	int s_y = height / cell_edge - (height / cell_edge / 4);

	pole[s_x][s_y] = 2;

	pole[f_x][f_y] = 1;


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(700, 700, "Snake game on the fucking openGL", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetKeyCallback(window, key_callback);
	//glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
	



	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	int pos = 0;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &width, &height);


		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		switch (s_dir)
		{
		case 0:
			s_y--;
			break;
		case 1:
			s_x++;
			break;
		case 2:
			s_y++;
			break;
		case 3:
			s_x--;
			break;
		}

		switch (f_dir)
		{
		case 0:
			f_y--;
			break;
		case 1:
			f_x++;
			break;
		case 2:
			f_y++;
			break;
		case 3:
			f_x--;
			break;
		}

		if (f_y >= height / cell_edge) {
			f_y = 0;
		}
		else if (f_y < 0) {
			f_y = height / cell_edge - 1;
		}

		if (f_x < 0) {
			f_x = width / cell_edge - 1;
		}
		else if (f_x >= width / cell_edge) {
			f_x = 0;
		}


		if (s_y >= height / cell_edge) {
			s_y = 0;
		}
		else if (s_y < 0) {
			s_y = height / cell_edge - 1;
		}

		if (s_x < 0) {
			s_x = width / cell_edge - 1;
		}
		else if (s_x >= width / cell_edge) {
			s_x = 0;
		}

		if (s_x == f_x && s_y == f_y) {
			std::cout << "Nichja" << '\n';
			break;
		}

		if (pole[s_x][s_y] % 2 == 1 && pole[s_x][s_y] > 0) {
			std::cout << "First player win" << '\n';
			break;
		}

		if (pole[f_x][f_y] % 2 == 0 && pole[f_x][f_y] > 0) {
			std::cout << "Second player win" << '\n';
			break;
		}

		if (f_x == x_p && f_y == y_p) {
			f_snake_len++;
			while (pole[x_p][y_p] != -1) {
				x_p = rand() % width / cell_edge + 1;
				y_p = rand() % height / cell_edge + 1;
			}
			pole[x_p][y_p] = -2;
		}

		if (s_x == x_p && s_y == y_p) {
			s_snake_len++;
			while (pole[x_p][y_p] != -1) {
				x_p = rand() % width / cell_edge + 1;
				y_p = rand() % height / cell_edge + 1;
			}
			pole[x_p][y_p] = -2;
		}

		pole[f_x][f_y] = 1;

		pole[s_x][s_y] = 2;

		/* Render here */
		glColor3f(1, 1, 1);

		for (int i = 0; i < 100; i++) {
			drawLine(i * cell_edge, 0, i * cell_edge, height);
			drawLine(0, i * cell_edge, width, i * cell_edge);
		}

		for (int i = 0; i < width / cell_edge + 1; i++)
			for (int j = 0; j < height / cell_edge + 1; j++) {
				if (pole[i][j] > 0) {
					if (pole[i][j] % 2 == 1) {
						glColor3f(1, 0, 0);
						drawRectangle(i * cell_edge, j * cell_edge, i * cell_edge + cell_edge, j * cell_edge + cell_edge);
					}
					if (pole[i][j] % 2 == 0) {
						glColor3f(0, 1, 0);
						drawRectangle(i * cell_edge, j * cell_edge, i * cell_edge + cell_edge, j * cell_edge + cell_edge);
					}
					pole[i][j] += 2;
				}
				if ((pole[i][j] / 2 > f_snake_len && pole[i][j] % 2 == 1) || (pole[i][j] / 2 > s_snake_len && pole[i][j] % 2 == 0)) {
					pole[i][j] = -1;
				}
			}
		glColor3f(0, 0, 1);
		drawRectangle(x_p * cell_edge, y_p * cell_edge, x_p * cell_edge + cell_edge, y_p * cell_edge + cell_edge);

		//drawRectangle(0, 0, 700, 700);

		//glFlush();

		/* Swap front and back buffers */

		glfwSwapBuffers(window);
		pos++;

		/* Poll for and process events */

		glfwPollEvents();

		//Sleep(50);
	}
	glfwDestroyWindow(window);
	delete pole;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << xpos << "  " << ypos << std::endl;
		if (xpos > 350) {
			code = 100;
		}
		if (xpos < 350) {
			code = 200;
		}
	}
		
}


int menu() {

	GLFWwindow* window;

	code = 0;

	window = glfwCreateWindow(700, 700, "Menu", NULL, NULL);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		drawLine(350, 0, 350, 700);


		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (code == 100) {
			glfwDestroyWindow(window);
			return 0;
		}
		if (code == 200) {
			glfwDestroyWindow(window);
			return -1;
		}
	}
	return 0;
}


int main(void)
{
	while (code != -1) {
		mainloop();
		code = menu();
	}
	std::cout << "End";
	glfwTerminate();
	return 0;
}