#pragma once
#include <util/types.h>

extern const char *fragment_shader_source;
extern const char *vertex_shader_source;

u32 compile_program(const char *vertex_shader_source, const char *fragment_shader_source);