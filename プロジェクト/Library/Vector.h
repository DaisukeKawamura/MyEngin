#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//XMFLOAT3�����Z�q�I�[�o�[���[�h������Vector3�^
class Vector3 : public XMFLOAT3
{
public:
	//�R���X�g���N�^
	Vector3(float x, float y, float z) : XMFLOAT3(x, y, z) {};
	Vector3() :XMFLOAT3(0, 0, 0) {};

	Vector3 operator+(const Vector3 &other)const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 operator-(const Vector3 &other)const { return Vector3(x - other.x, y - other.y, z - other.z); }
	Vector3 operator*(const Vector3 &other)const { return Vector3(x * other.x, y * other.y, z * other.z); }
	Vector3 operator/(const Vector3 &other)const { return Vector3(x / other.x, y / other.y, z / other.z); }
	Vector3 &operator+=(const Vector3 &other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	Vector3 &operator-=(const Vector3 &other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	Vector3 &operator*=(const Vector3 &other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
	Vector3 &operator/=(const Vector3 &other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

	Vector3 operator+(const XMFLOAT3 &other)const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 operator-(const XMFLOAT3 &other)const { return Vector3(x - other.x, y - other.y, z - other.z); }
	Vector3 operator*(const XMFLOAT3 &other)const { return Vector3(x * other.x, y * other.y, z * other.z); }
	Vector3 operator/(const XMFLOAT3 &other)const { return Vector3(x / other.x, y / other.y, z / other.z); }
	Vector3 &operator+=(const XMFLOAT3 &other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	Vector3 &operator-=(const XMFLOAT3 &other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	Vector3 &operator*=(const XMFLOAT3 &other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
	Vector3 &operator/=(const XMFLOAT3 &other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

	Vector3 &operator=(const XMFLOAT3 &other) { 
		Vector3 result = Vector3(other.x, other.y, other.z);
		return result; 
	}
	

	bool operator==(const Vector3 &other) { return this->x == other.x && this->y == other.y && this->z == other.z; }
	bool operator!=(const Vector3 &other) { return !(*this == other); }

	Vector3 operator*(const float &other) { return Vector3(x * other, y * other, z * other); }
	Vector3 operator/(const float &other) { return Vector3(x / other, y / other, z / other); }
	Vector3 operator*=(const float &other) { this->x *= other; this->y *= other; return *this; }
	Vector3 operator/=(const float &other) { this->x /= other; this->y /= other; return *this; }

	float length() { return sqrtf(x * x + y * y + z * z); }
	Vector3 norm() { return Vector3(x / length(), y / length(), z / length()); }
	float distance(const Vector3 &v) { return sqrtf(pow(v.x - x, 2) + pow(v.y - y, 2) + pow(v.z - z, 2)); }

	void zero() { x = 0, y = 0, z = 0; }

	Vector3 operator-() const { return Vector3(-x, -y, -z); }
};

inline float dot(const Vector3 &a, const Vector3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Vector3 cross(const Vector3 &a, const Vector3 &b) { return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

inline float distance(const Vector3 &v1,const Vector3 &v2){return sqrtf(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));}

inline Vector3 operator*(const float &sum, const Vector3 &sum2) { return Vector3(sum2.x * sum, sum2.y * sum, sum2.z * sum); }
inline Vector3 operator/(const float &sum, const Vector3 &sum2) { return Vector3(sum2.x / sum, sum2.y / sum, sum2.z / sum); }

//�ۊ�
inline const Vector3 lerp(const Vector3 &s, const Vector3 &e, const float t) {
	Vector3 start = s;
	Vector3 end = e;
	return start * (1.0f - t) + end * t;
}

namespace V3Ease {

	/// <summary>
	/// ���`��ԁi�����͊�{�S�����̌`�j
	/// </summary>
	/// <param name="s">�J�n�_</param>
	/// <param name="e">�I���_</param>
	/// <param name="t">�i�s���ԁi1.0 ~ 0.0�j�͈̔�</param>
	/// <returns>Vector3�^��t�̂Ƃ��̍��W��Ԃ�</returns>
	const Vector3 lerp(const Vector3 &s, const Vector3 &e, const float t);

	const Vector3 InQuad(const Vector3 &s, const Vector3 &e, const float t);

	const Vector3 OutQuad(const Vector3 &s, const Vector3 &e, const float t);

	const Vector3 InOutQuad(const Vector3 &s, const Vector3 &e, const float t);

}

//Vector3�^���g�p�����Փ˔���v���~�e�B�u
namespace V3Colider {

	///�����s�o�E���f�B���O�{�b�N�X AABB
	struct Rv3AABB {

		Vector3 min;	//����T�C�Y
		Vector3 max;	//����T�C�Y
		Vector3 oldPos;//1F�O�̍��W

		//�R���X�g���N�^�A�f�X�g���N�^
		Rv3AABB()	= default;
		~Rv3AABB()	= default;

		/// <summary>
		/// AABB�f�[�^�̃R���X�g���N�^
		/// </summary>
		/// <param name="min">���S�_����̋���A</param>
		/// <param name="max">���S�_����̋���B</param>
		/// <param name="pos">����̒��S�_</param>
		Rv3AABB(Vector3 min, Vector3 max, Vector3 pos) {
			this->min = pos + min;
			this->max = pos + max;
			this->oldPos = pos;
		}

		/// <summary>
		/// AABB�f�[�^�ݒ�
		/// </summary>
		/// <param name="pos">����̒��S�_</param>
		/// <param name="min">���S�_����̋���A</param>
		/// <param name="max">���S�_����̋���B</param>
		inline void Set(Vector3 pos, Vector3 min, Vector3 max) {
			this->min = pos + min;
			this->max = pos + max;
			this->oldPos = pos;
		}

		/// <summary>
		/// AABB�̃f�[�^�X�V
		/// </summary>
		/// <param name="actpos">���̎��_�ł�AABB�̒��S���W�iRVector3�j</param>
		inline void Update(Vector3 actpos) {
			Vector3 diff = actpos - oldPos;
			min += diff;
			max += diff;
			oldPos = actpos;
		}
	};

	/// <summary>
	/// AABB���m�̔���
	/// </summary>
	/// <param name="box1">�{�b�N�X1</param>
	/// <param name="box2">�{�b�N�X2</param>
	/// <returns>�Փ˔���</returns>
	inline bool ColisionAABB(const Rv3AABB &box1, const Rv3AABB &box2) {
		//��Փ�
		if (box1.min.x > box2.max.x) { return false; }
		if (box1.max.x < box2.min.x) { return false; }
		if (box1.min.y > box2.max.y) { return false; }
		if (box1.max.y < box2.min.y) { return false; }
		if (box1.min.z > box2.max.z) { return false; }
		if (box1.max.z < box2.min.z) { return false; }
		//�Փ�
		return true;
	}

	//��
	struct Sphere {
		//���S���W
		Vector3 center;
		//���a
		float rad;
		//�f�t�H���g�R���X�g���N�^
		Sphere() {
			center = Vector3(0, 0, 0);
			rad = 0;
		}
		//�l�w��R���X�g���N�^
		Sphere(Vector3 pos, float r) {
			center = pos;
			rad = r;
		}
	};

	/// <summary>
	/// �����m�̔���
	/// </summary>
	/// <param name="a">��1</param>
	/// <param name="b">��2</param>
	/// <returns>�Փ˔���</returns>
	inline bool Colision2Sphere(Sphere a, Sphere b) {
		if (a.rad + b.rad < distance(a.center, b.center)) {
			return false;
		}
		//�Փ�
		return true;
	}

	//����
	struct Plane
	{
		//�@���x�N�g��
		Vector3 normal;
		//���_����̋���
		float distance;
		//�f�t�H���g
		Plane() {
			normal.zero();
			distance = 0;
		}
		//�l�w��
		Plane(Vector3 n, float d) {
			normal = n;
			distance = d;
		}
	};

	/// <summary>
	/// ���ƕ��ʂ̏Փ˔���
	/// </summary>
	/// <param name="sphere">���̃v���~�e�B�u</param>
	/// <param name="plane">���ʃv���~�e�B�u</param>
	/// <param name="coliPos">�Փ˓_��Ԃ��ϐ�</param>
	/// <returns>�Փ˔���</returns>
	bool ColisionSphereToPlane(const Sphere &sphere, const Plane &plane, Vector3 *coliPos = nullptr);

	struct Ray {
		Vector3 start;
		Vector3 dir;
	};

	inline Vector3 CalcScreen2World(const XMFLOAT2 &scrPos, float fz,float window_w,float window_h,const XMMATRIX &prj,const XMMATRIX &view) {
		XMVECTOR pos;
		//�ˉe�ϊ��s��ƃr���[�|�[�g�s��̋t�s����i�[����ϐ�
		XMMATRIX InvPrj, InvVP,InvV;
		//�e�s��̋t�s����o��
		InvPrj = XMMatrixInverse(nullptr, prj);
		//�r���[�|�[�g�s��͂��Ƃ͂Ȃ��H�̂ł����Œ�`���ċt�s����o��
		InvVP = XMMatrixIdentity();
		InvVP.r[0].m128_f32[0] = window_w / 2.0f;
		InvVP.r[1].m128_f32[1] = -window_h / 2.0f;
		InvVP.r[3].m128_f32[0] = window_w / 2.0f;
		InvVP.r[3].m128_f32[1] = window_h / 2.0f;
		InvVP = XMMatrixInverse(nullptr, InvVP);

		InvV = XMMatrixInverse(nullptr, view);

		XMMATRIX inverce = InvVP * InvPrj * InvV;
		XMVECTOR scr = { scrPos.x,scrPos.y,fz };

		pos = XMVector3TransformCoord(scr, inverce);

		Vector3 returnpos = { pos.m128_f32[0],pos.m128_f32[1],pos.m128_f32[2] };
		return returnpos;
	}

	inline Ray CalcScreen2WorldRay(XMFLOAT2 &scrPos, float window_w, float window_h, XMMATRIX &prj,XMMATRIX &view) {

		Ray result;
		result.start = CalcScreen2World(scrPos, 0, window_w, window_h, prj, view);
		result.dir = CalcScreen2World(scrPos, 1, window_w, window_h, prj, view);
		return result;
	}

	inline bool ColisionRay2Plane(const Ray &ray, const Plane &plane, float *distance = nullptr, Vector3 *inter = nullptr) {
		const float epsilon = 1.0e-5f;
		Vector3 n = ray.dir;
		n.norm();
		Vector3 pn = plane.normal;
		pn.norm();
		float d1 = dot(pn, n);
		if (d1 > -epsilon) { return false; }
		float d2 = dot(pn, ray.start);
		float dist = d2 - plane.distance;
		float t = dist / -d1;
		if (t < 0) { return false; }
		if (distance) { *distance = t; }
		if (inter) {
			*inter = ray.start + t * n;
		}
		return true;
	}

	//�O�p�`
	struct Triangle {
		//���_���W
		Vector3 p0, p1, p2;
		//�@��
		Vector3 normal;
	};
};
