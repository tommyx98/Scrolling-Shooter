#include "SDLManager.h"
#include "Texture.h"
#include "./ComponentBasedES/AllComponents.h"
#include "Collision.h"
#include "Vector2D.h"
#include "Background.h"
#include "AssetManager.h"
#include "EnemyFactory.h"
#include "SDL_mixer.h"

SDL_Renderer* SDLManager::renderer = nullptr;
SDL_Event SDLManager::event;
SDL_Window* SDLManager::window;


EntityManager entityManager;
Background *theBackground;
AssetManager* SDLManager::assets = new AssetManager(&entityManager);
EnemyFactory *factory = new EnemyFactory();
Mix_Music *backgroundMusic;

auto& player(entityManager.AddEntity());


auto& highScoreText(entityManager.AddEntity());
auto& healthText(entityManager.AddEntity());

SDLManager::SDLManager() {

}

SDLManager::~SDLManager() {}

void SDLManager::CreateWindow() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
        gameIsRunning = false;
    }

    else{
        std::cout << "SDL video system initialized\n";
        window = SDL_CreateWindow("Scrolling Shooter",20, 20, 640,480,SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        gameIsRunning = true;
    }


    if(TTF_Init() < 0){
        std::cout<<"Error: "<<TTF_GetError()<<std::endl;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cout<<"Error: "<<Mix_GetError()<<std::endl;
    }

    backgroundMusic = Mix_LoadMUS("../music/background_music.mp3");
    Mix_PlayMusic(backgroundMusic, -1);

    assets->AddTexture("player", "../images/player_hover.png");
    assets->AddTexture("player_invicible", "../images/player_hover_invicible.png");
    assets->AddTexture("enemy", "../images/enemy_hover.png");
    assets->AddTexture("enemy2", "../images/enemy2_hover.png");
    assets->AddTexture("bullet", "../images/bullet.png");
    assets->AddTexture("bullet_enemy", "../images/bullet_enemy.png");
    assets->AddTexture("bullet_enemy2", "../images/bullet_enemy2.png");

    theBackground = new Background();
    theBackground->LoadBackground("../images/background.txt", 40, 30);


    player.AddComponentToEntity<TransformComponent>(300.0f, 420.0f, 64, 64, 0.5f);
    player.AddComponentToEntity<SpriteComponent>("player", 2, 1000);
    player.AddComponentToEntity<InputManagerComponent>();
    player.AddComponentToEntity<ColliderComponent>("player");
    player.AddGroupToEntity(PLAYER);
    player.AddComponentToEntity<HealthComponent>(3);
    player.AddComponentToEntity<ScoreTrackerComponent>();
    player.AddComponentToEntity<InvicibilityComponent>();

    const char *scoreText = "SCORE: 0";

    std::string baseHealthText = "HEALTH: ";
    int health = player.GetComponentFromEntity<HealthComponent>().GetHealth();
    std::string resultHealth = baseHealthText + std::to_string(health);
    const char *theHealthText = const_cast<char*>(resultHealth.c_str());


    highScoreText.AddComponentToEntity<UIComponent>(30,20);
    highScoreText.GetComponentFromEntity<UIComponent>().InitializeText(scoreText);
    highScoreText.AddGroupToEntity(SCORETEXT);


    healthText.AddComponentToEntity<UIComponent>(460, 430);
    healthText.GetComponentFromEntity<UIComponent>().InitializeText(theHealthText);
    healthText.AddGroupToEntity(HEALTHTEXT);
}

void SDLManager::EventHandler() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            gameIsRunning = false;
            break;

        default:
            break;
    }
}

auto &background(entityManager.GetGroup(SDLManager::BACKGROUND));
auto &colliders(entityManager.GetGroup(SDLManager::COLLIDER));
auto &players(entityManager.GetGroup(SDLManager::PLAYER));
auto &enemies(entityManager.GetGroup(SDLManager::ENEMY));
auto &bullets(entityManager.GetGroup(SDLManager::BULLET));
auto &enemyBullets(entityManager.GetGroup(SDLManager::ENEMYBULLET));

void SDLManager::Draw() {
    for(auto &b : background){
        b->DrawComponentsInEntity();
    }

    for(auto &c : colliders){
        c->DrawComponentsInEntity();
    }

    for(auto &p : players){
        p->DrawComponentsInEntity();
    }

    for(auto &e : enemies){
        e->DrawComponentsInEntity();
    }

    for(auto &bu : bullets){
        bu->DrawComponentsInEntity();
    }

    for(auto &eBU : enemyBullets){
        eBU->DrawComponentsInEntity();
    }

    highScoreText.DrawComponentsInEntity();
    healthText.DrawComponentsInEntity();
}

void SDLManager::Render() {
    if(!players.empty()) {
        SDL_RenderClear(renderer);
        Draw();
        SDL_RenderPresent(renderer);
    }
}

void SDLManager::Cleaner() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(backgroundMusic);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void SDLManager::Update() {
    if(players.empty()){
        // if player has died and not already on game over screen go to game over screen
        if(!onGameOverScreen){
            GameOver();
        }
        entityManager.RefreshEntities();
        entityManager.UpdateAllEntities();
    }

    else {
        onGameOverScreen = false;
        SDL_Rect playerCollider = entityManager.GetGroup(
                SDLManager::PLAYER)[0]->GetComponentFromEntity<ColliderComponent>().collider;
        Vector2D playerPosition = entityManager.GetGroup(
                SDLManager::PLAYER)[0]->GetComponentFromEntity<TransformComponent>().position;

        while (enemies.size() < 5) {
            factory->CreateEnemy();
        }

        entityManager.RefreshEntities();
        entityManager.UpdateAllEntities();

        for (auto &c: colliders) {
            SDL_Rect cCollider = c->GetComponentFromEntity<ColliderComponent>().collider;
            if (Collision::AABBCollisionCheck(cCollider, playerCollider)) {
                entityManager.GetGroup(
                        SDLManager::PLAYER)[0]->GetComponentFromEntity<TransformComponent>().position = playerPosition;
            }
        }
    }
}

bool SDLManager::ISGameRunning() {
    return gameIsRunning;
}

void SDLManager::GameOver() {
    SDL_Texture *t = Texture::TextureLoader("../images/game_over.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, t, NULL, NULL);
    SDL_RenderPresent(renderer);

    for(auto &e : enemies){
        e->DestroyEntity();
    }
    for(auto &eBU : enemyBullets){
        eBU->DestroyEntity();
    }
    for(auto &bu : bullets){
        bu->DestroyEntity();
    }

    auto& input(entityManager.AddEntity());
    input.AddComponentToEntity<InputManagerComponent>();
    onGameOverScreen = true;
}

void SDLManager::ResetPlayingStatus() {
    AddPlayer();

    std::string baseHealthText = "HEALTH: ";
    int health = players[0]->GetComponentFromEntity<HealthComponent>().GetHealth();
    std::string resultHealth = baseHealthText + std::to_string(health);
    const char *theHealthText = const_cast<char*>(resultHealth.c_str());
    healthText.GetComponentFromEntity<UIComponent>().InitializeText(theHealthText);
    highScoreText.GetComponentFromEntity<UIComponent>().InitializeText("SCORE: 0");

}

void SDLManager::AddPlayer() {
    auto& thePlayer(entityManager.AddEntity());
    thePlayer.AddComponentToEntity<TransformComponent>(300.0f, 420.0f, 64, 64, 0.5f);
    thePlayer.AddComponentToEntity<SpriteComponent>("player", 2, 1000);
    thePlayer.AddComponentToEntity<InputManagerComponent>();
    thePlayer.AddComponentToEntity<ColliderComponent>("player");
    thePlayer.AddGroupToEntity(PLAYER);
    thePlayer.AddComponentToEntity<HealthComponent>(3);
    thePlayer.AddComponentToEntity<ScoreTrackerComponent>();
    thePlayer.AddComponentToEntity<InvicibilityComponent>();
}