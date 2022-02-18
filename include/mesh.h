#ifndef MESH_H
#define MESH_H

#include "vec.h"

#include <stdbool.h>

typedef struct {
    Vec3 position;
} Vertex;

typedef struct {
    unsigned int vertex_capacity;
    unsigned int vertex_count;
    Vertex* vertices;

    unsigned int index_capacity;
    unsigned int index_count;
    unsigned int* indices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    bool buffers_mapped;
} Mesh;

Mesh *Mesh_make(unsigned int mesh_count);
void Mesh_init(Mesh *m, unsigned int vertex_capacity, unsigned int index_capacity);
void Mesh_free(Mesh *m);

void Mesh_mapBuffers(Mesh *m);
void Mesh_unmapBuffers(Mesh *m);

void Mesh_draw(const Mesh *m);

#endif