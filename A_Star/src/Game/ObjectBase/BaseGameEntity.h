#pragma once

#include "Vector2D.hpp"


class BaseGameEntity
{
public:
	enum
	{
		default_entity_type = -1,
		type_player=1,
	};
private:
	int m_iID;

	int m_iType;

	bool m_bTag;

	static int m_iNextValidID;

	void SetID(int val);

	unsigned int m_iAlpha = 255;

protected:

	Vector2D m_vPosition;

	double m_dZ = 0.0;

	Vector2D m_vScale;

	double    m_dBoundingRadius;

	BaseGameEntity(int ID);

public:
	virtual ~BaseGameEntity(){}

	static int GetNextValidID(){ return m_iNextValidID; }

	static void ResetNextValidID(){ m_iNextValidID = 0; }

	Vector2D Pos()const{ return m_vPosition; }
	void SetPos(Vector2D new_pos){ m_vPosition = new_pos; }

	double Get_Z()const { return m_dZ; }

	double BRadius()const{ return m_dBoundingRadius; }
	void SetBRadius(double new_rad){ m_dBoundingRadius = new_rad; }
	int ID()const{ return m_iID; }

	bool IsTagged()const{ return m_bTag; }
	void Tag(){ m_bTag = true; }
	void UnTag(){ m_bTag = false; }

	void SetZ(double new_Z){ m_dZ = new_Z; }

	Vector2D Scale()const{ return m_vScale; }
	void SetScale(Vector2D val){ m_dBoundingRadius *= MaxOf(val.x, val.y) / MaxOf(m_vScale.x, m_vScale.y); m_vScale = val; }
	void SetScale(double val){ m_dBoundingRadius *= (val / MaxOf(m_vScale.x, m_vScale.y)); m_vScale = Vector2D(val, val); }

	int EntityType()const{ return m_iType; }
	void SetEntityType(int new_type){ m_iType = new_type; }

	unsigned int Alpha()const{ return m_iAlpha; }
	void SetAlpha(unsigned int new_alpha){ assert(new_alpha < 0 && new_alpha>255); m_iAlpha = new_alpha; }

};