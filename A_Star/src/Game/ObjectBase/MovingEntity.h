#pragma once

#include "BaseGameEntity.h"
#include <d3d9.h>
#include <map>
#include <vector>
#include <algorithm>

#include "C2DMatrinx.hpp"
#include "SteeringBehaviors.h"



class MovingEntity :public BaseGameEntity
{
	std::string m_sFilename;
	std::string m_sResname;
	std::map<const std::string, RECT> m_HitRect;

	static std::vector<MovingEntity*>m_MovingEntities;

protected:

	Vector2D m_vVelocity;

	Vector2D m_vHeading;

	Vector2D m_vSide;

	double m_dMass;

	double m_dMaxSpeed;

	double m_dMaxForce;

	double m_dAngle;

	double m_dMaxTurnRate;

	int m_iAlpha = 255;

	bool m_bVisible = true;

	bool m_bHit = false;

	struct
	{
		int SrcX;
		int SrcY;
		int SizeX;
		int SizeY;
	}m_Rect;

	struct Circle
	{
		Vector2D Center;
		double Radius;
	};

	SteeringBehavior* m_pSteering;

private:
	std::map<const std::string, Circle> m_CollisionCircles;

public:
	MovingEntity(const std::string& fileName,const std::string& resName,int SrcX,int SrcY,int SizeX,int SizeY, Vector2D position, Vector2D velocity, double dZ, double max_speed, double mass, Vector2D scale, double max_force,int Type);

	virtual ~MovingEntity()
	{
		delete m_pSteering;
		m_MovingEntities.erase(remove(m_MovingEntities.begin(), m_MovingEntities.end(), this),m_MovingEntities.end());

	}

	Vector2D Velocity()const{ return m_vVelocity; }
	void SetVelocity(const Vector2D& NewVel){ m_vVelocity = NewVel; }

	double Mass()const{ return m_dMass; }

	double MaxSpeed()const{ return m_dMaxSpeed; }
	void SetMaxSpeed(double mf){ m_dMaxForce = mf; }

	double MaxForce()const { return m_dMaxForce; }
	void SetMaxForce(double mf) { m_dMaxForce = mf; }

	bool IsSpeedMaxedOut()const{ return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq(); }
	double Speed()const{ return m_vVelocity.Length(); }
	double SpeedSq()const{ return m_vVelocity.LengthSq(); }

	Vector2D  Heading()const { return m_vHeading; }
	Vector2D  Side()const { return m_vSide; }

	void      SetHeading(Vector2D new_heading);
	bool      RotateHeadingToFacePosition(Vector2D target);

	double     MaxTurnRate()const { return m_dMaxTurnRate; }
	void      SetMaxTurnRate(double val) { m_dMaxTurnRate = val; }

	void Add_HitRect(const std::string rectName, int bottom, int top, int right, int left);
	RECT* Get_Rect(const std::string& rectName);

	void Add_Collisioncircle(const std::string circleName, Vector2D Center, double Radius);
	Circle* Get_CollisionCircle(const std::string CircleName);

	SteeringBehavior*const  Steering()const { return m_pSteering; }

	static std::vector<MovingEntity*>* Get_Entities() { return &m_MovingEntities; }

	bool IsHit() { return m_bHit; }
	void Set_Hit(bool ToF) { m_bHit = ToF; }

	void Move();

#ifdef _DEBUG
	void Render_RectBox(const std::string& RectName,D3DCOLOR color);
#endif
	void Render();
};

inline bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
	Vector2D toTarget = Vec2DNormalize(target - m_vPosition);

	double angle = acos(m_vHeading.Dot(toTarget));

	if (angle < 0.00001) return true;

	if (angle > m_dMaxTurnRate) angle = m_dMaxTurnRate;

	C2DMatrix RotationMatrix;

	RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));
	RotationMatrix.TransformVector2Ds(m_vHeading);
	RotationMatrix.TransformVector2Ds(m_vVelocity);

	m_vSide = m_vHeading.Perp();

	return false;
}


inline void MovingEntity::SetHeading(Vector2D new_heading)
{
	assert((new_heading.LengthSq() - 1.0) < 0.00001);

	m_vHeading = new_heading;


	m_vSide = m_vHeading.Perp();
}
