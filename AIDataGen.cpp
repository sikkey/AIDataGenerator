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

#include "AIDataGen.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/split_free.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

using namespace boost::archive;

namespace inn
{
	void NNTrainData::SaveTXT(const std::string & InFileName) const
	{
		std::string fileName;

		if (InFileName.empty()) {
			fileName = (GetCurrTime() + ".txt");
		}
		else {
			if (InFileName.length() > 4 && InFileName.substr(InFileName.length() - 4).compare(".txt") != 0) {
				fileName = (InFileName + ".txt");
			}
			else {
				fileName = InFileName;
			}
		}

		std::ofstream out(fileName);
		if (out.fail()) {
			std::cout << "ERROR:: Fails writing to file " << fileName << std::endl;
			exit(1);
		}

		text_oarchive toa(out);
		toa << *this;
	}

	void NNTrainData::LoadTXT(const std::string & InFileName)
	{
		std::ifstream in(InFileName);
		if (in.fail()) {
			std::cout << "ERROR:: CANNOT READ FROM FILE: '" << InFileName << "'\n";
			exit(1);
		}

		text_iarchive tia(in);
		tia >> *this;
	}

	void NNTrainData::SaveData(const std::string & InFileName) const
	{
		std::string fileName;

		if (InFileName.empty()) {
			fileName = (GetCurrTime() + ".dat");
		}
		else {
			if (InFileName.length() > 4 && InFileName.substr(InFileName.length() - 4).compare(".dat") != 0) {
				fileName = (InFileName + ".dat");
			}
			else {
				fileName = InFileName;
			}
		}

		std::ofstream out(fileName);
		if (out.fail()) {
			std::cout << "ERROR:: Fails writing to file " << fileName << std::endl;
			exit(1);
		}

		binary_oarchive boa(out);
		boa << *this;
	}

	void NNTrainData::LoadData(const std::string & InFileName)
	{
		std::ifstream in(InFileName);
		if (in.fail()) {
			std::cout << "ERROR:: CANNOT READ FROM FILE: '" << InFileName << "'\n";
			exit(1);
		}

		binary_iarchive bia(in);
		bia >> *this;
	}

	std::string NNTrainData::GetCurrTime()
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);
		std::string currTime = std::to_string(now->tm_year + 1900) + '-' + std::to_string(now->tm_mon + 1) + '-' + std::to_string(now->tm_mday);
		currTime += "--" + ((now->tm_hour < 10) ? "0" + std::to_string(now->tm_hour) : std::to_string(now->tm_hour));
		currTime += "-" + ((now->tm_min < 10) ? "0" + std::to_string(now->tm_min) : std::to_string(now->tm_min));
		currTime += "-" + ((now->tm_sec < 10) ? "0" + std::to_string(now->tm_sec) : std::to_string(now->tm_sec));
		return currTime;
	}
}