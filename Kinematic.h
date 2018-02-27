#ifndef KINEMATIC_H
#define KINEMATIC_H

class Kinematic: public TObject
{
 public:

  Kinematic();
  float KinFunc(vector<Particle> PartVec,float coslep);
  ~Kinematic();
};

#endif
