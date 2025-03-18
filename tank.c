#include <components/tank.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <components/tank.h>
#include <components/spritecomponent.h>
#include <components/audiosourcecomponent.h>
#include <components/bullet.h>

typedef struct
{
    H3Handle scene;
    H3Handle tankR;
    H3Handle object2;
    bool IsGrounded;
    bool fire;
    bool player1;
} tank_Properties;


void TANK_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    tank_Properties* props = (tank_Properties*)properties;

    int mx;
    int my;
    float px;
    float py;
    static int _time = 0;

    H3_Input_GetMousePos(h3, &mx, &my); //Mouse's Position
    H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py); //Ship's Position


    float dx = mx - px;
    float dy = my - py;

    float dist = sqrtf(dx * dx + dy * dy); //Determinate the distance between Ship and Mouse
    float  angle = atan2((dy), (dx)); //Determinate the angle using Mouse's Pos and Ship's Pos

    if (H3_Input_IsKeyDown(K_Right)) {
        if (H3_Input_IsKeyPressed(K_Up) && props->IsGrounded) {
            float pvx = 0;
            float pvy = -500.0f;
            H3_Object_SetVelocity(object, pvx, pvy);
        }
        float pvx = 100.0f;
        float pvy;
        float bin;
        H3_Object_GetVelocity(object, &bin, &pvy);
        H3_Object_SetVelocity(object, pvx, pvy);
    }
    else if (H3_Input_IsKeyDown(K_Left)) {
        if (H3_Input_IsKeyPressed(K_Up) && props->IsGrounded) {
            float pvx = 0;
            float pvy = -500.0f;
            H3_Object_SetVelocity(object, pvx, pvy);

        }
        float pvx = -100.0f;
        float pvy;
        float bin;
        H3_Object_GetVelocity(object, &bin, &pvy);
        H3_Object_SetVelocity(object, pvx, pvy);

    }
    else if (H3_Input_IsKeyPressed(K_Up) && props->IsGrounded) {
        float pvx = 0;
        float pvy = -500.0f;
        H3_Object_SetVelocity(object, pvx, pvy);

    }
    else
    {
        float pvx;
        float pvy;
        H3_Object_GetVelocity(object, &pvx, &pvy);
        pvx *= 0.99f;
        pvy *= 1;
        H3_Object_SetVelocity(object, pvx, pvy);

    }

    if (H3_Input_IsKeyPressed(K_Space)) {

        float bdx = dx / dist;
        float bdy = dy / dist;

        float bx = px + bdx * 36.0f;
        float by = py + bdy * 36.0f;


        static int numBullets = 0;
        char buffer[256];
        snprintf(buffer, 256, "bullet%d", ++numBullets);

        static H3Handle pew = NULL;
        if (!pew)
            pew = H3_Sound_Load("assets/exp.flac");

        H3Handle bullet = H3_Object_Create(props->scene, buffer, NULL);
        H3_Object_EnablePhysics(bullet, H3_CIRCLE_COLLIDER(CDT_Dynamic, 5.0f, false));
        H3_Object_Translate(bullet, bx, by);
        H3_Object_Rotate(bullet, angle * H3_RAD2DEG + 90);
        H3_Object_AddComponent(bullet, SPRITECOMPONENT_CREATE("assets/bullet.png", A_Center | A_Middle));
        H3_Object_AddComponent(bullet, BULLET_CREATE(0, 0));
        H3_Object_AddComponent(bullet, AUDIOSOURCECOMPONENT_CREATE(pew));
        H3_Object_SetVelocity(bullet, bdx * 1200.0f, bdy * 1200.0f);
        AudioSourceComponent_Play(bullet, 0.4f, false);


    }
    static int ti = 0;
    ti++;
        
            float p1x, p1y;
            float p2x, p2y;
            H3_Transform_GetPosition(H3_Object_GetTransform(object), &p1x, &p1y); //Ship's Position
            H3_Transform_GetPosition(H3_Object_GetTransform(props->object2), &p2x, &p2y); //Ship's Position
            //printf("cc %f     %f", p1x, p2x);

            float ndx = p1x - p2x;
            float ndy = p1y - p2y;

            float nbx = ndx / 10;
            float nby = 0;
            H3_Object_SetVelocity(props->object2, nbx, nby);
            if (ti >= 800 && ndx <= 1200) {
                float dist2 = sqrtf(ndx * ndx + ndy * ndy);
                float angle2 = atan2((ndy), (ndx));
                float nbdx = ndx / dist2;
                float nbdy = ndy / dist2;

                float nbx = p2x + nbdx * 36.0f;
                float nby = p2y + nbdy * 36.0f;


                static int numBullets = 0;
                char buffer[256];
                snprintf(buffer, 256, "bullet%d", ++numBullets);

                static H3Handle pew = NULL;
                if (!pew)
                    pew = H3_Sound_Load("assets/exp.flac");

                H3Handle bullet = H3_Object_Create(props->scene, buffer, NULL);
                H3_Object_EnablePhysics(bullet, H3_CIRCLE_COLLIDER(CDT_Dynamic, 5.0f, false));
                H3_Object_Translate(bullet, nbx, nby);
                H3_Object_Rotate(bullet, angle2 * H3_RAD2DEG + 90);
                H3_Object_AddComponent(bullet, SPRITECOMPONENT_CREATE("assets/bullet.png", A_Center | A_Middle));
                H3_Object_AddComponent(bullet, BULLET_CREATE(0, 0));
                H3_Object_AddComponent(bullet, AUDIOSOURCECOMPONENT_CREATE(pew));
                H3_Object_SetVelocity(bullet, nbdx * 1200.0f, nbdy * 1200.0f);
                AudioSourceComponent_Play(bullet, 0.4f, false);


                ti = 0;
            }
        
}

void TANK_ColliderON(H3Handle object, SH3Collision collide)
{
    tank_Properties* props = (tank_Properties*)H3_Object_GetComponent(object, TANK_TYPEID)->properties;
    if (collide.other == NULL)
    {
        props->IsGrounded = true;
    }
}

void TANK_ColliderLeave(H3Handle object, H3Handle other)
{
    tank_Properties* props = (tank_Properties*)H3_Object_GetComponent(object, TANK_TYPEID)->properties;
    if (other == NULL)
    {
        props->IsGrounded = false;
    }
}
void TANK_Terminate(void* properties)
{
    free(properties);
}

void* TANK_CreateProperties(H3Handle scene, H3Handle tank)
{
    tank_Properties* properties = malloc(sizeof(tank_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->object2 = tank;
    properties->scene = scene;

    return properties;
}
