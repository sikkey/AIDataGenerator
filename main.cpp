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
using namespace inn;

#include <cstdio>
#include <random>

#define __Template_Input_Node_Count__ 784
#define __Template_Output_Node_Count__ 10
#define __PI__ 3.1415926
#define __RUN_GEN_FUNC_NAME__ TemplateGen

double TemplateInputTrait(size_t m, size_t n, int rand_data)
{
	int im = (int)m;
	int in = (int)n;

	return (((im << 4) + (in >> 4)) ^ ((im >> 4) + (in << 4)) ^ rand_data) / __PI__;
}

double TemplateOutputTrait(size_t m, size_t n, int rand_data)
{
	int ans = rand_data % __Template_Output_Node_Count__;
	if (n == (size_t)ans)
		return 1;
	
	return 0;
}

void TemplateGen(int TrainCount=100, int TestCount = 10, int InputCount=784, int OutputCount=10, std::string prefix="")
{
	NNTrainData trainData;
	NNTrainData testData;
	std::srand((unsigned int)time(0));

	// gen train file
	for (int groupId = 0; groupId < TrainCount; ++groupId)
	{
		int rand_data = rand();

		Matrix inputMatrix(1, __Template_Input_Node_Count__);
		for (size_t m = 0; m < inputMatrix.size1(); ++m) {
			for (size_t n = 0; n < inputMatrix.size2(); ++n) {
				inputMatrix(m, n) = TemplateInputTrait(m, n, rand_data);
			}
		}

		trainData.trainInputs.push_back(std::move(inputMatrix));

		Matrix outputMatrix(1, __Template_Output_Node_Count__);
		for (size_t m = 0; m < outputMatrix.size1(); ++m) {
			for (size_t n = 0; n < outputMatrix.size2(); ++n) {
				outputMatrix(m, n) = TemplateOutputTrait(m,n,rand_data);
			}
		}

		trainData.trainOutputs.push_back(std::move(outputMatrix));
	}

	std::string trainFilename = "train-" + NNTrainData::GetCurrTime();
	if (!prefix.empty())
	{
		trainFilename = prefix + "-train";
	}

	// save as txt
	trainData.SaveTXT(trainFilename);
	// save as binary
	trainData.SaveData(trainFilename);

	// gen test file
	for (int groupId = 0; groupId < TestCount; ++groupId)
	{
		int rand_data = rand();

		Matrix inputMatrix(1, __Template_Input_Node_Count__);
		for (size_t m = 0; m < inputMatrix.size1(); ++m) {
			for (size_t n = 0; n < inputMatrix.size2(); ++n) {
				inputMatrix(m, n) = TemplateInputTrait(m, n, rand_data);
			}
		}

		testData.trainInputs.push_back(std::move(inputMatrix));

		Matrix outputMatrix(1, __Template_Output_Node_Count__);
		for (size_t m = 0; m < outputMatrix.size1(); ++m) {
			for (size_t n = 0; n < outputMatrix.size2(); ++n) {
				outputMatrix(m, n) = TemplateOutputTrait(m, n, rand_data);
			}
		}

		testData.trainOutputs.push_back(std::move(outputMatrix));
	}

	std::string testFilename = "test-" + NNTrainData::GetCurrTime();
	if (!prefix.empty())
	{
		testFilename = prefix +"-test";
	}

	// save as txt
	testData.SaveTXT(testFilename);
	// save as binary
	testData.SaveData(testFilename);
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		__RUN_GEN_FUNC_NAME__(100,10,784,10,argv[1]);
	}
	else {
		__RUN_GEN_FUNC_NAME__();
	}
	
    return 0;
}