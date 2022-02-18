#include "shader.h"

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

static char *stringFromFile(const char *path)
{
    // Open file.
    FILE *fp = fopen(path, "rb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Could not open file '%s'\n", path);
        return NULL;
    }

    // Get the length of the file.
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Read file to string.
    char *string = malloc(sizeof *string * ((size_t)size + 1));
    if (string)
    {
        fread(string, sizeof(char), size, fp);
        string[size] = '\0';
    }
    else
    {
        fprintf(stderr, "ERROR: Failed to allocate string for file '%s'\n", path);
        return NULL;
    }
    fclose(fp);
    return string;
}

static GLuint compileShader(const char *shader_source, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    // Handle errors
    GLint is_compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
        GLint size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
        char *string = malloc(size);
        glGetShaderInfoLog(shader, size, &size, string);
        fprintf(stderr, "Failed to compile shader: %s\n", string);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLuint shaderFromFile(const char *shader_path, GLenum shader_type)
{
    const char *shader_source = stringFromFile(shader_path);
    if (!shader_source) return 0;
    return compileShader(shader_source, shader_type);
}

static GLuint linkProgram(GLuint vertex_shader, GLuint fragment_shader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint is_linked;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE)
    {
        GLint size;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
        char* string = (char*)malloc(size);
        glGetProgramInfoLog(program, size, &size, string);
        fprintf(stderr, "Failed to link program: %s\n", string);
        glDeleteProgram(program);
        return 0;
    }

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    return program;
}

static GLuint programFromFiles(const char *vert_shader_path, const char *frag_shader_path)
{
    GLuint vertex_shader = shaderFromFile(vert_shader_path, GL_VERTEX_SHADER);
    if (!vertex_shader) return 0;

    GLuint fragment_shader = shaderFromFile(frag_shader_path, GL_FRAGMENT_SHADER);
    if (!fragment_shader) return 0;

    return linkProgram(vertex_shader, fragment_shader);
}

struct Shader {
    GLuint program;
    const char* vert_shader_path;
    const char* frag_shader_path;
};

Shader *Shader_make(const char *vert_shader_path, const char *frag_shader_path)
{
    GLuint program = programFromFiles(vert_shader_path, frag_shader_path);
    if (!program) return NULL;

    Shader *shader = malloc(sizeof *shader);
    if (!shader) return NULL;

    shader->program = program;
    shader->vert_shader_path = vert_shader_path;
    shader->frag_shader_path = frag_shader_path;
}

void Shader_free(Shader *shader)
{
    if (shader)
    {
        free(shader);
    }
}

void Shader_use(Shader *shader)
{
    glUseProgram(shader->program);
}