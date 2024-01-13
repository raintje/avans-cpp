#ifndef GAME_HEADERS_DRAWING_PROMPT_DRAWER_H
#define GAME_HEADERS_DRAWING_PROMPT_DRAWER_H

namespace game::drawing {

class PromptDrawer {
 public:
  template<typename T>
  void DrawMap(T obj);

};

} // namespace game::drawing

#endif //GAME_HEADERS_DRAWING_PROMPT_DRAWER_H
