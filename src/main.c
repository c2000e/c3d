#include "app.h"
#include "shader.h"
#include "mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>


App *app = NULL;
Mesh *meshes = NULL;
Shader *base_shader = NULL;

void init()
{
	base_shader = Shader_make("shaders/vert.glsl", "shaders/frag.glsl");

	meshes = Mesh_make(1);
	Mesh_init(&meshes[0], 3, 3);
	Mesh_mapBuffers(&meshes[0]);

	meshes[0].vertices[0].position[0] = -0.5f;
	meshes[0].vertices[0].position[1] = -0.5f;
	meshes[0].vertices[0].position[2] =  0.0f;
	meshes[0].vertex_count += 1;

	meshes[0].indices[0] = 0;
	meshes[0].index_count += 1;

	meshes[0].vertices[1].position[0] =  0.5f; 
	meshes[0].vertices[1].position[1] = -0.5f;
	meshes[0].vertices[1].position[2] =  0.0f;
	meshes[0].vertex_count += 1;

	meshes[0].indices[1] = 1;
	meshes[0].index_count += 1;

	meshes[0].vertices[2].position[0] =  0.0f;
	meshes[0].vertices[2].position[1] =  0.5f;
	meshes[0].vertices[2].position[2] =  0.0f;
	meshes[0].vertex_count += 1;

	meshes[0].indices[2] = 2;
	meshes[0].index_count += 1;

	Mesh_unmapBuffers(&meshes[0]);

	glClearColor(0.6f, 1.0f, 0.8f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Shader_use(base_shader);
	Mesh_draw(&meshes[0]);
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
	app = App_make(&app_info);
	if (!app) return 1;

	App_run(app, &init, &render);

	App_free(app);

	return 0;
}