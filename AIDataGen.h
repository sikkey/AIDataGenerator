/*
MIT License

Copyright (c) 2020 7Mersenne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <iostream>
#include <fstream>
#include <utility>          // std::swap and std::move
#include <vector>
#include <random>
#include <cmath>            // for std::pow()
#include <ctime>
#include <string>

#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

namespace inn {
	typedef matrix<double> Matrix;

	class NNTrainData
	{
	public:
		std::vector<Matrix> trainInputs;
		std::vector<Matrix> trainOutputs;

		void SaveTXT(const std::string &InFileName = "") const;
		void LoadTXT(const std::string &InFileName);

		void SaveData(const std::string &InFileName = "") const;
		void LoadData(const std::string &InFileName);

		static std::string GetCurrTime();

	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & trainInputs;
			ar & trainOutputs;
		}
	};
}