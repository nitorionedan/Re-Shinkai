#include "Image.hpp"


bool Image::is_sUpdate = true;


Image::Image()	: count(0){}


Image::~Image()
{
	if (count != 0)
	{
		for (auto& gh : this->gh)	DeleteGraph(gh);
	}
}


void Image::ChengeIsUpdate(){
	is_sUpdate = !is_sUpdate;
}


int Image::Load(const TCHAR * FNAME, std::string key)
{
	this->key.push_back(key);

	gh.push_back( LoadGraph(FNAME) );

	count++;
	
	return 0;
}


void Image::List()
{
	if (count == 0)	return;

	int c = 0;

	printfDx("Image key list�F\n");

	for (auto key : this->key)
	{
		std::string list = key + "\n";
		printfDx(list.c_str());
		c++;
	}

	printfDx("%d images had loaded.", c);
}


int Image::Draw(int X, int Y, const std::string & key, int TransFlag)
{
	if (count == 0)
		return -1;
	int Hdl = GetHandle(key);
	return DrawGraph(X, Y, Hdl, TransFlag);
}


int Image::DrawF(float X, float Y, const std::string & key, int TransFlag)
{
	if (count == 0)
		return -1;
	int Hdl = GetHandle(key);
	return DrawGraphF(X, Y, Hdl, TransFlag);
}


int Image::DrawRota(int X, int Y, double ExRate, double Angle, std::string key, int TransFlag, int TurnFlag)
{
	if (count == 0)
		return -1;
	int Hdl = GetHandle(key);
	return DrawRotaGraph(X, Y, ExRate, Angle, Hdl, TransFlag, TurnFlag);
}


int Image::DrawRotaF(float X, float Y, double ExRate, double Angle, std::string key, int TransFlag, int TurnFlag)
{
	if (count == 0)
		return -1;
	int Hdl = GetHandle(key);
	return DrawRotaGraphF(X, Y, ExRate, Angle, Hdl, TransFlag, TurnFlag);
}


int Image::DrawRect(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, const std::string & key, int TransFlag, int TurnFlag)
{
	if (count == 0)
		return -1;
	int Hdl = GetHandle(key);
	return DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, Hdl, TransFlag, TurnFlag);
}


int Image::DrawRasterScroll(const int& X, const int& Y, const double& Cycle, const double& Shake, const double& Speed, const std::string & Key, const bool& isVertical)
{
	if (count == 0)	return -1;

	const int& Hdl = GetHandle(Key);

	int Width = 0, Height = 0;					// Images width & height

	static double Correction = 0.;				// Adjust raster scrole
	static int error = 0;						// Return only variable

	GetGraphSize(Hdl, &Width, &Height);

	switch (isVertical)
	{
	case true:
		for (int I = 0; I < Height; ++I)
		{
			// �摜�̕����`��i�c�ɂPpix���j
			const int& DestX = X - Width / 2 + std::cos((I + Correction) / 180. * DX_PI * Cycle) * Shake;
			const int& DestY = Y - Height / 2 + I;

			error = DrawRectGraph
				(
					DestX, DestY,
					0, I,
					Width, 1,
					Hdl,
					TRUE, FALSE
				);
		}
		break;

	case false:
		for (int I = 0; I < Width; ++I)
		{
			const int& DestX = X - Width / 2 + I;
			const int& DestY = Y - Height / 2 + std::cos((I + Correction) / 180. * DX_PI * Cycle) * Shake;

			// �摜�̕����`��i���ɂPpix���j
			error = DrawRectGraph
				(
					DestX, DestY,
					I, 0,
					1, Height,
					Hdl,
					TRUE, FALSE
				);
		}
		break;

	}


	// If is_sUpdate is FALSE, it does'nt raster scroll.
	if (!is_sUpdate)	return error;

	Correction += Speed;

	return error;
}


int Image::GetSize(std::string key, int * width, int * height)
{
	if (count == 0)	return -1;

	const int& Hdl = GetHandle(key);

	return GetGraphSize(Hdl, width, height);;
}


int Image::GetHandle(std::string key)
{
	for (int i = 0; i != this->key.size(); ++i)
	{
		if (this->key[i] != key)	continue;
		return this->gh[i];
	}

	std::string warning = key + " key was not found.";

	MessageBox(NULL, warning.c_str(), "NOT FOUND", MB_OK);
	
	return -1;
}

// EOF