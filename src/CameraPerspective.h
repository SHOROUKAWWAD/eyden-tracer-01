// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"
#include "ray.h"

// ================================ Perspective Camera Class ================================
/**
 * @brief Perspective Camera class
 * @ingroup moduleCamera
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param resolution The image resolution in pixels
	 * @param pos Camera origin (center of projection)
	 * @param dir Normalized camera viewing direction
	 * @param up Normalized camera up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum in degrees
	 */
	CCameraPerspective(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float angle)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
		, Size resolution 
	{
		m_zAxis = m_dir;
		m_xAxis = cv::normalize(m_zAxis.cross(m_up));
		m_yAxis = cv::normalize (m_zAxis.cross(m_xAxis));
		m_focus = 1 / tan((pif *angle)/360)
		m_aspect = (float)resolution.width / resolution.height;
	}
	virtual ~CCameraPerspective(void) = default;

	virtual void InitRay(Ray& ray, int x, int y) override
	{
		// --- PUT YOUR CODE HERE ---
		float ndcx = (float)(x + 0.5) / getResolution().width;
		float ndcy = (float)(x + 0.5) / getResolution().height;
		float sscx = (float)(2 * ndcx - 1);
		float sscy = (float)2 * ndcy - 1;
		ray.org = m_pos;
		ray.t = std::numeric_limits<float>::max();
		ray.dir = m_xAxis * (2.0 * ((x + 0.5) / getResolution().width) * m_aspect) + (m_yAxis * (1.0 - 2 * (y + 0.5) / getResolution().height)) + (m_zAxis * m_focus);
	}


private:
	// input values
	Vec3f m_pos;			///< Camera origin (center of projection)
	Vec3f m_dir;			///< Camera viewing direction
	Vec3f m_up;				///< Camera up-vector
	float m_focus;	///< The focal length
	float m_aspect;
	// preprocessed values
	Vec3f m_xAxis;			///< Camera x-axis in WCS
	Vec3f m_yAxis;			///< Camera y-axis in WCS
	Vec3f m_zAxis;			///< Camera z-axis in WCS
};

