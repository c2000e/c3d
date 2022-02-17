#include "app.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

struct App {
	AppInfo *app_info;
	GLFWwindow *window;
};

App *App_make(const AppInfo *app_info)
{
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: Failed to initialize GLFW.\n");
		return NULL;
	}

	App *app = malloc(sizeof * app);
	if (!app) return NULL;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, app_info->gl_major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, app_info->gl_minor_version);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	app->window = glfwCreateWindow(
		app_info->width,
		app_info->height,
		app_info->title,
		NULL,
		NULL
	);
	if (!app->window)
	{
		fprintf(stderr, "ERROR: Failed to create window.\n");
		App_free(app);
		return NULL;
	}

	glfwMakeContextCurrent(app->window);

	if (!gladLoadGLLoader(glfwGetProcAddress))
	{
		fprintf(stderr, "ERROR: Failed to intialize GLAD.\n");
		App_free(app);
		return NULL;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glCallback, NULL);

	glViewport(0, 0, app_info->width, app_info->height);

	return app;
}

void App_free(App *app)
{
	if (app)
	{
		free(app);
	}
	glfwTerminate();
}

void App_run(const App *app, void (*init_func)(void), void (*loop_func)(void))
{
	init_func();

	while (!glfwWindowShouldClose(app->window))
	{
		if (glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(app->window, true);
		}

		loop_func();

		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}
}