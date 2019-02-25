#include <iostream>
#include <memory>
#include <map>

using namespace std;
class SpaceShip;
class SpaceStation;
class Asteroid;
class GameObject {
public:
	virtual void collide(GameObject& otherObject) = 0;
	virtual void hitSpaceShip(GameObject &otherObject) = 0;
	virtual void hitSpaceStation(GameObject &otherObject) = 0;
	virtual void hitAsteroid(GameObject &otherObject) = 0;
};
class SpaceShip: public GameObject {
public:

	typedef void (SpaceShip::*HitFunctionPtr) (GameObject&);
	using HitMap = std::map<string, HitFunctionPtr>;
	static HitFunctionPtr lookup(const GameObject& whatWeHit) {
		static std::shared_ptr<HitMap> collisionMap{initializeCollisionMap()};
		cout<< typeid(whatWeHit).name()<<endl;
		auto mapEntry = collisionMap->find(typeid(whatWeHit).name());
		if(mapEntry == collisionMap->end())
			return nullptr;
		return mapEntry->second;
	}

	void collide(GameObject& otherObject) override {
//		otherObject.hitSpaceShip(*this);
		auto hfp = lookup(otherObject);
		if(hfp) {
			(this->*hfp)(otherObject);
		} else{
//			throw CollisionWithUnknownObject(otherObject);
			cout << "CollisionWithUnknownObject" <<endl;
		}

	}
private:
	static HitMap* initializeCollisionMap() ;

	void hitSpaceShip(GameObject &otherObject) override {
		cout << "SpaceShip : SpaceShip" << endl;
	}

	void hitSpaceStation(GameObject &otherObject) override {
		cout << "SpaceShip : SpaceStation" << endl;
	}

	void hitAsteroid(GameObject &otherObject) override {
		cout << "SpaceShip : Asteroid" << endl;
	};
};

class SpaceStation: public GameObject {
public:
	void collide(GameObject& otherObject) override {
		otherObject.hitSpaceStation(*this);
	}

private:
	void collideWithSpaceShip(SpaceShip &otherObject) override {
		cout << "SpaceStation : SpaceShip" << endl;
	}

	void collideWithSpaceStation(SpaceStation &otherObject) override {
		cout << "SpaceStation : SpaceStation" << endl;
	}

	void collideWithAsteroid(Asteroid &otherObject) override {
		cout << "SpaceStation : Asteroid" << endl;
	};
};


class Asteroid: public GameObject {
public:
	void collide(GameObject& otherObject) override {
		otherObject.hitAsteroid(*this);
	}
private:
	void collideWithSpaceShip(SpaceShip &otherObject) override {
		cout << "Asteroid : SpaceShip" << endl;
	}

	void collideWithSpaceStation(SpaceStation &otherObject) override {
		cout << "Asteroid : SpaceStation" << endl;
	}

	void collideWithAsteroid(Asteroid &otherObject) override {
		cout << "Asteroid : Asteroid" << endl;
	}
};
SpaceShip::HitMap *SpaceShip::initializeCollisionMap() {
//		auto phm = std::make_shared<HitMap>();
		auto phm = new HitMap;
		(*phm)[typeid(SpaceShip).name()] = &SpaceShip::hitSpaceShip;
		(*phm)[typeid(SpaceStation).name()] = &SpaceShip::hitSpaceStation;
		(*phm)[typeid(Asteroid).name()] = &SpaceShip::hitSpaceStation;
		return phm;
}



int main() {
	SpaceShip ss;
//	GameObject* sst =  new SpaceStation;
//	GameObject* as =  new Asteroid;
	ss.collide(ss);
//	ss->collide(*sst);
//	ss->collide(*as);
//	sst->collide(*ss);
//	sst->collide(*sst);
//	sst->collide(*as);
//	as->collide(*ss);
//	as->collide(*sst);
//	as->collide(*as);
	return 0;
}