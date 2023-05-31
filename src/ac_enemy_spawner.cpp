#include "ac_enemy_spawner.h"
// butano
#include "bn_log.h"
#include "bn_sound_items.h"
// assets
#include "bn_sprite_items_enemy_red.h"
#include "bn_sprite_items_enemy_green.h"
#include "bn_sprite_items_enemy_purple.h"

namespace ac
{
    namespace {
        constexpr const int FRAMES_GAME_DURATION = constants::FPS * constants::GAME_SECONDS_DURATION;

        constexpr bn::array<Enemy_Type, constants::INGAME_NUM_ENEMIES> enemy_type_array {
            Enemy_Type::Type_1,
            Enemy_Type::Type_1,
            Enemy_Type::Type_2,
            Enemy_Type::Type_1,
            Enemy_Type::Type_1,
            Enemy_Type::Type_2,
            Enemy_Type::Type_3,
            Enemy_Type::Type_2,
            Enemy_Type::Type_2,
            Enemy_Type::Type_3,
            Enemy_Type::Type_2,
            Enemy_Type::Type_1,
            Enemy_Type::Type_1,
            Enemy_Type::Type_3,
            Enemy_Type::Type_2,
            Enemy_Type::Type_2,
            Enemy_Type::Type_2,
            Enemy_Type::Type_3,
            Enemy_Type::Type_2,
            Enemy_Type::Type_1,
            Enemy_Type::Type_1,
            Enemy_Type::Type_2,
            Enemy_Type::Type_2,
            Enemy_Type::Type_3,
            Enemy_Type::Type_1,
            Enemy_Type::Type_2,
            Enemy_Type::Type_3,
            Enemy_Type::Type_1,
            Enemy_Type::Type_1,
            Enemy_Type::Type_2,
            Enemy_Type::Type_2,
            Enemy_Type::Type_3
        };
    }

    Enemy_Spawner::Enemy_Spawner(Game_Events* game_events) : 
        _enemy_array({
            Enemy(bn::sprite_items::enemy_red.create_sprite(0, 0), game_events, Enemy_Type::Type_1),
            Enemy(bn::sprite_items::enemy_red.create_sprite(0, 0), game_events, Enemy_Type::Type_1),
            Enemy(bn::sprite_items::enemy_red.create_sprite(0, 0), game_events, Enemy_Type::Type_1),
            Enemy(bn::sprite_items::enemy_red.create_sprite(0, 0), game_events, Enemy_Type::Type_1),
            Enemy(bn::sprite_items::enemy_green.create_sprite(0, 0), game_events, Enemy_Type::Type_2),
            Enemy(bn::sprite_items::enemy_green.create_sprite(0, 0), game_events, Enemy_Type::Type_2),
            Enemy(bn::sprite_items::enemy_green.create_sprite(0, 0), game_events, Enemy_Type::Type_2),
            Enemy(bn::sprite_items::enemy_green.create_sprite(0, 0), game_events, Enemy_Type::Type_2),
            Enemy(bn::sprite_items::enemy_purple.create_sprite(0, 0), game_events, Enemy_Type::Type_3),
            Enemy(bn::sprite_items::enemy_purple.create_sprite(0, 0), game_events, Enemy_Type::Type_3),
            Enemy(bn::sprite_items::enemy_purple.create_sprite(0, 0), game_events, Enemy_Type::Type_3)
        }),
        _random_generator(),
        _frames_left(FRAMES_GAME_DURATION),
        _game_events(game_events),
        _next_enemy_index(0)
    {}

    void Enemy_Spawner::update()
    {
        for (int i = 0; i < _enemy_array.size(); i++) 
        {
            if (!_enemy_array.at(i).is_active()) continue;
            _enemy_array.at(i).update();
            
            for (auto bullet_collider : _game_events->bullet_col_f_list)
            {
                if (_enemy_array.at(i).check_collision(*bullet_collider)) {
                    bn::sound_items::explosion.play();
                    _game_events->score += _enemy_array.at(i).score_given();
                }
            }
        }

        if (--_frames_left) {
            switch (_frames_left)
            {
            case FRAMES_GAME_DURATION - 2 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 3 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 6 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 8 * constants::FPS:
                _spawn();
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 10 * constants::FPS:
                _spawn();
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 14 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 15 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 18 * constants::FPS:
                _spawn();
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 19 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 20 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 21 * constants::FPS:
                _spawn();
                _spawn();
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 23 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 24 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 25 * constants::FPS:
                _spawn();
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 27 * constants::FPS:
                _spawn();
                _spawn();
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 28 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 29 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 30 * constants::FPS:
                _spawn();
                break;
            case FRAMES_GAME_DURATION - 32 * constants::FPS:
                _spawn();
                _spawn();
                _spawn();
                _spawn();
                _spawn();
                break;
            default:
                break;
            }
        }
        else {
            _game_events->gameHasEnded = true;
        }
    }

    void Enemy_Spawner::_spawn()
    {
        int wanted_enemy_type = enemy_type_array.at(_next_enemy_index);
        _next_enemy_index++;

        for (int i = 0; i < _enemy_array.size(); i++)
        {
            if (_enemy_array.at(i).enemy_type() == wanted_enemy_type &&
                !_enemy_array.at(i).is_active())
            {
                _enemy_array.at(i).init();
                return;
            }
        }
    }
}