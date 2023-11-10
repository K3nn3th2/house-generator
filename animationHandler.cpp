#include "animationHandler.h"

AnimationHandler::AnimationHandler(float x, float y, float z, float fov){
    // Initialize renderer
    renderer = Renderer(x, y, z, fov);
    // generate house data
    generate_houses();

}

// generates house data
void AnimationHandler::generate_houses(){

   // hard coded positions to make it look like a road in a village
    std::vector<std::vector<float>> housePositions = {
      { 30.0, 0.0, 7.0 },
      { 27.0, 0.0, 7.5 },
      { 18.0, 0.0, 6.7 },
      { 14.2, 0.0, 7.0 },
      { 11.2, 0.0, 7.0 },
      { 4.0, 0.0, 7.5 },
      { 1.0, 0.0, 6.5 },
      { -1.5, 0.0, 7.1 },
      { -4.5, 0.0, 6.1 },
      // opposite
      { 28.0, 0.0, -1.0 },
      { 25.0, 0.0, -0.1 },
      { 18.0, 0.0, -1.7 },
      { 14.2, 0.0, -1.0 },
      { 11.2, 0.0, -1.3 },
      { 7.2, 0.0, -1.0 },
      { 3.6, 0.0, 1.2 },
      { 0.6, 0.0, -1.2 },
      { -2.9, 0.0, -0.2 },
    };

    int amount_houses = Random::get(MIN_RANDOM_HOUSES, MAX_RANDOM_HOUSES);

    // add randomly placed houses
    for (int i = 0; i < amount_houses; i++){
        House random_house;
        houses.push_back(random_house);
        if (random_house.height_roof > house_highest)
            house_highest = random_house.height_roof;
    }
    // add houses for the positions for our village road
    for (std::vector<float> pos : housePositions){
        House random_house(pos[0], pos[1], pos[2]);
        houses.push_back(random_house);
        if (random_house.height_roof > house_highest)
            house_highest = random_house.height_roof;
    }
}
// calculates the clipping plane height according to the current time and highest building
void AnimationHandler::calculate_clip_height(){

    float visible_amount;
     if (timer.time_total <= 1.0){ // increase clipping plane height.
         visible_amount = timer.time_total;
         renderer.height_clip = visible_amount * house_highest;

     }else if(timer.time_total >= 5.0){ // total animation cycle is over. reset clip plane height and timer 
         renderer.height_clip = 0.0;
         //std::cout << "Resetting animation." << std::endl; 
         timer.frame_start = static_cast<float>(glfwGetTime());

     }else if(timer.time_total >= 4.0){ // lower the clipping plane.
         visible_amount = (timer.time_total - 4.0);
         renderer.height_clip = house_highest - visible_amount * house_highest;
     }
}

// animation loop
void AnimationHandler::loop(){
    timer.start();

    while (!glfwWindowShouldClose(renderer.window)) {

        handle_input_kb();
        // Time handling
        timer.measure();

        calculate_clip_height();

        // reset house parameters and time when the 5 sec cycle is over
        if (timer.time_total > 5.0){
            house_highest = 0.0;
            for (House& house : houses){
                house.randomize();
                if (house.height_roof > house_highest)
                    house_highest = house.height_roof;
            }
            timer.start();
        }
        renderer.render(houses);
    }

    // Clean up
    renderer.terminate();

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void AnimationHandler::handle_input_kb()
{
    if (glfwGetKey(renderer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(renderer.window, true);

    if (glfwGetKey(renderer.window, GLFW_KEY_W) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(FORWARD, timer.time_delta);
    if (glfwGetKey(renderer.window, GLFW_KEY_S) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(BACKWARD, timer.time_delta);
    if (glfwGetKey(renderer.window, GLFW_KEY_A) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(LEFT, timer.time_delta);
    if (glfwGetKey(renderer.window, GLFW_KEY_D) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(RIGHT, timer.time_delta);
}
