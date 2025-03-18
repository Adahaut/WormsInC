#include <components/bullet.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/audiosourcecomponent.h>
typedef struct
{
    bool dest;
    int a;
    int b;
} bullet_Properties;

//void bullet_Terminate(void* properties) {
//	free(properties);
//}

void bullet_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {

    bullet_Properties* props = (bullet_Properties*)properties;

    if (props->dest == false) {
        static H3Handle paw = NULL;
            paw = H3_Sound_Load("assets/boom.wav");

       // H3_Object_AddComponent(object, AUDIOSOURCECOMPONENT_CREATE(paw));
        H3_Sound_Play(paw, 1.0, false);
        H3_Object_Destroy(&object, false);
    }

    }



void bullet_ColliderON(H3Handle self, SH3Collision collide) {
    bullet_Properties* props = (bullet_Properties*)H3_Object_GetComponent(self, BULLET_TYPEID)->properties;
    printf("bine");
    props->dest = false;
}


void* bullet_CreateProperties(int a, int b) {
    bullet_Properties* properties = malloc(sizeof(bullet_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->a = a;
    properties->b = b;
    return properties;
}

