#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

static void glCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	GLchar const* message,
	void const* user_param
)
{
	fprintf(stderr, "%d: %s\n", id, message);
}

#define WIDTH 1024
#define HEIGHT 768

int main(int argc, char **argv)
{
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: Failed to initialize GLFW.\n");
		return 1;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "c3d", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "ERROR: Failed to create window.\n");
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(glfwGetProcAddress))
	{
		fprintf(stderr, "ERROR: Failed to intialize GLAD.\n");
		return 1;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glCallback, NULL);

	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.6f, 1.0f, 0.8f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}