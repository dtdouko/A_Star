#include "BaseGameEntity.h"
#include "../../../../lib/gplib.h"

int BaseGameEntity::m_iNextValidID = 0;

BaseGameEntity::BaseGameEntity(int ID)
	:
	m_dBoundingRadius(0.0),
	m_vScale(Vector2D(1.0, 1.0)),
	m_iType(default_entity_type),
	m_bTag(false)
{
	SetID(ID);
}

void BaseGameEntity::SetID(int val)
{
	assert((val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

	m_iID = val;

	m_iNextValidID = m_iID + 1;
}