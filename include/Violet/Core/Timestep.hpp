#ifndef VIOLET_TIMESTEP_H_
#define VIOLET_TIMESTEP_H_

namespace Violet {
  struct Timestep {
    Timestep(float time = 0.0f): m_Time(time){}

    float getSeconds() const {return m_Time;}
    float getMilliseconds() const {return m_Time * 1000.0f;}

    float m_Time;
  };
}


#endif // VIOLET_TIMESTEP_H_
