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
    if (!gladLoadGL()) {
        std::cout << "gladLoadGL failed";
        glfwTerminate();
        return 1;
    }
    glEnable(GL_DEPTH_TEST);

    Model model = Model("brick.obj");
    Shader shader = Shader("vertexShader.gl", "fragmentShader.gl");

    shader.use();
    float pi = 3.1415926f;

//    shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//    shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
//    shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//    shader.setFloat("material.shininess", 0.0f);
//    shader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
//    shader.setVec3("light.diffuse",  1.0f, 1.0f, 1.0f);
//    shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glDisable(GL_BLEND);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float) height;
        glViewport(0, 0, width, height);

        mat4x4 p;

        glm::mat4 m = glm::mat4(1.0f);
        m = glm::translate(m, glm::vec3(-1.0f, 0.0f, -5.0f));
        m = glm::rotate(m, (float)glfwGetTime() * 2, glm::vec3(1.0f, 0.0f, 0.0f));
        m = glm::rotate(m, (float)glfwGetTime() / 2, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        mat4x4_perspective(p, 1.8f, ratio, 0.001f, 60);

        shader.use();
        shader.setMat4("model", glm::value_ptr(m));
        shader.setMat4("view", glm::value_ptr(view));
        shader.setMat4("projection", (const GLfloat*)p);
        shader.setVec3("lightPos", 2.0, 2.0, -3.0);

        shader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
        shader.setVec3("light.diffuse",  1.0f, 1.0f, 1.0f);
        shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        model.Draw(shader);

        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
