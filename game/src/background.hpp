#ifndef __BACKGROUND_hpp
#define __BACKGROUND_hpp

#include <vector>

#include "background_elements.hpp"

//forward declarations
namespace Graphics {
	class VertexBuffer;
	class Vertex;
	class RenderOperation;
}


class Background
{
private:
	/// Initialises the star background.
	void InitStarBg();

	/// Initialises the station background.
	void InitStationBg();

	/// Renders the star background.
	void UpdateStars(float dt);

	/// Renders the station background.
	void RenderStationBg();

	/// @summary	The background.
	int background;

	Graphics::RenderOperation* render_large_stars_op;
	Graphics::RenderOperation* render_med_stars_op;
	Graphics::RenderOperation* render_small_stars_op;

	std::vector<Graphics::RenderOperation*> background_ops;
	std::vector<Star> small_stars;
	std::vector<Star> med_stars;
	std::vector<Star> large_stars;

	std::vector<Graphics::RenderOperation*> station_ops;
	std::vector<Station> left_stations;
	std::vector<Station> right_stations;

	float light_alpha;
	bool lights_are_illuminating;
public:
	/// Default constructor.
	Background(void);

	/// Prepares the provided background for display
	/// @param	background	The background.
	void Prepare(int background);

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);

	/// Renders this object.
	void QueueRenderables();
};


#endif  // __BACKGROUND_hpp