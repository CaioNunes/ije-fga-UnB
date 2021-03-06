#include "alligator_controller.hpp"

bool AlligatorController::init() {
    min = _main_game_object->main_positionX - 100;
    max = _main_game_object->main_positionX + 100;
    animController->flipping(!isRight);

    return true;
}

void AlligatorController::update(){
    animController->play_animation("alligator1_walking");
    head->main_positionX = _main_game_object->main_positionX + (_main_game_object->main_width / 2.0);
    head->main_positionY = _main_game_object->main_positionY - 10.0;

    gravity();
    processPos();
    onCollision();
    // move();
}

void AlligatorController::gravity(){
    if(!hasGround()){
        aceleration_alligator += gravityForce_alligator;
    }else{
        aceleration_alligator = 0;
    }
}

void AlligatorController::processPos(){
    prev_position_y_alligator = _main_game_object->main_positionY;
    _main_game_object->main_positionY += aceleration_alligator;
}

bool AlligatorController::hasGround(){
    ground_alligator = Game::instance.collision_manager->checkCollision(_main_game_object, "ground");
    if(ground_alligator && aceleration_alligator >= 0){
        if(aceleration_alligator > 5){
            _main_game_object->main_positionY = ground_alligator->main_positionY - _main_game_object->main_height;
        }
        return true;
    }
    return false;
}

void AlligatorController::onCollision(){
    if(Game::instance.collision_manager->checkCollision(_main_game_object, "ground")){
        walkDown = false;
    }

    if(Game::instance.collision_manager->checkCollision(head, "player")){
        head->setState(GameObject::State::disabled);
        head->shutdown();
        _main_game_object->setState(GameObject::State::disabled);
        _main_game_object->shutdown();
        // _main_game_object->setState(GameObject::State::disabled);
    }

}

void AlligatorController::move(){
    if(_main_game_object->main_positionX <= min){
        walkRightAlligator = true;
    }

    if(_main_game_object->main_positionX >= max){
        walkRightAlligator = false;
    }

    if(walkRightAlligator){
        _main_game_object->main_positionX += moveSide_alligator;
    }else{
        _main_game_object->main_positionX -= moveSide_alligator;
    }
}

AlligatorController::~AlligatorController(){}
