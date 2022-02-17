#include "app.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

void init()
{
	glClearColor(0.6f, 1.0f, 0.8f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
	AppInfo app_info = {
		.title = "Christian's 3D Rendering Engine",
		.width = 1024,
		.height = 768,
		.gl_major_version = 4,
		.gl_minor_version = 5
	};

	App *app = App_make(&app_info);
	if (!app) return 1;

	App_run(app, &init, &render);

	App_free(app);

	return 0;
}