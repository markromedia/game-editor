#include "background.hpp"

#include "opengl.h"
#include <sdl2/SDL.h>
#include <vector>
#include <set>
#include <sstream>
#include <time.h>

#include "background_elements.hpp"
#include "game.hpp"
#include "constants.cpp"
#include "graphics/render_operation.hpp"
#include "graphics/render_op_manager.hpp"
#include "graphics/texture.hpp"
#include "graphics/texture_manager.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "math/matrix4.hpp"

const int station_width = 581;
const int station_height = 355;
const int station_depth = 1094;

Background::Background()
{
}

void Background::InitStarBg()
{
	for (int i = 1; i <= 20; i++)
	{
		std::stringstream filename; 
		if (i < 10)
			filename << "resources\\ice_field_strip0" << i << ".bmp";
		else
			filename << "resources\\ice_field_strip" << i << ".bmp";
		Graphics::RenderOperation* op = Graphics::RenderOperationManager::GetDrawTextureOp(filename.str(), 1024, 64, 1024, 64);
		op->translation_y = (i - 1) * 64; 
		background_ops.push_back(op);
	}

	render_small_stars_op = Graphics::RenderOperationManager::GetDrawStarfieldOp(1, Graphics::Color4f::WHITE, 200);
	render_med_stars_op = Graphics::RenderOperationManager::GetDrawStarfieldOp(2, Graphics::Color4f::WHITE, 200);
	render_large_stars_op = Graphics::RenderOperationManager::GetDrawStarfieldOp(3, Graphics::Color4f::WHITE, 200);

	//init stars
	for (int i = 0; i < 200; i++) 
	{
		Star s = Star(render_small_stars_op->VertexBuffer->CreateVertex());
		s.velocity = .5f;
		small_stars.push_back(s);
	}

	for (int i = 0; i < 200; i++) 
	{
		Star s = Star(render_med_stars_op->VertexBuffer->CreateVertex());
		s.velocity = .75f;
		med_stars.push_back(s);
	}

	for (int i = 0; i < 200; i++) 
	{
		Star s = Star(render_large_stars_op->VertexBuffer->CreateVertex());
		s.velocity = 1;
		large_stars.push_back(s);
	}
}

void Background::InitStationBg()
{
	light_alpha = 0;
	lights_are_illuminating = true;
	//init pairs
	for (int i = 0; i < 10; i++)
	{
		int y_pos = station_height * (i - 1);
		float z_pos = z_pos = -station_depth / 2 - 300;

		Station left_station;
		Station right_station;

		int model = 5;
		left_station.RenderWireframeOp = Graphics::RenderOperationManager::GetDrawWireframeOp(model);
		left_station.RenderModelOp = Graphics::RenderOperationManager::GetDrawModelOp(model);
		right_station.RenderModelOp = Graphics::RenderOperationManager::GetDrawModelOp(model);
		right_station.RenderWireframeOp = Graphics::RenderOperationManager::GetDrawWireframeOp(model);
		left_station.RenderModelOp->Color.rbga(1, 1, 1, 1);
		right_station.RenderModelOp->Color.rbga(1,  1, 1, 1);
		left_station.RenderModelOp->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources\\station_color.bmp");
		right_station.RenderModelOp->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources\\station_color.bmp");
		left_station.RenderModelOp->Illumination_Texture = Graphics::TextureManager::GetTexture("resources\\station_illumination.bmp");
		right_station.RenderModelOp->Illumination_Texture = Graphics::TextureManager::GetTexture("resources\\station_illumination.bmp");

		/*
		float x_pos = -Constants::SCREEN_WIDTH / 2 - station_height;
		float x_rot = std::rand() % 2 == 0 ? 0 : 180;
		float y_rot = -20, z_rot = 90;
		Math::Matrix4 model_matrix = Math::Matrix4::XYZRotationMat(x_rot, y_rot, z_rot);
		left_station.RenderModelOp->ModelMatrix = model_matrix;
		left_station.RenderWireframeOp->ModelMatrix = model_matrix;
		left_station.RenderModelOp->ModelMatrix.SetTranslation(x_pos, y_pos, z_pos);
		left_station.RenderWireframeOp->ModelMatrix.SetTranslation(x_pos, y_pos, z_pos);

		float x_pos2 = Constants::SCREEN_WIDTH / 2 + station_height;
		float x_rot2 = std::rand() % 2 == 0 ? 0 : 180;
		float z_rot2 = -90;//std::rand() % 5 == 0 ? 90 : -90;
		float y_rot2 = 20;
		Math::Matrix4 model_matrix2 = Math::Matrix4::XYZRotationMat(x_rot2, y_rot2, z_rot2);
		right_station.RenderModelOp->ModelMatrix = model_matrix2;
		right_station.RenderWireframeOp->ModelMatrix = model_matrix2;
		right_station.RenderModelOp->ModelMatrix.SetTranslation(x_pos2, y_pos, z_pos);
		right_station.RenderWireframeOp->ModelMatrix.SetTranslation(x_pos2, y_pos, z_pos);

		left_stations.push_back(left_station);
		right_stations.push_back(right_station);
		*/
	}
}

void Background::Prepare( int background )
{
	this->background = background;
	
	switch (background) {
	case 0: 
		{
			InitStarBg();	
			break;
		}
	case 1: 
		{
			InitStationBg();	
			break;
		}
	}
}

void Background::Update( float dt )
{
	switch (background)	
	{
	case 0 :
		{
			UpdateStars(dt);
			break;
		}
	case 1:
		{
			/*
			int camera_y = Game::PerspectiveCamera->world_y;
			for(std::vector<Station>::iterator it = left_stations.begin(); it != left_stations.end(); ++it) 
			{
				int y_pos = it->RenderModelOp->ModelMatrix.data[13];
				int diff = camera_y - y_pos - station_height * 2;
				if (diff >= Constants::SCREEN_HEIGHT)
				{
					int max_y = 0;
					for(std::vector<Station>::iterator it2 = left_stations.begin(); it2 != left_stations.end(); ++it2) 
					{
						if (it2->RenderModelOp->ModelMatrix.data[13] > max_y)
							max_y = it2->RenderModelOp->ModelMatrix.data[13];
					}
					
					y_pos = max_y + station_height;
				}
				it->RenderModelOp->ModelMatrix.data[13] = y_pos;
				it->RenderWireframeOp->ModelMatrix.data[13] = y_pos;
			}
			for(std::vector<Station>::iterator it = right_stations.begin(); it != right_stations.end(); ++it) 
			{
				int y_pos = it->RenderModelOp->ModelMatrix.data[13];
				int diff = camera_y - y_pos - station_height * 2;
				if (diff >= Constants::SCREEN_HEIGHT)
				{
					int max_y = 0;
					for(std::vector<Station>::iterator it2 = right_stations.begin(); it2 != right_stations.end(); ++it2) 
					{
						if (it2->RenderModelOp->ModelMatrix.data[13] > max_y)
							max_y = it2->RenderModelOp->ModelMatrix.data[13];
					}

					y_pos = max_y + station_height;
				}
				it->RenderModelOp->ModelMatrix.data[13] = y_pos;
				it->RenderWireframeOp->ModelMatrix.data[13] = y_pos;

			}

			if (lights_are_illuminating)
			{
				light_alpha += .01;
				if (light_alpha >= .6) {
					lights_are_illuminating = false;
					light_alpha = .6;
				}
					
			}
			else
			{
				light_alpha -= .01;
				if (light_alpha <= 0) {
					light_alpha = 0;
					lights_are_illuminating = true;
				}
			}
			*/

			break;
		}
	}
	//queue renderables
	QueueRenderables();
}

void Background::UpdateStars(float dt)
{
	float dy = 0;//-0.05f;//(dt / 1000.0f * -10.0f);
	for(std::vector<Graphics::RenderOperation*>::iterator it = background_ops.begin(); it != background_ops.end(); ++it) {
		Graphics::RenderOperation* op = *it;
		op->translation_y += dy;
		if (op->translation_y + 64 < 0)
		{
			op->translation_y += (background_ops.size()) * 64;
		}
	}

	//update stars
	for(std::vector<Star>::iterator it = small_stars.begin(); it != small_stars.end(); ++it)
		it->Update(dt);
	for(std::vector<Star>::iterator it = med_stars.begin(); it != med_stars.end(); ++it)
		it->Update(dt);
	for(std::vector<Star>::iterator it = large_stars.begin(); it != large_stars.end(); ++it)
		it->Update(dt);
}

void Background::QueueRenderables()
{
	switch (background)	
	{
	case 0 :
		{
			for(std::vector<Graphics::RenderOperation*>::iterator it = background_ops.begin(); it != background_ops.end(); ++it) {
				Graphics::RenderOperation* op = *it;
				if (op->translation_y + 64 > 0 && op->translation_y < Constants::SCREEN_HEIGHT)
					Game::ScreenFrame->QueueRenderOperation(op, Game::OrthoCamera);
			}

			//queue stars
			Game::ScreenFrame->QueueRenderOperation(render_small_stars_op, Game::OrthoCamera);
			Game::ScreenFrame->QueueRenderOperation(render_med_stars_op, Game::OrthoCamera);
			Game::ScreenFrame->QueueRenderOperation(render_large_stars_op, Game::OrthoCamera);
			break;
		}
	case 1 :
		{
			RenderStationBg();
			break;
		}
	}
}


void Background::RenderStationBg()
{
	for(std::vector<Station>::iterator it = left_stations.begin(); it != left_stations.end(); ++it) 
	{
		it->RenderModelOp->Color.a = light_alpha;
		Game::ScreenFrame->QueueRenderOperation(it->RenderWireframeOp, Game::PerspectiveCamera);
		Game::ScreenFrame->QueueRenderOperation(it->RenderModelOp, Game::PerspectiveCamera);
	}
	for(std::vector<Station>::iterator it = right_stations.begin(); it != right_stations.end(); ++it) 
	{
		it->RenderModelOp->Color.a = light_alpha;
		Game::ScreenFrame->QueueRenderOperation(it->RenderWireframeOp, Game::PerspectiveCamera);
		Game::ScreenFrame->QueueRenderOperation(it->RenderModelOp, Game::PerspectiveCamera);
	}
}


