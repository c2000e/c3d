#include "mesh.h"

#include <glad/glad.h>

#include <stdlib.h>
#include <stdio.h>

Mesh *Mesh_make(unsigned int mesh_count)
{
    Mesh *m = malloc(sizeof *m * mesh_count);
    if (!m)
    {
        fprintf(stderr, "ERROR: Failed to allocate meshes!\n");
        return NULL;
    }
    return m;
}

void Mesh_init(Mesh *m, unsigned int vertex_capacity, unsigned int index_capacity)
{
    m->vertex_capacity = vertex_capacity;
    m->vertex_count = 0;

    m->index_capacity = index_capacity;
    m->index_count = 0;

    m->buffers_mapped = false;

    glGenVertexArrays(1, &m->vao);
    glBindVertexArray(m->vao);

    glGenBuffers(1, &m->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof *m->vertices * vertex_capacity, NULL, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof *m->indices * index_capacity, NULL, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh_free(Mesh *m)
{
    if (m)
    {
        m->vertex_capacity = 0;
        m->vertex_count = 0;

        m->index_capacity = 0;
        m->index_count = 0;

        Mesh_unmapBuffers(m);

        glDeleteVertexArrays(1, &m->vao);
        glDeleteBuffers(1, &m->vbo);
        glDeleteBuffers(1, &m->ebo);
    }
}

void Mesh_mapBuffers(Mesh *m)
{
    if (!m->buffers_mapped)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
        m->vertices = (Vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ebo);
        m->indices = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

        m->buffers_mapped = true;
    }
}

void Mesh_unmapBuffers(Mesh *m)
{
    if (m->buffers_mapped)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        m->vertices = NULL;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ebo);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        m->indices = NULL;

        m->buffers_mapped = false;
    }
}

void Mesh_draw(const Mesh *m)
{
    if (!m->buffers_mapped)
    {
        glBindVertexArray(m->vao);
        glDrawElements(GL_TRIANGLES, m->index_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}