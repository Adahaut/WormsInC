#ifndef _H3_TANK_H_
#define _H3_TANK_H_

#include <h3.h>

#define TANK_TYPEID 0x02000019

H3_CAPI_BEGIN_BLOCK
//void TANK_Init(H3Handle object);
void TANK_Terminate(void* properties);
void TANK_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void TANK_ColliderON(H3Handle object, SH3Collision collide);
void TANK_ColliderLeave(H3Handle object, H3Handle other);
void* TANK_CreateProperties(H3Handle scene, H3Handle tank);

H3_CAPI_END_BLOCK

#define TANK_CREATE(SCN, OBJ)											\
	(SH3Component) {																			\
		.Terminate          = TANK_Terminate,												\
		.Update             = TANK_Update,													\
		.isInitialized      = false,															\
		.OnCollisionEnter   = TANK_ColliderON,					\
		.OnCollisionLeave   = TANK_ColliderLeave,											\
		.componentType      = TANK_TYPEID,													\
		.properties         = TANK_CreateProperties(SCN, OBJ)			\
}


#endif /* _H3_COMPONENTS_TANK_H_ */

