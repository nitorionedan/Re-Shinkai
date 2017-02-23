/*
@file		Image.hpp
@brief		If you used this module, you no need DeleteGraph function!
@author		nitorionedan
@warning	This module uses DxLib functions.
*/
#ifndef DEF_IMAGE_HPP
#define DEF_IMAGE_HPP

#include "DxLib.h"
#include "Graphics2D.hpp"
#include <string>
#include <vector>

// TODO : Be implement.
/*
enum class eColor
{
	Red		= GetColor(255, 0, 0),
	Green	= GetColor(0, 255, 0),
	Blue	= GetColor(0, 0, 255),
};
*/

class Image
{
public:
	Image();
	~Image();

	static void ChengeIsUpdate();

	/* --------------------------------------------------------------------
	@brief					Near Raster Scrole
	@param[in]	X, Y		Position
	@param[in]	Cycle		Period
	@param[in]	Shake		Amplitude
	@param[in]	Key			Key Word
	@param[in]	isVertical	Does Wave direct vertical or horizontal?
	@return					Successe >> 1, Failed >> -1
	*/
	int DrawRasterScroll(const int &X, const int &Y, double Cycle, double Shake, const std::string &Key, bool isVertical = true){}

	int Load(const TCHAR* fileName, std::string key);

	void List();
	
	/// --------------------------------------------------------------------
	// @brief               左上を中心に画像を描画
	// @param[in] X, Y      描画座標
	// @param[in] key       画像キー
	// @param[in] TransFlag アルファチャンネルをしようするかどうか
	// @return              エラー判定
	int Draw(int    X, int   Y, const std::string& key, int TransFlag = 0 );
	int DrawF(float X, float Y, const std::string& key, int TransFlag = 0);

	/// --------------------------------------------------------------------
	// @brief               画像の中心を基準に描画
	// @param[in] X, Y      描画座標
	// @param[in] ExRate    拡大率
	// @param[in] Angle     回転値
	// @param[in] key       画像キー
	// @param[in] TransFlag アルファチャンネルをしようするかどうか
	// @param[in] TurnFlag  反転フラグ
	// @return              エラー判定
	int DrawRota(int    X, int   Y, double ExRate, double Angle, std::string key, int TransFlag = 0, int TurnFlag = 0);
	int DrawRotaF(float X, float Y, double ExRate, double Angle, std::string key, int TransFlag = 0, int TurnFlag = 0);

	/// --------------------------------------------------------------------
	// @brief                   画像の指定矩形部分のみを等倍描画
	// @param[in] DestX, DestY  描画座標
	// @param[in] SrcX, SrcY    矩形の左上
	// @param[in] Width, Height 矩形の左下
	// @param[in] key           画像キー
	// @param[in] TransFlag     アルファチャンネルをしようするかどうか
	// @param[in] TurnFlag      反転フラグ
	// @return                  エラー判定
	int DrawRect(int DestX,	int DestY, int SrcX, int SrcY, int Width, int Height, const std::string& key, int TransFlag = 0, int TurnFlag = 0 );

	/// --------------------------------------------------------------------
	// @brief					Near raster scroll
	// @param[in]	X, Y		Drawing position
	// @param[in]	Cycle		Wave period
	// @param[in]	Shake		Wave amplitude
	// @param[in]	Speed		Wave speed
	// @param[in]	Key			The key you yourself set
	// @param[in]	isVertical	Does wave facing vertical or  horizontal?
	// @return					Successful:1	Error:-1
	int DrawRasterScroll(const int& X, const int& Y, const double& Cycle, const double& Shake, const double& Speed, const std::string &Key, const bool& isVertical = true);
//	int DrawWrapScroll(const )

	int GetSize(std::string key, int* width, int* height);
	int GetHandle(std::string key);


private:
	static bool is_sUpdate;
	std::vector<std::string> key;	// Key name
	std::vector<int> gh;			// Graphics handle
	int count;
};


#endif // !DEF_IMAGE_HPP
