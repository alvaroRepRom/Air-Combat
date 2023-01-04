#include "Intellisense.h"
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
        
        // animation
        x_pos = _plane.x();
        int sprite_index = 0;        
        if (x_pos > 9)
            sprite_index = 4;
        else if (x_pos > 6)
            sprite_index = 3;
        else if (x_pos > 3)
            sprite_index = 2;
        else if (x_pos > 0)
            sprite_index = 1;

        _plane.set_item(bn::sprite_items::plane_sheet, sprite_index);
    }
}