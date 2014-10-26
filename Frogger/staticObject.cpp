#include "staticObject.h"

StaticObject::StaticObject(float x, float y, float z) : GameObject(x, y, z){}
StaticObject::~StaticObject(){}

void StaticObject::setupObjects(){}
void StaticObject::render(VSShaderLib shader){}