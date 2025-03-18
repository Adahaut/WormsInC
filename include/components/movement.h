#ifndef _H3_MOVEMENT_H_
#define _H3_MOVEMENT_H_

#include <h3.h>

#define MOVEMENT_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
//void movement_Init(H3Handle object);
void movement_Terminate(void* properties);
void movement_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void movement_ColliderON(H3Handle object, SH3Collision collide);
void movement_ColliderLeave(H3Handle object, H3Handle other);
void* movement_CreateProperties(H3Handle scene, H3Handle object, bool fire);

H3_CAPI_END_BLOCK

#define MOVEMENT_CREATE(SCENE, TANKL, FIRE)											\
	(SH3Component) {																			\
		.Terminate          = movement_Terminate,												\
		.Update             = movement_Update,													\
		.isInitialized      = false,															\
		.OnCollisionEnter   = movement_ColliderON,												\
		.OnCollisionLeave	= movement_ColliderLeave,											\
		.componentType      = MOVEMENT_TYPEID,													\
		.properties         = movement_CreateProperties(SCENE, TANKL, FIRE)			\
}


#endif /* _H3_COMPONENTS_MOVEMENT_H_ */
