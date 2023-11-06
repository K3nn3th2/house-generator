#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "camera.h"
#include <iostream>
#include <random>
#include <vector>
//#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


const int WIDTH = 1920;
const int HEIGHT = 1080;

const int MAX_HOUSES = 50;

// dimensional constraints for the houses

const float MAX_POS_X = 25.0;
const float MAX_POS_Z = 25.0;

const float MIN_HOUSE_WIDTH = 1.5;
const float MIN_HOUSE_LENGTH = 1.5;
const float MIN_HOUSE_HEIGHT_WALL = 1.5;

const float MAX_HOUSE_WIDTH = 3.5;
const float MAX_HOUSE_LENGTH = 7.5;
const float MAX_HOUSE_HEIGHT_ROOF = 7.5;
const float MAX_HOUSE_HEIGHT_WALL = 4.0;

float house_highest = 0.0;

// initialize random number generator
std::random_device rd;
std::mt19937 gen(rd());


// camera
Camera camera(glm::vec3(25.0f, 10.0f, 25.0f));
glm::mat4 mat_projection = glm::perspective(glm::radians(80.0f), (float)WIDTH / (float)HEIGHT, 1.0f, 150.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float startFrame = 0.0f;
float currentFrame = 0.0;
float duration = 0.0;
float ratio = 0.0;

float random_val(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    float generated = dist(gen);
    return generated;
}

class House{
    
    public:
        float height_roof, height_wall, width, length;
        float pos_x, pos_z;
        float pos_y = 0.0; //on ground level
        float colour_wall_r, colour_wall_g, colour_wall_b;
        float colour_roof_r, colour_roof_g, colour_roof_b;
        glm::mat4 mat_model = glm::mat4(1.0f);

        House(){
           pos_x = random_val(-MAX_POS_X, MAX_POS_X);
           pos_z = random_val(-MAX_POS_Z, MAX_POS_Z);
           set_random_dimensions();
           set_random_colours();
        }

        // specific constructor in case needed
        House(float x, float y, float z, float w, float l, float h_r, float h_w, float col_wall_r, float col_wall_g, float col_wall_b, float col_roof_r, float col_roof_g, float col_roof_b){
           pos_x = x;
           pos_z = z;

           width = w;
           length = l;
           height_roof = h_r;
           height_wall = h_w;

           colour_wall_r = col_wall_r;
           colour_wall_g = col_wall_g;
           colour_wall_b = col_wall_b;
           colour_roof_r = col_roof_r;
           colour_roof_g = col_roof_g;
           colour_roof_b = col_roof_b;
        }

        // This method sets the dimensional attributes to random values within the specified boundaries.
        void set_random_dimensions(){
           //mat_model = glm::rotate(glm::mat4(1.0f), (float)glm::radians(random_val(0.0, 359.0)), glm::vec3(0.0, 1.0, 0.0));
           width = random_val(MIN_HOUSE_WIDTH, MAX_HOUSE_WIDTH);
           length = random_val(MIN_HOUSE_LENGTH, MAX_HOUSE_LENGTH);
           height_wall = random_val(MIN_HOUSE_HEIGHT_WALL, MAX_HOUSE_HEIGHT_WALL);
           height_roof = random_val(height_wall, MAX_HOUSE_HEIGHT_ROOF);

           if (height_roof > house_highest)
               house_highest = height_roof;
        }

        void set_random_colours(){
           colour_wall_r = random_val(0.0, 1.0);
           colour_wall_g = random_val(0.0, 1.0);
           colour_wall_b = random_val(0.0, 1.0);
           colour_roof_r = random_val(0.0, 1.0);
           colour_roof_g = random_val(0.0, 1.0);
           colour_roof_b = random_val(0.0, 1.0);
        }

};


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

double get_clip_height(){
     double height_clip = house_highest;
     if (duration <= 1.0){ // increase clipping plane height.
         ratio = duration;
         height_clip = ratio * house_highest;

     }else if(duration >= 5.0){ // total animation cycle is over. reset clip plane height and timer 
         height_clip = 0.0;
         std::cout << "Resetting animation." << std::endl; 
         startFrame = static_cast<float>(glfwGetTime());

     }else if(duration >= 4.0){ // lower the clipping plane.
         ratio = (duration - 4.0);
         double dist = house_highest - ratio * house_highest;
         height_clip = dist;
     }
     return height_clip;

}

int main() {
    // Initialize GLFW and GLEW
    glfwInit();

    // Create a window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Parametric House Renderer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    std::vector<House*> houses;
    int amount_houses = (int)random_val(12.0, (double)MAX_HOUSES);

    for (int i = 0; i < amount_houses; i++){
        House* random_house = new House();
        houses.push_back(random_house);
    }

    glewInit();
    glEnable(GL_DEPTH_TEST);
    Shader shader("vertexShader.vert", "fragmentShader.frag", "geometryShader.geom");
    shader.use();
    glEnable(GL_CLIP_PLANE0);

    // Use the shader program
    float startFrame = static_cast<float>(glfwGetTime());

    double height_clip;

    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        duration = currentFrame - startFrame;
        lastFrame = currentFrame;

        height_clip = get_clip_height();
        if (duration > 5.0){
            house_highest = 0.0;
            for (House* house : houses){
                house->set_random_dimensions();
            }
            startFrame = static_cast<float>(glfwGetTime());
        }


        glm::mat4 mat_view = camera.GetViewMatrix();;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setFloat("u_height_clip", height_clip);
        for(House* house : houses){
           shader.setFloat("u_width", house->width);
           shader.setFloat("u_length", house->length);
           shader.setFloat("u_height_wall", house->height_wall);
           shader.setFloat("u_height_roof", house->height_roof);
           shader.setVec4("u_location", house->pos_x, house->pos_y, house->pos_z, 1.0);
           shader.setVec3("u_colour_roof", house->colour_roof_r, house->colour_roof_g, house->colour_roof_b);
           shader.setVec3("u_colour_wall", house->colour_wall_r, house->colour_wall_g, house->colour_wall_b);
           shader.setMat4("u_mvp", mat_projection * mat_view * house->mat_model);
           glDrawArrays(GL_POINTS, 0, 10);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
