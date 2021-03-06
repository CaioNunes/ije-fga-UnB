#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include <iostream>

#include "components/component.hpp"
#include "components/animation_controller.hpp"
#include "game.hpp"
#include "Logger.hpp"
#include <utility>

using namespace engine;

class PlayerController : public Component{
public:
  PlayerController(GameObject &main_game_object, std::string id, ImageComponent *background, AnimationControllerComponent *pAnimCtrl):
    Component(main_game_object,id), limit(true), walkDown(false), walkUp(false),
                                               walkLeft(false), walkRight(false), back(background), isRightPlayer(true), animCtrl(pAnimCtrl){}

    ~PlayerController();

    bool init();
    void update();
    void onCollision();
    void move_player();

    void gravity();
    void jump_player();
    void processPos();
    bool hasGround();

    bool limit;

private:
    bool walkDown;
    bool walkUp;
    bool walkLeft;
    bool walkRight;
    ImageComponent *back;
    bool isRightPlayer;
    AnimationControllerComponent *animCtrl;
};

#endif
