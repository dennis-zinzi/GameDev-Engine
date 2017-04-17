#include "Physics.h"

Physics::Physics(){
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0.0f, 9.81f, 0.0f));

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(0, 0, 0));

	btStaticPlaneShape *plane = new btStaticPlaneShape(btVector3(0, 1.0f, 0.0), 0.0f);
	btMotionState *motion = new btDefaultMotionState(t);

	//If 0, then won't move (static), > 0 then dynamic
	btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion, plane);
	btRigidBody *body = new btRigidBody(info);

	world->addRigidBody(body);
	rigidBodies.push_back(body);

	addSphere(1.0f, 0.0f, 20.0f, -10.0f, 1.0f);
}


Physics::~Physics(){
	delete dispatcher;
	delete solver;
	delete broadphase;
	delete collisionConfig;
	delete world;

	for(auto body : rigidBodies){
		//delete body dynamically allocated vars
		delete body;
	}
}


void Physics::init(){

}


void Physics::UpdatePhysics(float msec){
	world->stepSimulation(msec / 1000.0f);
}


btRigidBody* Physics::addSphere(float radius, float x, float y, float z, float mass){
	//Set position and rotation
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btSphereShape *sphere = new btSphereShape(radius);
	btVector3 inertia(0.0f, 0.0f, 0.0f);
	if(mass != 0.0f){
		//Calculates inertia, and passes value into given Vector
		sphere->calculateLocalInertia(mass, inertia);
	}

	btMotionState *motion = new btDefaultMotionState(t);

	//If 0, then won't move (static), > 0 then dynamic
	btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion, sphere, inertia);
	btRigidBody *body = new btRigidBody(info);

	world->addRigidBody(body);
	rigidBodies.push_back(body);

	return body;
}


btRigidBody* Physics::addBox(float x, float y, float z, float height, float width, float depth, float mass){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btBoxShape *box = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));

	btVector3 inertia(0.0f, 0.0f, 0.0f);
	if(mass != 0.0f){
		box->calculateLocalInertia(mass, inertia);
	}

	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);
	btRigidBody *body = new btRigidBody(info);

	world->addRigidBody(body);
	rigidBodies.push_back(body);

	return body;
}