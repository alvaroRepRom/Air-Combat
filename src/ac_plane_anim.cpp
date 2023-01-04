#include "ac_plane_anim.h"
//butano
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_plane_sheet.h"
#include "bn_sprite_ptr.h"

namespace
{
    bn::fixed init_y = 50;
    int pos_angle = 0;
    int const amplitud = 2;
    int const oscilation_speed = 3;
}

namespace ac
{
    /// @brief Creates fly animations on suspension and turnings
    Plane_Anim::Plane_Anim(bn::sprite_ptr& sprite) : _plane(sprite), 
            _action(bn::create_sprite_animate_action_forever(_plane, 2, 
                    bn::sprite_items::plane_sheet.tiles_item(), 1,2,3,4))
    {
        _plane.set_position(0, init_y);
    }

    void Plane_Anim::update()
    {
        // oscilate up and down
        pos_angle += oscilation_speed;
        if (pos_angle >= 360) pos_angle = 0;
        
        _plane.set_y(init_y + amplitud * bn::degrees_cos(pos_angle));
        
        // move to left and right
        bn::fixed x_pos = _plane.x();
        if(bn::keypad::left_held())
        {
            if (x_pos > -10)
                _plane.set_x(x_pos - 1);
        }
        else if(bn::keypad::right_held())
        {
            if (x_pos < 10)
                _plane.set_x(x_pos + 1);
        }
        else // return to original pos
        {
            if (x_pos > 0)
                _plane.set_x(x_pos - 1);
            else if (x_pos < 0)
                _plane.set_x(x_pos + 1);
        }
        // sprite frame animation
        _plane.set_item(bn::sprite_items::plane_sheet, _sprite_frame_select());
    }

    int Plane_Anim::_sprite_frame_select()
    {
        bn::fixed x_pos = _plane.x();
        if (x_pos > 0) {
            if (x_pos > 9) return 4;
            if (x_pos > 6) return 3;
            if (x_pos > 3) return 2;
            return 1;
        }
        else 
        if (x_pos < 0) {
            if (x_pos < -9) return 4;
            if (x_pos < -6) return 3;
            if (x_pos < -3) return 2;
            return 1;
        }
        return 0;
    }
}