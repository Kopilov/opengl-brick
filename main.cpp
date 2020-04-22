#include "mesh.h"
#include "linmath.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    if (!glfwInit()) {
        std::cout << "Initialization failed";
        return 1;
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title brick", nullptr, nullptr);
    if (!window) {
        std::cout << "Window or OpenGL context creation failed";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "glewInit failed";
        glfwTerminate();
        return 1;
    }

    Model model = Model("brick.obj");
    Shader shader = Shader("vertexShader.gl", "fragmentShader.gl");
    GLuint modelview_projection_param = glGetUniformLocation(shader.ID, "MVP");

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float) height;
        glViewport(0, 0, width, height);

        mat4x4 m, p, mvp;
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4_perspective(p, 1.8, ratio, -10.0f, 10.0f);

        mat4x4_translate(m, 0.0f, 1, -3.0f);
        mat4x4_mul(mvp, m, p);

        glUniformMatrix4fv(modelview_projection_param, 1, GL_FALSE, (const GLfloat*)mvp);
        model.Draw(shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
