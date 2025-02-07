#ifndef TEXT_PARTICLE_HPP
#define TEXT_PARTICLE_HPP
#include "../entity.hpp"
class Text_particle : public Entity
{
  public:
    float xa, ya, za;
    float xx, yy, zz;
    Text_particle(char* msg, uint8_t msg_length, int x, int y, uint8_t col);      // col = textcolor
    Text_particle(uint8_t number, uint8_t msg_length, int x, int y, uint8_t col); // col = textcolor
    ~Text_particle();
    void tick() override;
    void render(int x_scroll, int y_scroll) override;

  private:
    char* msg;
    uint8_t number;
    uint8_t msg_length;
    uint8_t col;
    uint8_t time;
};
#endif
