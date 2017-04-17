#pragma once

#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "LinearMath.lib")

//#include "../bullet3-2.86.1/src/btBulletCollisionCommon.h"
//#include "../bullet3-2.86.1/src/btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include <vector>

using std::vector;

class Physics{
	public:
		Physics();
		~Physics();
		
		void init();
		void UpdatePhysics(float msec);

		/*static*/ btRigidBody* addSphere(float radius, float x, float y, float z, float mass);

		btRigidBody* addBox(float x, float y, float z, float height, float width, float depth, float mass);
		
		inline vector<btRigidBody*>& getRigidBodies(){
			return rigidBodies;
		}

		void AddPhysicalObjects();

	private:
		btDynamicsWorld *world;
		btDispatcher *dispatcher;
		btBroadphaseInterface *broadphase;
		btConstraintSolver *solver;
		btCollisionConfiguration *collisionConfig;

		vector<btRigidBody*> rigidBodies;

};
