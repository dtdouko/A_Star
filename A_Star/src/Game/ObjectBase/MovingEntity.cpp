#include "MovingEntity.h"
#include "../../../../lib/gplib.h"

std::vector<MovingEntity*> MovingEntity::m_MovingEntities;

MovingEntity::MovingEntity(const std::string& resName,const std::string& fileName, int SrcX, int SrcY, int SizeX, int SizeY, Vector2D position, Vector2D velocity, double dZ, double max_speed, double mass, Vector2D scale, double max_force,int Type)
	:
	BaseGameEntity(BaseGameEntity::GetNextValidID()),
	m_sFilename(fileName),
	m_sResname(resName),
	m_vVelocity(velocity),
	m_dMass(mass),
	m_vSide(m_vHeading.Perp()),
	m_dMaxSpeed(max_speed),
	m_vHeading(Vector2D(sin(D3DXToRadian(m_dAngle)), -cos(D3DXToRadian(m_dAngle)))),
	m_dMaxForce(max_force)
{
	m_vPosition = position;
	m_vScale = scale;
	if(!m_sFilename.empty()&&!m_sResname.empty())
		gplib::graph::Draw_LoadObject(m_sFilename, m_sResname, 0);
	m_Rect.SizeX = SizeX;
	m_Rect.SizeY = SizeY;
	m_Rect.SrcX = SrcX;
	m_Rect.SrcY = SrcY;

	m_dZ = dZ;

	RECT def;
	def.bottom = SizeY;
	def.top = SrcY;
	def.left = SrcX;
	def.right = SizeX;

	SetEntityType(Type);

	m_MovingEntities.push_back(this);

	m_HitRect.insert(std::map<std::string, RECT>::value_type("default", def));

	m_pSteering = new SteeringBehavior(this);

}

void MovingEntity::Render()
{
	if (m_bVisible)
		gplib::graph::Draw_Graphics(static_cast<float>(m_vPosition.x), static_cast<float>(m_vPosition.y), static_cast<float>(m_dZ), m_sFilename, m_Rect.SrcX, m_Rect.SrcY, m_Rect.SizeX, m_Rect.SizeY, static_cast<float>(m_dAngle), 1.f, 1.f, m_iAlpha, 255, 255, 255);
	for (auto& rect : m_HitRect)
	{
		SetRect(&rect.second, static_cast<int>(m_vPosition.x) - m_Rect.SizeX / 2 + m_Rect.SrcX, static_cast<int>(m_vPosition.y) - m_Rect.SizeY / 2 + m_Rect.SrcY,
			(int)m_vPosition.x + m_Rect.SizeX / 2 - m_Rect.SrcX, (int)m_vPosition.y + m_Rect.SizeY / 2 - m_Rect.SrcY);
	}
}

RECT* MovingEntity::Get_Rect(const std::string& rectName)
{
	return &m_HitRect.find(rectName)->second;
}

#ifdef _DEBUG
void MovingEntity::Render_RectBox(const std::string& RectName, D3DCOLOR color)
{
	RECT rc = *Get_Rect(RectName);

	gplib::graph::Draw_Box(rc.left, rc.top, rc.right, rc.bottom,
		0.0f, ARGB(254, 0, 0, 0), color, 1, 0);
}
#endif


void MovingEntity::Add_HitRect(std::string rectName,int bottom,int top,int right, int left)
{
	RECT rect;
	rect.bottom = bottom;
	rect.top = top;
	rect.right = right;
	rect.left = left;

	m_HitRect.insert(std::map<std::string, RECT>::value_type(rectName, rect));

}

void MovingEntity::Add_Collisioncircle(const std::string CircleName, Vector2D Center, double Radius)
{
	Circle circle;
	circle.Center = Center;
	circle.Radius = Radius;
	//m_CollisionCircles.insert(std::make_pair(CircleName, circle));
	m_CollisionCircles[CircleName] = circle;
}

MovingEntity::Circle* MovingEntity::Get_CollisionCircle(const std::string CircleName)
{
	return &m_CollisionCircles[CircleName];
}

void MovingEntity::Move()
{
	Vector2D OldPos = Pos();

	Vector2D SteeringForce;

	SteeringForce = m_pSteering->Calculate();

	Vector2D acceleration = SteeringForce / m_dMass;

	m_vVelocity += acceleration;

	m_vVelocity.Truncate(m_dMaxSpeed);

	m_vPosition += m_vVelocity;

	if (m_vVelocity.LengthSq() > 0.00000001)
	{
		m_vHeading = Vec2DNormalize(m_vVelocity);

		m_vSide = m_vHeading.Perp();
	}


}
