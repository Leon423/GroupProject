#include "stdafx.h"

#include "keyboard_manager.h"
#include <allegro5/allegro.h>
#include <cstdlib>


namespace csis3700 {
  keyboard_manager *keyboard_manager::default_instance = NULL;

  keyboard_manager *keyboard_manager::get() {
    if (default_instance == NULL)
      default_instance = new keyboard_manager();
    return default_instance; 
  }

  keyboard_manager::keyboard_manager() {
  }

  bool keyboard_manager::is_key_down(int keycode) {
    ALLEGRO_KEYBOARD_STATE s;
    al_get_keyboard_state(&s);
    return al_key_down(&s,keycode);
  }


}
