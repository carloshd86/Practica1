#pragma once

#include "sprite.h"
#include "vec2.h"
#include <litegfx.h>
#include <array>
#include <list>
#include <vector>

class World {
public:
	World(
		float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
		const ltex_t* back0 = nullptr, const ltex_t* back1 = nullptr,
		const ltex_t* back2 = nullptr, const ltex_t* back3 = nullptr) :
		mClearColor{ clearRed, clearGreen, clearBlue },
		mBackgrounds{ back0, back1, back2, back3 },
		mCurrentScrolls{ Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f) },
		mScrollRatios{ 1.0f, 1.0f, 1.0f, 1.0f },
		mScrollSpeeds{ 0.0f, 0.0f, 0.0f, 0.0f },
		mCameraPosition(0.0f, 0.0f),
		mMapSize(Vec2(0.0f, 0.0f)),
		mTileSize(Vec2(0.0f, 0.0f)) {}

	~World();

	float getClearRed() const { return mClearColor[0]; }
	float getClearGreen() const { return mClearColor[1]; }
	float getClearBlue() const { return mClearColor[2]; }
	const ltex_t* getBackground(size_t index) const { return mBackgrounds[index]; }
	float getScrollRatio(size_t layer) const { return mScrollRatios[layer]; }
	void setScrollRatio(size_t layer, float ratio) { mScrollRatios[layer] = ratio; }
	const Vec2& getScrollSpeed(size_t layer) const { return mScrollSpeeds[layer]; }
	void setScrollSpeed(size_t layer, const Vec2& speed) { mScrollSpeeds[layer] = speed; }
	const Vec2& getCameraPosition() const { return mCameraPosition; }
	void setCameraPosition(const Vec2& pos) { mCameraPosition = pos; }
	void addSprite(Sprite& sprite) { mSprites.push_back(&sprite); }
	void removeSprite(Sprite& sprite) { mSprites.remove(&sprite); }
	void update(float deltaTime);
	void draw(const Vec2& screenSize);

	bool loadMap(const char* filename, uint16_t firstColId);
	Vec2 getMapSize() const { return mMapSize; }
	bool moveSprite(Sprite& sprite, const Vec2& amount);

private:
	std::array<float, 3>	        mClearColor;
	std::array<const ltex_t *, 4>	mBackgrounds;
	std::array<Vec2, 4>	            mCurrentScrolls;
	std::array<float, 4>	        mScrollRatios;
	std::array<Vec2, 4>	            mScrollSpeeds;
	Vec2                            mCameraPosition;
	std::list<Sprite *>	            mSprites;
	Vec2                            mMapSize;
	Vec2                            mTileSize;
	int                             mTileColumns;
	int                             mTileRows;
	std::vector<int>                mTileGidList;
	ltex_t                         *mMapImage;
	int                             mFirstgid;
	uint16_t                        mFirstColId;
};