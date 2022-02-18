#ifndef SHADER_H
#define SHADER_H

typedef struct Shader Shader;

Shader *Shader_make(const char *vert_shader_path, const char *frag_shader_path);
void Shader_free(Shader *shader);

void Shader_use(Shader *shader);

#endif