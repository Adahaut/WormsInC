#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <components/movement.h>
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
} movement_Properties;

void movement_Init(void* properties) {

    //movement_Properties* props = (movement_Properties*)properties;
    //H3Handle tankR = H3_Object_Create(props->scene, "tankR", NULL);
    //H3_Object_AddComponent(tankR, SPRITECOMPONENT_CREATE("assets/tankR.png", A_Center | A_Middle));
    //H3_Object_EnablePhysics(tankR, H3_BOX_COLLIDER(CDT_Dynamic, 50, 32, A_Center | A_Middle, 0x22));

    //H3Handle tankL = H3_Object_Create(props->scene, "tankL", NULL);
    //H3_Object_AddComponent(tankL, SPRITECOMPONENT_CREATE("assets/tankL.png", A_Center | A_Middle));
    //H3_Object_EnablePhysics(tankL, H3_BOX_COLLIDER(CDT_Dynamic, 50, 32, A_Center | A_Middle, 0x22));

    //props->tankR = tankR;
    //props->tankL = tankL;
}


void movement_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    movement_Properties* props = (movement_Properties*)properties;

    int mx;
    int my;
    float px;
    float py;
    static int _time = 0;

    H3_Input_GetMousePos(h3, &mx, &my); //Mouse's Position
    if (props->player1)
        H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py); //Ship's Position
    if (!props->player1)
        H3_Transform_GetPosition(H3_Object_GetTransform(props->object2), &px, &py); //Ship's Position

   
    /*printf("Sprite :%f , %f\n", px, py);*/
    float dx = mx - px;
    float dy = my - py;
    
    float dist = sqrtf(dx * dx + dy * dy); //Determinate the distance between Ship and Mouse
    float  angle = atan2((dy), (dx)); //Determinate the angle using Mouse's Pos and Ship's Pos

    //H3_Object_SetRotation(object, angle * H3_RAD2DEG + 180); //Do the rotation of the Ship

    if (H3_Input_IsKeyDown(K_Right)) {
        if (H3_Input_IsKeyPressed(K_Up) && props->IsGrounded) {
            /// if (_time == 0) {
            float pvx = 0;
            float pvy = -500.0f;
            //H3_Object_GetVelocity(object, &pvx, &pvy);
            //dx /= dist;
            //dy /= dist;
            if (props->player1)
                H3_Object_SetVelocity(object, pvx, pvy);
            if (!props->player1)
                H3_Object_SetVelocity(props->object2, pvx, pvy);

            

            //H3_Object_SetVelocity(object, dx, dy);
            //_time = 300;
     //   }
        }
        float pvx = 100.0f;
        float pvy;
        float bin;
        if (props->player1) {
            H3_Object_GetVelocity(object, &bin, &pvy);
                H3_Object_SetVelocity(object, pvx, pvy);
        }
        else if (!props->player1) {
            H3_Object_GetVelocity(props->object2, &bin, &pvy);
            H3_Object_SetVelocity(props->object2, pvx, pvy);
        }

        

        //H3_Object_SetVelocity(object, dx, dy);
    } else if (H3_Input_IsKeyDown(K_Left)) {
        if (H3_Input_IsKeyPressed(K_Up) && props->IsGrounded) {
            /// if (_time == 0) {
            float pvx = 0;
            float pvy = -500.0f;
            //H3_Object_GetVelocity(object, &pvx, &pvy);
            //dx /= dist;
            //dy /= dist;
           if (props->player1)
                H3_Object_SetVelocity(object, pvx, pvy);
            if (!props->player1)
                H3_Object_SetVelocity(props->object2, pvx, pvy);

        }
        float pvx = -100.0f;
        float pvy;
        float bin;
        if (props->player1) {
            H3_Object_GetVelocity(object, &bin, &pvy);
            //dx /= dist;
            //dy /= dist;
            H3_Object_SetVelocity(object, pvx, pvy);
        }else if (!props->player1) {
            H3_Object_GetVelocity(props->object2, &bin, &pvy);
            //dx /= dist;
        //    //dy /= dist;
            H3_Object_SetVelocity(props->object2, pvx, pvy);
        }

        //H3_Object_SetVelocity(object, dx, dy);
    } else if (H3_Input_IsKeyPressed(K_Up) && props->IsGrounded) {
       /// if (_time == 0) {
            float pvx = 0;
            float pvy = -500.0f;
            //H3_Object_GetVelocity(object, &pvx, &pvy);
            //dx /= dist;
            //dy /= dist;
            if (props->player1)
                H3_Object_SetVelocity(object, pvx, pvy);
            if (!props->player1)
                H3_Object_SetVelocity(props->object2, pvx, pvy);

            //

            //H3_Object_SetVelocity(object, dx, dy);
            //_time = 300;
     //   }
    }
    else 
    {
        float pvx;
        float pvy;
        if (props->player1) {
            H3_Object_GetVelocity(object, &pvx, &pvy);
            pvx *= 0.99f;
            pvy *= 1;
            //if (_time > 0){ _time -= 1; }
            H3_Object_SetVelocity(object, pvx, pvy);
        }else if (!props->player1) {
            H3_Object_GetVelocity(props->object2, &pvx, &pvy);
            pvx *= 0.99f;
            pvy *= 1;
            //if (_time > 0){ _time -= 1; }
        //    H3_Object_SetVelocity(props->object2, pvx, pvy);
        }
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
            props->player1 = !props->player1;

        
    }
    
}

void movement_ColliderON(H3Handle object, SH3Collision collide)
{
    movement_Properties* props = (movement_Properties*)H3_Object_GetComponent(object, MOVEMENT_TYPEID)->properties;
    if (collide.other == NULL)
    {
        props->IsGrounded = true;
    }
}

void movement_ColliderLeave(H3Handle object, H3Handle other)
{
    movement_Properties* props = (movement_Properties*)H3_Object_GetComponent(object, MOVEMENT_TYPEID)->properties;
    if (other == NULL)
    {
        props->IsGrounded = false;
    }
}

void movement_Terminate(void* properties)
{
    free(properties);
}

void* movement_CreateProperties(H3Handle scene, H3Handle object)
{
    movement_Properties* properties = malloc(sizeof(movement_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->scene = scene;
    properties->object2 = object;

    return properties;
}
