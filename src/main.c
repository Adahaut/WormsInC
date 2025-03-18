#include <h3.h>
#include <components/cameracomponent.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <stdio.h>
#include <components/maplayercomponent.h>
#include <components/movement.h>
#include <components/bullet.h>
#include <components/textcomponent.h>
#include <components/tank.h>


#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG

int main(int argc, char** argv)
{
    int jeu;
    printf("Ecrivez 1 pour jouer contre l'ordinateur, ou ecrivez 2 pour jouer avec un ami !\n");
    scanf_s("%d", &jeu);

    H3Handle h3 = H3_Init((SH3InitParams) {
            .width = 1920,
            .height = 1024,
            .fullscreen = false,
            .windowTitle = "Worms"
    });
    
    

    bool running = true;
    int score = 0;
    int life = 3;

    H3Handle scn = H3_Scene_Create(h3, true);
    H3_Scene_SetGravity(scn, 0, 9.91);


    H3Handle map = H3_Map_Load("assets/map.tmx");
    H3_Map_RegisterObjectLayerForPhysicsInScene(scn, map, "collider");

    H3Handle maplayer = H3_Object_Create(scn, "map", NULL);
    H3_Object_AddComponent(maplayer, MAPLAYERCOMPONENT_CREATE(map, "Background2"));
    H3Handle maplayer2 = H3_Object_Create(scn, "map2", NULL);
    H3_Object_AddComponent(maplayer2, MAPLAYERCOMPONENT_CREATE(map, "Background"));

    
    H3Handle tankR = H3_Object_Create(scn, "tankR", NULL);
    H3_Object_AddComponent(tankR, SPRITECOMPONENT_CREATE("assets/tankR.png", A_Center | A_Middle));
    H3_Object_EnablePhysics(tankR, H3_BOX_COLLIDER(CDT_Dynamic, 50, 32, A_Center | A_Middle, 0x22));


    

    H3Handle tankL = H3_Object_Create(scn, "tankL", NULL);
    H3_Object_AddComponent(tankL, SPRITECOMPONENT_CREATE("assets/tankL.png", A_Center | A_Middle));
    H3_Object_EnablePhysics(tankL, H3_BOX_COLLIDER(CDT_Dynamic, 50, 32, A_Center | A_Middle, 0x22));
    if (jeu == 1) { H3_Object_AddComponent(tankR, TANK_CREATE(scn, tankL)); }
    else if (jeu == 2) { H3_Object_AddComponent(tankR, MOVEMENT_CREATE(scn, tankL, false)); }

    /*H3_Object_AddComponent(tankL, TANK_CREATE());*/
    //H3_Object_AddComponent(tankL, MOVEMENT_CREATE(scn, tankR, tankL, false));
    H3Handle font = H3_Font_Load("assets/Comfortaa-Regular.ttf");
    H3Handle scoreText = H3_Object_Create(scn, "scoreText", NULL);
    H3Handle lifeText = H3_Object_Create(scn, "lifeText", NULL);
    H3_Object_SetTranslation(lifeText, 10, 10);
    H3_Object_SetTranslation(scoreText, 1900, 10);

    SH3TextProperties textProps1 = {
    .font = font,
    .size = 30,
    .fillColor = {255,0,0,255},
    .hasOutline = false,
    .outlineColor = {0,255,0,0},
    .outlineThickness = 5,
    .anchor = A_Left | A_Top,
    .isBold = false,
    .isItalic = false,
    .isUnderlined = false,
    .isViewLocal = false
    };

    SH3TextProperties textProps2 = {
        .font = font,
        .size = 30,
        .fillColor = {255,0,0,255},
        .hasOutline = false,
        .outlineColor = {0,255,0,0},
        .outlineThickness = 5,
        .anchor = A_Right | A_Top,
        .isBold = false,
        .isItalic = false,
        .isUnderlined = false,
        .isViewLocal = false
    };
    char scoreBuffer[256];
    char lifeBuffer[256];

    H3_Object_AddComponent(scoreText, TEXTCOMPONENT_CREATE("", textProps2));
    H3_Object_AddComponent(lifeText, TEXTCOMPONENT_CREATE("", textProps1));





    typedef struct
    {
        const char* Text;
        SH3TextProperties Props;
    } TextComponent_Properties;





    H3_Object_Translate(tankR, 1850.0f, 950.0f);
    H3_Object_Translate(tankL, 70.0f, 950.0f);


    do {
        snprintf(scoreBuffer, 256, "score : %d", score);
        SH3Component* compoText = H3_Object_GetComponent(scoreText, SPRITECOMPONENT_TYPEID);
        TextComponent_Properties* textProps = (TextComponent_Properties*)(compoText->properties);
        textProps->Text = scoreBuffer;
        snprintf(lifeBuffer, 256, "life : %d", life);
        SH3Component* compoText2 = H3_Object_GetComponent(lifeText, SPRITECOMPONENT_TYPEID);
        TextComponent_Properties* textProps2 = (TextComponent_Properties*)(compoText2->properties);
        textProps2->Text = lifeBuffer;


        running = H3_DoFrame(h3, scn);
    } while (running);

    H3_Object_Destroy(&tankL, true);
    H3_Object_Destroy(&tankR, true);
    H3_Object_Destroy(&maplayer2, true);
    H3_Object_Destroy(&maplayer, true);
    H3_Scene_Destroy(&scn);
    
    H3_Terminate(&h3);


	return 0;
}

