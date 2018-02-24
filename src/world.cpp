#include "world.h"
#include "pugixml.hpp"
#include "stringutils.h"
#include "ugine.h"
#include <algorithm>
#include <iostream>


World::~World() { if (mMapImage) ltex_free(mMapImage); }

void World::update(float deltaTime) {

	// Actualizamos scroll automatico
	for (int i = 3; i >= 0; --i) {
		mCurrentScrolls[i] = mCurrentScrolls[i] - (mScrollSpeeds[i] * deltaTime);
		if (mBackgrounds[i]) {
			if(static_cast<int>(mCurrentScrolls[i].x) >= mBackgrounds[i]->width) mCurrentScrolls[i].x -= static_cast<float>(mBackgrounds[i]->width);
			else if(mCurrentScrolls[i].x < 0.0f)                                 mCurrentScrolls[i].x += static_cast<float>(mBackgrounds[i]->width);

			if(static_cast<int>(mCurrentScrolls[i].y) >= mBackgrounds[i]->height) mCurrentScrolls[i].y -= static_cast<float>(mBackgrounds[i]->height);
			else if(mCurrentScrolls[i].y < 0.0f)                                  mCurrentScrolls[i].y += static_cast<float>(mBackgrounds[i]->height);
		}
	}

	// Actualizamos sprites
	for(Sprite * sprite : mSprites) {
		sprite->update(deltaTime);
	}
}

void World::draw(const Vec2& screenSize) {

	// Establecemos propiedades de pintado
	lgfx_clearcolorbuffer(mClearColor[0], mClearColor[1], mClearColor[2]);
	
	// Aplicamos traslacion de camara
	lgfx_setorigin(mCameraPosition.x, mCameraPosition.y);

	// Pintamos

	// Backgrounds
	for (int i = 3; i >= 0; --i) {
		const ltex_t * back = mBackgrounds[i];
		if (back) {
			float u0 = ((mCameraPosition.x * mScrollRatios[i]) + mCurrentScrolls[i].x) / back->width;
			float v0 = ((mCameraPosition.y * mScrollRatios[i]) + mCurrentScrolls[i].y) / back->height;
			float u1 = u0 + (screenSize.x / back->width);
			float v1 = v0 + (screenSize.y / back->height);

			ltex_drawrotsized(back, mCameraPosition.x, mCameraPosition.y, 0.0f, 0.0f, 0.0f, screenSize.x, screenSize.y, u0, v0, u1, v1);
		}
	}

	// Map
	Sprite tileSprite(mMapImage, mTileColumns, mTileRows);
	Vec2 tilesPerMap = mMapSize / mTileSize;
	Vec2 tileDrawPosition;
	int mTileGidListSize = mTileGidList.size();
	int maxTileGid = (mTileColumns * mTileRows) + mFirstgid - 1;
	for(int i = 0; i < mTileGidListSize; ++i) {
		int gid = mTileGidList[i] - mFirstgid;
		if (gid < mFirstgid || gid > maxTileGid) continue;

		int row = gid / mTileColumns;
		int col = gid % mTileColumns;
		float stepU = 1.0f / mTileColumns;
		float stepV = 1.0f / mTileRows;
		float u0 = col * stepU;
		float v0 = row * stepV;
		float u1 = u0 + stepU;
		float v1 = v0 + stepV;

		int mapRow = i / static_cast<int>(tilesPerMap.x);
		int mapCol = i % static_cast<int>(tilesPerMap.x);
		tileDrawPosition.x = mapCol * mTileSize.x;
		tileDrawPosition.y = mapRow * mTileSize.y;

		ltex_drawrotsized(mMapImage, tileDrawPosition.x, tileDrawPosition.y, 0.0f, 0.0f, 0.0f, mTileSize.x, mTileSize.y, u0, v0, u1, v1);
		tileSprite.setPivot(Vec2());
		tileSprite.setPosition(tileDrawPosition);
	}

	for(Sprite * sprite : mSprites) { sprite->draw(); }
}

bool World::loadMap(const char* filename, uint16_t firstColId) {

	mTileGidList.clear();

	mFirstColId = firstColId;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename);

	if (!result) {
		std::cout << "Map file not found" << std::endl;
		return false;
	}

	pugi::xml_node mapNode = doc.child("map");
	int mapWidth = mapNode.attribute("width").as_int();
	int mapHeight = mapNode.attribute("height").as_int();
	mTileSize.x = mapNode.attribute("tilewidth").as_float();
	mTileSize.y = mapNode.attribute("tileheight").as_float();
	mMapSize.x = mapWidth * mTileSize.x;
	mMapSize.y = mapHeight * mTileSize.y;

	pugi::xml_node tilesetNode = mapNode.child("tileset");
	mFirstgid = tilesetNode.attribute("firstgid").as_int();
	int tileCount = tilesetNode.attribute("tilecount").as_int();
	mTileColumns = tilesetNode.attribute("columns").as_int();
	mTileRows = tileCount / mTileColumns;
	//int tileWidth2 = tilesetNode.attribute("tilewidth").as_int();
	//int tileHeight2 = tilesetNode.attribute("tileheight").as_int();

	pugi::xml_node imageNode = tilesetNode.child("image");
	const char * imageSource = imageNode.attribute("source").as_string();
	int imageWidth = imageNode.attribute("width").as_int();
	int imageHeight = imageNode.attribute("height").as_int();
	std::string imageRealPath = extractPath(filename) + imageSource;
	mMapImage = loadTexture(imageRealPath.c_str());
	if (!mMapImage) {
		std::cout << "Image of tileset not found" << std::endl;
		return false;
	}

	pugi::xml_node tileoffsetNode = tilesetNode.child("tileoffset");
	int tileoffsetX = tileoffsetNode.attribute("x").as_int();
	int tileoffsetY = tileoffsetNode.attribute("y").as_int();


	pugi::xml_node layerNode = mapNode.child("layer");
	pugi::xml_node layerDataNode = layerNode.child("data");
	std::string encoding = layerDataNode.attribute("encoding").as_string();
	std::string compression = layerDataNode.attribute("compression").as_string();
	if (!encoding.empty()) {
		std::cout << "Unsupported encoding" << std::endl;
		return false;
	}
	if (!compression.empty()) {
		std::cout << "Unsupported compression" << std::endl;
		return false;
	}

	for (pugi::xml_node tileNode = layerDataNode.child("tile"); tileNode; tileNode = tileNode.next_sibling("tile")) {
		// Iteramos por todos los tiles
		mTileGidList.push_back(tileNode.attribute("gid").as_int());
	}

	return true;
}

bool World::moveSprite(Sprite& sprite, const Vec2& amount) {

	bool isCollision = false;
	Sprite tileSprite(mMapImage, mTileColumns, mTileRows);
	tileSprite.setPivot(Vec2(0.f, 0.f));
	tileSprite.setCollisionType(Sprite::CollisionType::COLLISION_RECT);

	int mTileGidListSize = mTileGidList.size();
	int maxTileGid = (mTileColumns * mTileRows) + mFirstgid - 1;
	Vec2 tilesPerMap = mMapSize / mTileSize;
	Vec2 tileDrawPosition;
	Vec2 spritePosition = sprite.getPosition();
	
	spritePosition.x += amount.x;
	if (spritePosition.x < 0.f) spritePosition.x = 0.f;
	if (spritePosition.x > mMapSize.x) spritePosition.x = mMapSize.x;
	sprite.setPosition(spritePosition);
	for(int i = 0; i < mTileGidListSize; ++i) {
		int gid = mTileGidList[i] - mFirstgid;
		if (gid < mFirstgid || gid > maxTileGid || gid < mFirstColId) continue;

		int mapRow = i / static_cast<int>(tilesPerMap.x);
		int mapCol = i % static_cast<int>(tilesPerMap.x);
		tileDrawPosition.x = mapCol * mTileSize.x;
		tileDrawPosition.y = mapRow * mTileSize.y;
		tileSprite.setPosition(tileDrawPosition);
		if (sprite.collides(tileSprite)) {
			isCollision = true;
			spritePosition.x -= amount.x;
			break;
		}
	}

	spritePosition.y += amount.y;
	if (spritePosition.y < 0.f) spritePosition.y = 0.f;
	if (spritePosition.y > mMapSize.y) spritePosition.y = mMapSize.y;
	sprite.setPosition(spritePosition);
	for(int i = 0; i < mTileGidListSize; ++i) {
		int gid = mTileGidList[i] - mFirstgid;
		if (gid < mFirstgid || gid > maxTileGid || gid < mFirstColId) continue;

		int mapRow = i / static_cast<int>(tilesPerMap.x);
		int mapCol = i % static_cast<int>(tilesPerMap.x);
		tileDrawPosition.x = mapCol * mTileSize.x;
		tileDrawPosition.y = mapRow * mTileSize.y;
		tileSprite.setPosition(tileDrawPosition);
		if (sprite.collides(tileSprite)) {
			isCollision = true;
			spritePosition.y -= amount.y;
			break;
		}
	}

	sprite.setPosition(spritePosition);

	return isCollision;
}