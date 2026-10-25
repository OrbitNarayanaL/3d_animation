#include "glad.h"
#include <GLFW/glfw3.h>

int gladLoadGLLoader(GLADloadproc load)
{
    (void)load;
    return 1;
}

const unsigned char* glGetString(GLenum name) { (void)name; return (const unsigned char*)"OpenGL 3.3"; }
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { (void)red; (void)green; (void)blue; (void)alpha; }
void glClear(GLbitfield mask) { (void)mask; }
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) { (void)x; (void)y; (void)width; (void)height; }
unsigned int glCreateShader(GLenum type) { (void)type; return 1; }
void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length) { (void)shader; (void)count; (void)string; (void)length; }
void glCompileShader(GLuint shader) { (void)shader; }
void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) { (void)shader; (void)pname; if (params) *params = 1; }
void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) { (void)shader; (void)bufSize; if (length) *length = 0; if (infoLog) infoLog[0] = 0; }
unsigned int glCreateProgram(void) { return 1; }
void glAttachShader(GLuint program, GLuint shader) { (void)program; (void)shader; }
void glLinkProgram(GLuint program) { (void)program; }
void glGetProgramiv(GLuint program, GLenum pname, GLint *params) { (void)program; (void)pname; if (params) *params = 1; }
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) { (void)program; (void)bufSize; if (length) *length = 0; if (infoLog) infoLog[0] = 0; }
void glDeleteShader(GLuint shader) { (void)shader; }
void glDeleteProgram(GLuint program) { (void)program; }
void glUseProgram(GLuint program) { (void)program; }
void glGenVertexArrays(GLsizei n, GLuint *arrays) { for (GLsizei i = 0; i < n; i++) arrays[i] = 1; }
void glGenBuffers(GLsizei n, GLuint *buffers) { for (GLsizei i = 0; i < n; i++) buffers[i] = 1; }
void glBindVertexArray(GLuint array) { (void)array; }
void glBindBuffer(GLenum target, GLuint buffer) { (void)target; (void)buffer; }
void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) { (void)target; (void)size; (void)data; (void)usage; }
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) { (void)index; (void)size; (void)type; (void)normalized; (void)stride; (void)pointer; }
void glEnableVertexAttribArray(GLuint index) { (void)index; }
void glDrawArrays(GLenum mode, GLint first, GLsizei count) { (void)mode; (void)first; (void)count; }
void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) { (void)n; (void)arrays; }
void glDeleteBuffers(GLsizei n, const GLuint *buffers) { (void)n; (void)buffers; }
