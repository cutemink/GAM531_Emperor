#include "Core.hpp"
#include "Node.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Actor.hpp"
#include <iostream>
#include "WindowController.hpp"
#include "UnifiedMaterial.hpp"
#include <chrono>

using namespace Emperor;

Core::Core() : gfxEngine(0) {}

struct SwaySystem
   {
   iNode* trans;
   iNode* rot;
   float transPhaseShift;
   float rotPhaseShift;
   float phaseScale;
   float transDist;
   float rotRad;
   float lastRot;
   std::chrono::time_point<std::chrono::high_resolution_clock> start;
   Vector<float,3> transAxis;
   Vector<float,3> rotAxis;

   SwaySystem(){}

   SwaySystem(iSceneController* scene,
      float transPhaseShift,
      float rotPhaseShift,
      float phaseScale,
      float transDist,
      float rotRad,
      Vector<float,3> transAxis = Vector3(1,0,0),
      Vector<float,3> rotAxis = Vector3(0,0,1),
      iNode* parent = nullptr) :
         transPhaseShift(transPhaseShift), rotPhaseShift(rotPhaseShift), phaseScale(phaseScale),
         transDist(transDist), rotRad(rotRad), transAxis(transAxis), rotAxis(rotAxis),
         lastRot(0.0f)
      {
      trans = scene->createNode();
      rot = scene->createNode();
      rot->attachTo(trans);
      if (parent)
         {
         trans->attachTo(parent);
         }

      start = std::chrono::high_resolution_clock::now();
      }

   void update()
      {
      auto now = std::chrono::high_resolution_clock::now();
      auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
      auto deltaS = float(delta.count()) / 1000000.0f;
      float transAlpha = sinf(phaseScale * (transPhaseShift + deltaS));
      trans->setPosition(transAxis * transDist * transAlpha);

      float rotAlpha = sinf(phaseScale * (rotPhaseShift + deltaS));
      float newRot = rotAlpha * rotRad;
      rot->rotate(rotAxis, newRot - lastRot);
      lastRot = newRot;
      }

   iNode* root()
      {
      return trans;
      }

   iNode* tip()
      {
      return rot;
      }
   };

struct Squadron
   {
   float height;
   float orbitDuration;
   float forwardSpacing;
   float sideSpacing;
   int numShips;
   iNode* root;
   iNode* rotRoot;
   std::chrono::time_point<std::chrono::high_resolution_clock> last;

   struct Ship
      {
      SwaySystem sway;
      Ship()
         {
         }
      Ship(iSceneController* scene, iNode* parent, bool isBomber)
         {
         float phase = 3.14159f * float(rand()) / float(RAND_MAX);
         float scale = 1.25f * float(rand()) / float(RAND_MAX);
         float dist = 0.5f + 0.25f * float(rand()) / float(RAND_MAX);
         float rot = (0.075f + 0.025f * float(rand()) / float(RAND_MAX)) * 3.14159f;
         sway = SwaySystem(scene, phase + 0.25f * 3.14159f, phase, scale, dist, rot, Vector3(1,0,0), Vector3(0,0,1), parent);

         iActor* actor = scene->createActor();
         if (isBomber)
            {
            actor->setMesh("bomber.obj");
            actor->setMaterial("BomberMaterial");
            }
         else
            {
            actor->setMesh("fighter.obj");
            actor->setMaterial("FighterMaterial");
            }
         actor->attachTo(sway.tip());
         actor->activate();
         }

      void update()
         {
         sway.update();
         }
      };
   std::vector<Ship> ships;
   SwaySystem squadronSway;

   Squadron(){}
   Squadron(iSceneController* scene, float baseHeight)
      {
      numShips = 2 + rand() % 7;
      height = baseHeight + rand() % 200;
      orbitDuration = 64.0f + 32.0f * float(rand()) / float(RAND_MAX);
      forwardSpacing = 1.25f + 0.75f * float(rand()) / float(RAND_MAX);
      sideSpacing = 1.0f + 0.5f * float(rand()) / float(RAND_MAX);

      // Create requisite nodes
      root = scene->createNode();
      root->rotate(Vector3(1,0,0), -0.3f * float(rand()) / float(RAND_MAX) * 3.14159f);
      rotRoot = scene->createNode();
      rotRoot->attachTo(root);
      rotRoot->rotate(Vector3(0,1,0), 2.0f * 3.14159f * float(rand()) / float(RAND_MAX));
      iNode* heightNode = scene->createNode();
      heightNode->attachTo(rotRoot);
      heightNode->setPosition(Vector3(0, 0, height));
      heightNode->rotate(Vector3(0,-1,0), 0.5f * 3.14159f);
      heightNode->rotate(Vector3(1,0,0), 0.5f * 3.14159f);

      // Sway for squadron
      float phase = 3.14159f * float(rand()) / float(RAND_MAX);
      float scale = 1.0f + 0.5f * float(rand()) / float(RAND_MAX);
      float dist = 75.0f + 25.0f * float(rand()) / float(RAND_MAX);
      float rot = (0.1f + 0.05f * float(rand()) / float(RAND_MAX)) * 3.14159f;
      squadronSway = SwaySystem(scene, phase + 0.25f * 3.14159f, phase, scale, dist, rot, Vector3(0,1,0), Vector3(1,0,0), heightNode);
      squadronSway.tip()->scale(Vector3(10,10,10));

      // Create squad
      float squadLength = forwardSpacing * ((numShips + 1) / 2);
      iNode* leader = scene->createNode();
      leader->attachTo(squadronSway.tip());
      leader->setPosition(Vector3(0,0,squadLength * 0.5f));
      leader->rotate(Vector3(0,1,0), 3.14159f);
      ships.push_back(Ship(scene, leader, true));

      int shipsToCreate = numShips;
      float fSpacing = forwardSpacing;
      float sSpacing = sideSpacing;
      do {
         for (int i = 0; i < 2 && shipsToCreate > 0; i++, shipsToCreate--)
            {
            iNode* node = scene->createNode();
            node->attachTo(leader);
            node->setPosition(Vector3(sSpacing, 0, fSpacing));
            sSpacing *= -1;
            ships.push_back(Ship(scene, node, false));
            }

         fSpacing += forwardSpacing;
         sSpacing += sideSpacing;
         } while (shipsToCreate > 0);

      last = std::chrono::high_resolution_clock::now();
      }

   void update()
      {
      squadronSway.update();
      for (auto i = ships.begin(), end = ships.end(); i != end; ++i)
         {
         i->update();
         }

      auto now = std::chrono::high_resolution_clock::now();
      auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - last);
      auto deltaS = float(delta.count()) / 1000000.0f;
      last = now;

      rotRoot->rotate(Vector3(0,-1,0), deltaS / orbitDuration * 3.14159f * 2.0f);
      }
   };

static SwaySystem frigSway;
std::vector<Squadron> squadrons;
Squadron::Ship testShip;

Core::~Core()
   {
   if(gfxEngine)
      releaseEngine(gfxEngine);
   gfxEngine = 0;
   }

void Core::init()
   {
   srand(1);
   Emperor::RenderSystem renderSystem = RS_DX11;
   gfxEngine = createEngine(renderSystem);
   
   if(!settings.loadFromFile(EMP_SETTINGS_FILE))
      LOG("Settings file failed to load. Running on defaults...");

   //We need a window to draw on
   w1 = WindowController::createWindow();
   w1->setName("testing window");
   w1->setSize(settings.resolution);
   w1->init();

   //Activate the engine on the window
   gfxEngine->activateDevice(w1);
   gfxEngine->setFullScreen(settings.fullscreen);
   gfxEngine->initialize();

   auto resource = gfxEngine->getResourceController();
   auto scene = gfxEngine->getSceneController();

   // Sun
   auto sunLight = scene->createLight();
   sunLight->setDiffuse(Color(1.0f,1.0f,1.0f,1.0f));
   auto earthNode = scene->createNode();
   earthNode->scale(Vector3(100, 100, 100));
   auto sunNode = scene->createNode();
   sunNode->attachTo(earthNode);
   sunNode->setPosition(Vector3(-1000, 1000, -1000));
   auto testMatrix = sunNode->getLocalTransform();
   auto testVector = Vector4(0, 0, 0, 1);
   testVector = testVector * testMatrix;
   testVector = Vector4(1, 0, 0, 1);
   testMatrix = rotationMatrix(Vector3(0, 1, 0), 0.5f * 3.14159f);
   setPosition(testMatrix, Vector3(10, 20, 30));
   testVector = testVector * testMatrix;
   sunLight->attachTo(sunNode);
   sunLight->activate();

   // Camera
   n1 = scene->createNode();
   n2 = scene->createNode();
   n2->attachTo(n1);
   n2->translate(Vector3(-1000,2100,-3000));
   n2->rotate(Vector3(0,1,0), 3.14159f);
   auto camera = scene->createCamera();
   camera->setFarClipping(800000.0f);

   RasterizerStateDescription rs;
   camera->setRasterState(rs);
   camera->attachTo(n2);
   camera->activate();

   // Earth
   UnifiedMaterial earthMat(
      "EarthMaterial",
      resource,
      "earth_simple_diffuse.jpg",
      "earth_night.png",
      "earth_spec.png",
      0.15f,
      10.0f);

   auto earthActor = scene->createActor();
   earthActor->setMaterial("EarthMaterial");
   earthActor->setMesh("earth.obj");
   earthActor->attachTo(earthNode);
   earthActor->activate();

   // Starfield
   UnifiedMaterial sfMat(
      "StarfieldMaterial",
      resource,
      "starmap.png",
      "starmap.png");
   auto sfActor = scene->createActor();
   sfActor->setMaterial("StarfieldMaterial");
   sfActor->setMesh("starfield.obj");
   sfActor->attachTo(earthNode);
   sfActor->activate();

   // Frigate
   UnifiedMaterial frigMat(
      "FrigMaterial",
      resource,
      "frigate_diffuse.jpg",
      "frigate_ambient.jpg",
      "frigate_specular.jpg",
      1.0f,
      128.0f);
   fn1 = scene->createNode();
   fn1->rotate(Vector3(0,1,0), -0.00027f * 3.14159f);
   fn2 = scene->createNode();
   fn2->attachTo(fn1);
   fn2->rotate(Vector3(0,0,1), 0.3f * 3.14159f);
   fn2->rotate(Vector3(0,1,0), -0.45f * 3.14159f);
   fn2->setPosition(Vector3(-1000,2100,-2998));
   frigSway = SwaySystem(scene, 3.14159f * 0.25f, 0.0f, 1.0f, 0.5f, 3.14159f * 0.075f, Vector3(1,0,0), Vector3(0,0,1), fn2);

   auto frigActor = scene->createActor();
   frigActor->setMaterial("FrigMaterial");
   frigActor->setMesh("frigate.obj");
   frigActor->attachTo(frigSway.tip());
   frigActor->activate();

   // Create squadrons
   UnifiedMaterial fighterMaterial(
      "FighterMaterial",
      resource,
      "fighter_diffuse.jpg",
      "fighter_ambient.jpg",
      "fighter_specular.jpg",
      1.0f,
      128.0f);
   UnifiedMaterial bomberMaterial(
      "BomberMaterial",
      resource,
      "bomber_diffuse.jpg",
      "bomber_ambient.jpg",
      "bomber_specular.jpg",
      1.0f,
      128.0f);
   //testShip = Squadron::Ship(scene, fn2, false);

   int numSquadrons = 80;
   for (int i = 0; i < numSquadrons; ++i)
      {
      squadrons.push_back(Squadron(scene, 3400));
      }

   for (int i = 0; i < numSquadrons; ++i)
      {
      squadrons.push_back(Squadron(scene, 3700));
      }
   }

float lastAngleDiff = 0.0f;
bool frigCatchingUp = false;

void Core::run()
   {
   bool active = true;
   auto start = std::chrono::high_resolution_clock::now();
   auto last = start;
   while(active)
      {
      auto msg = WindowController::retrieveWindowMessages();
      auto end = msg.end();
      for(auto i = msg.begin(); i < end; ++i)
         {
         switch((*i).msg)
            {
         case EMP_WINDOW_CLOSE:
            active = false;
            break;
         case EMP_WINDOW_MBUTTONUP:
            gfxEngine->setFullScreen(true);
            break;
         case EMP_WINDOW_RBUTTONUP:
            gfxEngine->setFullScreen(false);
            break;
         case EMP_WINDOW_MOVE:
            std::cout << "Moved!" << std::endl;
            break;
            }
         }
      auto now = std::chrono::high_resolution_clock::now();
      auto msDiff = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
      float deltaS = float(msDiff) / 1000000.0f;
      last = now;

      // Current angle diff b/w frig and camera
      n2->_recalcAbsTransform();
      fn2->_recalcAbsTransform();
      auto camPos = getPosition(n2->_getAbsTransform());
      auto frigPos = getPosition(fn2->_getAbsTransform());
      float angleDiff = camPos.radiansBetween(frigPos);

      float camPerSec = -0.02f;
      float frigPerSec = camPerSec * 0.999f;
      if (lastAngleDiff != 0.0f)
         {
         // growing apart?
         if (angleDiff > lastAngleDiff && angleDiff > 3.14159f * 0.0005f)
            {
            frigCatchingUp = !frigCatchingUp;
            //std::cout << "switch!" << std::endl;
            }
         }
      //std::cout << "now: " << angleDiff << ", last: " << lastAngleDiff << std::endl;
      lastAngleDiff = angleDiff;

      if (frigCatchingUp) frigPerSec *= 1.003f;

      n1->rotate(Vector3(0,1,0), camPerSec * 3.14159f * deltaS);
      fn1->rotate(Vector3(0,1,0), frigPerSec * 3.14159f * deltaS);
      //testShip.update();
      for (auto i = squadrons.begin(), end = squadrons.end(); i != end; ++i)
         {
         i->update();
         }
      frigSway.update();
      gfxEngine->render();
      }
   if(!settings.saveToFile(EMP_SETTINGS_FILE))
      LOG("Settings file failed to save. Changes have been lost");
   }

void Core::halt()
   {

   }
