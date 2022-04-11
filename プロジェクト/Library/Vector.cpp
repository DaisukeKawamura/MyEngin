#include "Vector.h"

bool V3Colider::ColisionSphereToPlane(const Sphere &sphere, const Plane &plane, Vector3 *coliPos)
{
	//•½–Ê‚Æ‹…‚Ì’†S‚Æ‚Ì‹——£‚ğ‹‚ß‚é
	float dist = dot(sphere.center, plane.normal) - plane.distance;
	//‹——£‚Ìâ‘Î’l‚ª”¼Œa‚æ‚è‘å‚«‚¯‚ê‚Î‚ ‚½‚Á‚Ä‚È‚¢
	if (fabsf(dist) > sphere.rad) { return false; }
	//‚ ‚½‚Á‚Ä‚¢‚éê‡‚Í‹^—Œğ“_‚ğŒvZ
	*coliPos = -dist * plane.normal + sphere.center;
	//Õ“Ë
	return true;
}

const Vector3 V3Ease::lerp(const Vector3 &s, const Vector3 &e, const float t)
{
	Vector3 start = s;
	Vector3 end = e;
	return start * (1.0f - t) + end * t;
}

const Vector3 V3Ease::InQuad(const Vector3 &s, const Vector3 &e, const float t)
{
	Vector3 start = s;
	Vector3 end = e;
	return start * (1.0f - t) + end * (t * t);
}

const Vector3 V3Ease::OutQuad(const Vector3 &s, const Vector3 &e, const float t)
{
	Vector3 start = s;
	Vector3 end = e;
	return start * (1.0f - t) + end * (1 - (1 - t) * (1 - t));
}

const Vector3 V3Ease::InOutQuad(const Vector3 &s, const Vector3 &e, const float t)
{
	Vector3 start = s;
	Vector3 end = e;
	return t < 0.5f ? start * (1.0f - t) + end * (t * t) : start * (1.0f - t) + end * (1 - pow(-2 * t + 2, 2) / 2);
}
