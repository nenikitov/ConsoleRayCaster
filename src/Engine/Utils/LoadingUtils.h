#pragma once

class LoadingUtils
{
	public:
		static bool loadCapped(const int VALUE, int& out, const int MIN = 0, const int MAX = 7);
		static bool loadCappedNormalized(const int VALUE, double& out, const int MIN = 0, const int MAX = 7);
};
